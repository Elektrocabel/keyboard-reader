#include <zephyr/drivers/gpio.h>
#ifndef GPIOS_H
#define GPIOS_H

#define PIN_NUM 30

static struct gpio_dt_spec gpio[30] = {
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 0),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 1),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 2),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 3),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 4),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 5),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 6),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 7),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 8),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 9),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 10),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 11),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 12),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 13),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 14),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 15),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 16),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 17),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 18),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 19),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 20),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 21),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 22),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 23),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 24),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 25),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 26),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 27),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 28),
    GPIO_DT_SPEC_GET_BY_IDX(DT_NODELABEL(keyboard0), gpios, 29)
};

#endif //GPIOS_H