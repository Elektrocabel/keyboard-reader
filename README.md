## Keyboard reader
This small utility can help you figure out your keyboard's rows and columns.

#### HOWTOS
1. edit `app.overlay` to enumerate your GPIO connections
2. build and flash
3. open a serial port
    * type a key name, e.g. `Space` and hold this key on the target keyboard
    * press enter
    * `<key_name> (<first>, <second>)` will be printed
        * if `first` and `second` are in your pin number range, you got your pin pair for the key
        * if it is `(255, 255)` the pair couldn't be found, you might want to check your connections and/or pin availability (if a certain pin never appears for any key, it's worth checking)

#### Notes
This was built for and used on an NRF52840 DK, other boards should probably work fine as long as they have enough GPIOs to host your target keyboard.