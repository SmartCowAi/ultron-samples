#!/usr/bin/env python3

"""Minimal example of toggling multiple lines."""

import gpiod
import time

from gpiod.line import Direction, Value


def toggle_value(value):
    if value == Value.INACTIVE:
        return Value.ACTIVE
    return Value.INACTIVE


def toggle_multiple_line_values(chip_path, line_values):
    value_str = {Value.ACTIVE: "Active", Value.INACTIVE: "Inactive"}

    request = gpiod.request_lines(
        chip_path,
        consumer="toggle-multiple-line-values",
        config={
            tuple(line_values.keys()): gpiod.LineSettings(direction=Direction.OUTPUT)
        },
        output_values=line_values,
    )

    while True:
        print(
            " ".join("{}={}".format(l, value_str[v]) for (l, v) in line_values.items())
        )
        time.sleep(1)
        for l, v in line_values.items():
            line_values[l] = toggle_value(v)
        request.set_values(line_values)


if __name__ == "__main__":
    """
    There are 8 relay lines available for each ND1 starting from 0-7 lines, here we set five of them to high and other three to low.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    """
    try:
        toggle_multiple_line_values(
            "/dev/Slot1-GPIOA", {0: Value.ACTIVE, 1: Value.ACTIVE, 2: Value.INACTIVE, 3: Value.ACTIVE, 4: Value.ACTIVE, 5: Value.INACTIVE, 6: Value.ACTIVE, 7: Value.INACTIVE}
        )
    except OSError as ex:
        print(ex, "\nCustomise the example configuration to suit your situation")
