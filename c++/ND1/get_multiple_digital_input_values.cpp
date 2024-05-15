/* Minimal example of reading multiple Digital Input lines. */

#include <cstdlib>
#include <gpiod.hpp>
#include <iostream>

namespace {

/*
    There are 8 Digital Input lines available for each ND1 starting from 12-15 on GPIOA and 0-3 on GPIOB lines.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    Example configuration - customize to suit your situation
*/
const ::std::filesystem::path chip_path_1("/dev/Slot1-GPIOA");
const ::gpiod::line::offsets line_offsets_1 = { 12, 13, 14, 15 };
const ::std::filesystem::path chip_path_2("/dev/Slot1-GPIOB");
const ::gpiod::line::offsets line_offsets_2 = { 0, 1, 2, 3 };

} /* namespace */

int main()
{
	auto request_1 = ::gpiod::chip(chip_path_1)
			       .prepare_request()
			       .set_consumer("get-multiple-line-values")
			       .add_line_settings(
				       line_offsets_1,
				       ::gpiod::line_settings().set_direction(
					       ::gpiod::line::direction::INPUT))
			       .do_request();

	auto values_1 = request_1.get_values();

    auto request_2 = ::gpiod::chip(chip_path_2)
			       .prepare_request()
			       .set_consumer("get-multiple-line-values")
			       .add_line_settings(
				       line_offsets_2,
				       ::gpiod::line_settings().set_direction(
					       ::gpiod::line::direction::INPUT))
			       .do_request();

	auto values_2 = request_2.get_values();

	for (size_t i = 0; i < line_offsets_1.size(); i++)
		::std::cout << line_offsets_1[i] << "="
			    << (values_1[i] == ::gpiod::line::value::ACTIVE ?
					"Active" :
					"Inactive")
			    << ' ';
	::std::cout << ::std::endl;

    for (size_t i = 0; i < line_offsets_2.size(); i++)
		::std::cout << line_offsets_2[i] << "="
			    << (values_2[i] == ::gpiod::line::value::ACTIVE ?
					"Active" :
					"Inactive")
			    << ' ';
	::std::cout << ::std::endl;

	return EXIT_SUCCESS;
}
