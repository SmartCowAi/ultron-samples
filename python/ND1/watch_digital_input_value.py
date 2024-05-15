#!/usr/bin/env python3

"""Minimal example of watching for edges on a single digital input line."""

import gpiod

from datetime import timedelta
from gpiod.line import Bias, Edge


def edge_type_str(event):
    if event.event_type is event.Type.RISING_EDGE:
        return "Rising"
    if event.event_type is event.Type.FALLING_EDGE:
        return "Falling"
    return "Unknown"


def watch_line_value(chip_path, line_offset):
    # Assume a button connecting the pin to ground,
    # so pull it up and provide some debounce.
    with gpiod.request_lines(
        chip_path,
        consumer="watch-line-value",
        config={
            line_offset: gpiod.LineSettings(
                edge_detection=Edge.BOTH,
                bias=Bias.PULL_UP
            )
        },
    ) as request:
        while True:
            # Blocks until at least one event is available
            for event in request.read_edge_events():
                print(
                    "line: {}  type: {:<7}  event #{}".format(
                        event.line_offset, edge_type_str(event), event.line_seqno
                    )
                )


if __name__ == "__main__":
    """
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines, here we watch value change on zeroth line.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    """
    try:
        watch_line_value("/dev/Slot1-GPIOA", 12)
    except OSError as ex:
        print(ex, "\nCustomise the example configuration to suit your situation")
