# ND1

The module consists of the following controls and there corresponding lines, chips are also mentioned:
| Control Type | \#Numbers | Chip | Board Numbering |
| ------------ | ------------------ | ---- | ---- |
| Relays | 1-8 | GPIOA | 0-7 |
| Digital Outputs | 0-3 | GPIOA | 8-11 |
| Digital Inputs | 0-3 | GPIOA | 12-15 |
| Digital Inputs | 4-7 | GPIOB | 0-3 |
| Analog Inputs | 0-3 | ADC | 4-7 |

This folder contains samples to access and set/get the values of the controls.

## Build

To build these samples run `make` in this folder and binaries are built separately.

## Usage

All the samples are by default set to access the ND1 with address `1`. The modules are loaded on the device by `/dev/Slot<address>-<chip>` this format. `Chip` can be `GPIOA` or `GPIOB` and the `address` is the one displayed on the OLED of the module.
