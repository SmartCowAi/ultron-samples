#!/usr/bin/env python3

"""Minimal example of watching for edges on multiple digital input lines."""

import gpiod

from gpiod.line import Edge


def edge_type_str(event):
    if event.event_type is event.Type.RISING_EDGE:
        return "Rising"
    if event.event_type is event.Type.FALLING_EDGE:
        return "Falling"
    return "Unknown"


def watch_multiple_line_values(chip_path, line_offsets):
    with gpiod.request_lines(
        chip_path,
        consumer="watch-multiple-line-values",
        config={tuple(line_offsets): gpiod.LineSettings(edge_detection=Edge.BOTH)},
    ) as request:
        while True:
            for event in request.read_edge_events():
                print(
                    "offset: {}  type: {:<7}  event #{}  line event #{}".format(
                        event.line_offset,
                        edge_type_str(event),
                        event.global_seqno,
                        event.line_seqno,
                    )
                )


if __name__ == "__main__":
    """
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines, watching the values of the first four lines.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    """
    try:
        watch_multiple_line_values("/dev/Slot1-GPIOA", [12, 13, 14, 15])
    except OSError as ex:
        print(ex, "\nCustomise the example configuration to suit your situation")
