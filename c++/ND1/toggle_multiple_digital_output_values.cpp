/* Minimal example of toggling multiple Digital Output lines. */

#include <cstdlib>
#include <gpiod.hpp>
#include <iostream>
#include <thread>

namespace {

/*
    There are 4 Digital Output lines available for each ND1 starting from 8-11 lines, here we toggle all 4 outputs every 5 seconds.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    Example configuration - customize to suit your situation
*/
const ::std::filesystem::path chip_path("/dev/Slot1-GPIOA");
const ::gpiod::line::offsets line_offsets = { 8, 9, 10, 11 };

::gpiod::line::value toggle_value(::gpiod::line::value v)
{
	return (v == ::gpiod::line::value::ACTIVE) ?
		       ::gpiod::line::value::INACTIVE :
		       ::gpiod::line::value::ACTIVE;
}

void toggle_values(::gpiod::line::values &values)
{
	for (size_t i = 0; i < values.size(); i++)
		values[i] = toggle_value(values[i]);
}

void print_values(::gpiod::line::offsets const &offsets,
		  ::gpiod::line::values const &values)
{
	for (size_t i = 0; i < offsets.size(); i++)
		::std::cout << offsets[i] << "=" << values[i] << ' ';
	::std::cout << ::std::endl;
}

} /* namespace */

int main()
{
	::gpiod::line::values values = { ::gpiod::line::value::ACTIVE,
					 ::gpiod::line::value::ACTIVE,
					 ::gpiod::line::value::INACTIVE,
					 ::gpiod::line::value::INACTIVE };

	auto request =
		::gpiod::chip(chip_path)
			.prepare_request()
			.set_consumer("toggle-multiple-line-values")
			.add_line_settings(
				line_offsets,
				::gpiod::line_settings().set_direction(
					::gpiod::line::direction::OUTPUT))
			.set_output_values(values)
			.do_request();

	for (;;) {
		print_values(line_offsets, values);
		std::this_thread::sleep_for(std::chrono::seconds(5));
		toggle_values(values);
		request.set_values(line_offsets, values);
	}
}
