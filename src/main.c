/*
 * Copyright (c) 2022 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>

#include <string.h>
#include <stdio.h>

#include "gpios.h"

/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_CHOSEN(zephyr_shell_uart)

#define MSG_SIZE 32

/* queue to store up to 10 messages (aligned to 4-byte boundary) */
K_MSGQ_DEFINE(uart_msgq, MSG_SIZE, 10, 4);

static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

/* receive buffer used in UART ISR callback */
static char rx_buf[MSG_SIZE];
static int rx_buf_pos;

/*
 * Read characters from UART until line end is detected. Afterwards push the
 * data to the message queue.
 */
void serial_cb(const struct device *dev, void *user_data)
{
	uint8_t c;

	if (!uart_irq_update(uart_dev)) {
		return;
	}

	if (!uart_irq_rx_ready(uart_dev)) {
		return;
	}

	/* read until FIFO empty */
	while (uart_fifo_read(uart_dev, &c, 1) == 1) {
		if ((c == '\n' || c == '\r') && rx_buf_pos > 0) {
			/* terminate string */
			rx_buf[rx_buf_pos] = '\0';

			/* if queue is full, message is silently dropped */
			k_msgq_put(&uart_msgq, &rx_buf, K_NO_WAIT);

			/* reset the buffer (it was copied to the msgq) */
			rx_buf_pos = 0;
		} else if (rx_buf_pos < (sizeof(rx_buf) - 1)) {
			rx_buf[rx_buf_pos++] = c;
		}
		/* else: characters beyond buffer size are dropped */
	}
}

/*
 * Print a null-terminated string character by character to the UART interface
 */
void print_uart(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++) {
		uart_poll_out(uart_dev, buf[i]);
	}
}

static int current_driver = 0;

void gpio_init(void) {
	int ret = gpio_pin_configure_dt(&gpio[0], GPIO_OUTPUT_HIGH);
	if (ret < 0)
		print_uart("error :(\r\n");
	for (int i=1; i<PIN_NUM; i++) {
		ret = gpio_pin_configure_dt(&gpio[i], GPIO_INPUT | GPIO_PULL_DOWN);
		if (ret < 0)
			print_uart("error :(\r\n");
	}
}

void select_next(void) {
	int ret = gpio_pin_configure_dt(&gpio[current_driver], GPIO_INPUT | GPIO_PULL_DOWN);
	if (ret < 0)
		print_uart("error disabling :(\r\n");
	current_driver = (current_driver + 1) % PIN_NUM;
	ret = gpio_pin_configure_dt(&gpio[current_driver], GPIO_OUTPUT_HIGH);
	if (ret < 0)
		print_uart("error enabling next :(\r\n");
}

typedef struct {
	uint8_t first;
	uint8_t second;
} pair_t;

pair_t get_pair(void) {
	pair_t p = {0xff, 0xff};
	for (uint8_t i=0; i<PIN_NUM; i++) {
		for (uint8_t j=0; j<PIN_NUM; j++) {
			if (j == i)
				continue;
			int level = gpio_pin_get_dt(&gpio[j]);
			if (level < 0) {
				print_uart("an error getting pin state :(\r\n");
			} else if (level == 1) {
				if (p.first == 0xff) {
					p.first = i; p.second = j;
				} else if (p.first != j && p.second != i) {
					print_uart("detected more than one pair!\r\n");
				}
			}
		}
		select_next();
	}
	return p;
}

int main(void)
{
	char tx_buf[MSG_SIZE];

	if (!device_is_ready(uart_dev)) {
		printk("UART device not found!");
		return 0;
	}

	/* configure interrupt and callback to receive data */
	int ret = uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);

	if (ret < 0) {
		if (ret == -ENOTSUP) {
			printk("Interrupt-driven UART API support not enabled\n");
		} else if (ret == -ENOSYS) {
			printk("UART device does not support interrupt-driven API\n");
		} else {
			printk("Error setting UART callback: %d\n", ret);
		}
		return 0;
	}
	uart_irq_rx_enable(uart_dev);

	gpio_init();

	print_uart("Hello! I'm your keyboard bot.\r\n");
	print_uart("Type the name of a key, hold it and press enter to get a pin pair for it.\r\n");

	char s_to_print[20];
	/* indefinitely wait for input from the user */
	while (k_msgq_get(&uart_msgq, &tx_buf, K_FOREVER) == 0) {
		pair_t p = get_pair();
		sprintf(s_to_print, "%s: (%d, %d)\r\n", tx_buf, p.first, p.second);
		print_uart(s_to_print);
	}
	return 0;
}
