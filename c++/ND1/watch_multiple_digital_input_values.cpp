/* Minimal example of watching for edges on multiple Digital Input lines. */

#include <cstdlib>
#include <gpiod.hpp>
#include <iomanip>
#include <iostream>

namespace {

/*
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines, watching the values of the first four lines.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    Example configuration - customize to suit your situation
*/
const ::std::filesystem::path chip_path("/dev/Slot1-GPIOA");
const ::gpiod::line::offsets line_offsets = { 12, 13, 14, 15 };

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
			.set_consumer("watch-multiple-line-values")
			.add_line_settings(
				line_offsets,
				::gpiod::line_settings()
					.set_direction(
						::gpiod::line::direction::INPUT)
					.set_edge_detection(
						::gpiod::line::edge::BOTH))
			.do_request();

	::gpiod::edge_event_buffer buffer;

	for (;;) {
		/* Blocks until at leat one event available */
		request.read_edge_events(buffer);

		for (const auto &event : buffer)
			::std::cout << "offset: " << event.line_offset()
				    << "  type: " << ::std::setw(7)
				    << ::std::left << edge_event_type_str(event)
				    << "  event #" << event.global_seqno()
				    << "  line event #" << event.line_seqno()
				    << ::std::endl;
	}
}
