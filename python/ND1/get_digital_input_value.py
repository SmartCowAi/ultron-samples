#!/usr/bin/env python3

"""Minimal example of reading a single digital input line."""

import gpiod

from gpiod.line import Direction


def get_line_value(chip_path, line_offset):
    with gpiod.request_lines(
        chip_path,
        consumer="get-line-value",
        config={line_offset: gpiod.LineSettings(direction=Direction.INPUT)},
    ) as request:
        value = request.get_value(line_offset)
        print("{}={}".format(line_offset, value))


if __name__ == "__main__":
    """
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines, here we get value from zeroth line.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    """
    try:
        get_line_value("/dev/Slot1-GPIOA", 12)
    except OSError as ex:
        print(ex, "\nCustomise the example configuration to suit your situation")
