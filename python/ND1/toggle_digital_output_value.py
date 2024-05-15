#!/usr/bin/env python3

"""Minimal example of toggling a single digital output line."""

import gpiod
import time

from gpiod.line import Direction, Value


def toggle_value(value):
    if value == Value.INACTIVE:
        return Value.ACTIVE
    return Value.INACTIVE


def toggle_line_value(chip_path, line_offset):
    value_str = {Value.ACTIVE: "Active", Value.INACTIVE: "Inactive"}
    value = Value.ACTIVE

    with gpiod.request_lines(
        chip_path,
        consumer="toggle-line-value",
        config={
            line_offset: gpiod.LineSettings(
                direction=Direction.OUTPUT, output_value=value
            )
        },
    ) as request:
        while True:
            print("{}={}".format(line_offset, value_str[value]))
            time.sleep(1)
            value = toggle_value(value)
            request.set_value(line_offset, value)


if __name__ == "__main__":
    """
    There are 4 Digital Output lines available for each ND1 starting from 8-11 lines, of which one line toggling is seen in the example.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    """
    try:
        toggle_line_value("/dev/Slot1-GPIOA", 8)
    except OSError as ex:
        print(ex, "\nCustomise the example configuration to suit your situation")
