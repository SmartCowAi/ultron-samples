/* Minimal example of watching for rising edges on a single Digital Input line. */

#include <cstdlib>
#include <filesystem>
#include <gpiod.hpp>
#include <iomanip>
#include <iostream>

namespace {

/*
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines, here we watch rising on zeroth line.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    Example configuration - customize to suit your situation.
*/
const ::std::filesystem::path chip_path("/dev/Slot1-GPIOA");
const ::gpiod::line::offset line_offset = 12;

const char *edge_event_type_str(const ::gpiod::edge_event &event)
{
	switch (event.type()) {
	case ::gpiod::edge_event::event_type::RISING_EDGE:
		return "Rising";
	case ::gpiod::edge_event::event_type::FALLING_EDGE:
		return "Falling";
	default:
		return "Unknown";
	}
}

} /* namespace */

int main()
{
	auto request =
		::gpiod::chip(chip_path)
			.prepare_request()
			.set_consumer("watch-line-value")
			.add_line_settings(
				line_offset,
				::gpiod::line_settings()
					.set_direction(
						::gpiod::line::direction::INPUT)
					.set_edge_detection(
						::gpiod::line::edge::RISING)
			)
			.do_request();

	/*
	 * A larger buffer is an optimisation for reading bursts of events from
	 * the kernel, but that is not necessary in this case, so 1 is fine.
	 */
	::gpiod::edge_event_buffer buffer(1);

	for (;;) {
		/* Blocks until at least one event is available. */
		request.read_edge_events(buffer);

		for (const auto &event : buffer)
			::std::cout << "line: " << event.line_offset()
				    << "  type: " << ::std::setw(7) << ::std::left << edge_event_type_str(event)
				    << "  event #" << event.line_seqno()
				    << ::std::endl;
	}
}
