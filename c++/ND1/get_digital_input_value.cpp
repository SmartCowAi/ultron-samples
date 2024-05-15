/* Minimal example of reading a single Digital Input line. */

#include <cstdlib>
#include <filesystem>
#include <gpiod.hpp>
#include <iostream>

namespace {

/*
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines, here we get value from zeroth line.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    Example configuration - customize to suit your situation
*/
const ::std::filesystem::path chip_path("/dev/Slot1-GPIOA");
const ::gpiod::line::offset line_offset = 12;

} /* namespace */

int main()
{
	auto request = ::gpiod::chip(chip_path)
			       .prepare_request()
			       .set_consumer("get-line-value")
			       .add_line_settings(
				       line_offset,
				       ::gpiod::line_settings().set_direction(
					       ::gpiod::line::direction::INPUT))
			       .do_request();

	::std::cout << line_offset << "="
		    << (request.get_value(line_offset) ==
					::gpiod::line::value::ACTIVE ?
				"Active" :
				"Inactive")
		    << ::std::endl;

	return EXIT_SUCCESS;
}
