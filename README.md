# arduino-pico-serialmic
Serial microphone using arduino-pico on an RP2040 and INMP441 MEMS mic

## Wiring
Current implementation uses the following wiring, so it fit's nicely on top of a RP2040-zero:
| RP2040 | INMP441 |
|--------|---------|
| 1      | L/R     |
| 3      | SCK     |
| 4      | WS      |
| GND    | GND     |
| 3V3    | VDD     |
| 29     | SD      |

Connect RP2040 pin 2 and 4 together, so the mic connections align nicely with the zero (WS connects to both RP2040 pin 2 and 4).

## Run
The sketch outputs its 24 bits samples in 3 bytes, in hex format over the serial port. Using `xxd` this can be piped to ALSA:
```
$ cat /dev/ttyACM0 | xxd -r -p | aplay -r16000 -c1 -fS24_3BE
```
