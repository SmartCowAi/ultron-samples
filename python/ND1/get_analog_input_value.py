#!/usr/bin/env python3

"""Minimal example to get analog input value of a single line."""

import time

def read_value_from_analog_input(file_path, frequency, num_samples):
    for i in range(num_samples):
        try:
            with open(file_path, 'r') as file:
                raw_value = file.read()
                # 409.6 is the scaling ratio of the ADC
                processed_value = float(raw_value.strip())/409.6
                print(f'Sample {i} --> {processed_value}V')
        except FileNotFoundError:
            print(f"Device '{file_path}' not found.")
        except Exception as e:
            print(f"An error occurred: {e}")

        time.sleep(frequency)

if __name__ == "__main__":
    """
    There are 4 Analog Input lines available for each ND1 starting from 4-7 on GPIOB lines, here we get value from zeroth line.
    The raw value can be read from `/dev/Slot<address>-ADC/in_voltage<channel>_mode_7_ADC_raw`.
    In current example ND1 module in Slot1 is addressed, should be changed according to the address in which they are actually connected.
    The below call to the method reads channel 0 of the Slot1 ND1 analog input 10 times for every 5 seconds.
    """

    read_value_from_analog_input('/dev/Slot1-ADC/in_voltage4_mode_7_ADC_raw', 5, 10)
