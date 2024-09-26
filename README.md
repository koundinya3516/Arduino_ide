PIN CONNECTIONS:
3461BS-1 (4-Digit 7-Segment Display):

    Segment Pins (A to G, DP):
        A -> GPIO 0 (Pico Pin 1)
        B -> GPIO 1 (Pico Pin 2)
        C -> GPIO 2 (Pico Pin 4)
        D -> GPIO 3 (Pico Pin 5)
        E -> GPIO 4 (Pico Pin 6)
        F -> GPIO 5 (Pico Pin 7)
        G -> GPIO 6 (Pico Pin 9)
        DP (Decimal Point) -> GPIO 7 (Pico Pin 10)

    Digit Control Pins (Common Anodes for D1, D2, D3, D4):
        D1 (First digit) -> GPIO 8 (Pico Pin 11)
        D2 (Second digit) -> GPIO 9 (Pico Pin 12)
        D3 (Third digit) -> GPIO 10 (Pico Pin 14)
        D4 (Fourth digit) -> GPIO 11 (Pico Pin 15)

HC-SR04 Ultrasonic Sensor:

    VCC -> 3.3V (Pico Pin 36) or 5V (Pico Pin 40) depending on your model.
    GND -> GND (Pico Pin 38 or any other GND pin).
    TRIG -> GPIO 15 (Pico Pin 20)
    ECHO -> GPIO 14 (Pico Pin 19)
