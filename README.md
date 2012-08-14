# Switch

Switch is a simple TCP server that runs on the Arduino with an Ethernet shield.
It listens on port 23 for commands like `output 1 1`, which turns on a pin on 
the Arduino. Connect a relay on the pin and use it to control devices like lights.

## Getting Started

- Edit switch.c and enter the MAC address of your Ethernet Shield.
`byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };`
- Compile and write switch.c to your Arduino.
- Connect an LED to output 1. (Pin 8)
- `echo 'output 1 1' | nc 10.5.1.88 23`
- `echo 'output 1 0' | nc 10.5.1.88 23`

