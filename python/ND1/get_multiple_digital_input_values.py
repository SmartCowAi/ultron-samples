#!/usr/bin/env python3

"""Minimal example of reading multiple digital input lines."""

import gpiod

from gpiod.line import Direction


def get_multiple_line_values(chip_path, line_offsets):
    with gpiod.request_lines(
        chip_path,
        consumer="get-multiple-line-values",
        config={tuple(line_offsets): gpiod.LineSettings(direction=Direction.INPUT)},
    ) as request:
        vals = request.get_values()

        for offset, val in zip(line_offsets, vals):
            print("{}={} ".format(offset, val), end="")
        print()


if __name__ == "__main__":
    """
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    """
    try:
        get_multiple_line_values("/dev/Slot1-GPIOA", [12, 13, 14, 15])
        get_multiple_line_values("/dev/Slot1-GPIOB", [0, 1, 2, 3])
    except OSError as ex:
        print(ex, "\nCustomise the example configuration to suit your situation")
