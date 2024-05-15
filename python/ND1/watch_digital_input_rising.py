#!/usr/bin/env python3

"""Minimal example of watching for rising edges on a single digital input line."""

import gpiod

from gpiod.line import Edge


def watch_line_rising(chip_path, line_offset):
    with gpiod.request_lines(
        chip_path,
        consumer="watch-line-rising",
        config={line_offset: gpiod.LineSettings(edge_detection=Edge.RISING)},
    ) as request:
        while True:
            # Blocks until at least one event is available
            for event in request.read_edge_events():
                print(
                    "line: {}  type: Rising   event #{}".format(
                        event.line_offset, event.line_seqno
                    )
                )


if __name__ == "__main__":
    """
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines, here we watch rising on zeroth line.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    """
    try:
        watch_line_rising("/dev/Slot1-GPIOA", 12)
    except OSError as ex:
        print(ex, "\nCustomise the example configuration to suit your situation")
