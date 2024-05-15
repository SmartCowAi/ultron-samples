/* Minimal example of toggling a single Digital Output line. */

#include <cstdlib>
#include <chrono>
#include <filesystem>
#include <gpiod.hpp>
#include <iostream>
#include <thread>

namespace {

/*
    There are 8 relay lines available for each ND1 starting from 0-7 lines, of which one line toggling is seen in the example for every 5 seconds.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    Example configuration - customize to suit your situation.
*/
const ::std::filesystem::path chip_path("/dev/Slot1-GPIOA");
const ::gpiod::line::offset line_offset = 0;

::gpiod::line::value toggle_value(::gpiod::line::value v)
{
	return (v == ::gpiod::line::value::ACTIVE) ?
		       ::gpiod::line::value::INACTIVE :
		       ::gpiod::line::value::ACTIVE;
}

} /* namespace */

int main()
{
	::gpiod::line::value value = ::gpiod::line::value::ACTIVE;

	auto request =
		::gpiod::chip(chip_path)
			.prepare_request()
			.set_consumer("toggle-line-value")
			.add_line_settings(
				line_offset,
				::gpiod::line_settings().set_direction(
					::gpiod::line::direction::OUTPUT))
			.do_request();

	for (;;) {
		::std::cout << line_offset << "=" << value << ::std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(5));
		value = toggle_value(value);
		request.set_value(line_offset, value);
	}
}
