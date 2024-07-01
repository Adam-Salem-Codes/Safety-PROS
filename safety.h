/**
 * @file safety.h
 * @brief Utility to help users check v5 devices using the PROS 4 api.
 * @author Adam Salem
 * @copyright Copyright (c) 2024 Adam Salem
 */

#pragma once

#include "api.h"

namespace safety
{
    /**
     * Checks if a device is plugged in at the given port.
     *
     * @param port The port number of the device.
     *
     * @return True if the device is plugged in and its type is not none or undefined, false otherwise.
     */
    bool isPluggedIn(int port)
    {
        return !(
            (pros::v5::Device::get_plugged_type(port) == pros::v5::DeviceType::none) ||
            (pros::v5::Device::get_plugged_type(port) == pros::v5::DeviceType::undefined));
    }

    /**
     * Checks if a device is a motor at the given port.
     *
     * @param port The port number of the device.
     *
     * @return True if the device is a motor, false otherwise.
     *
     * @throws None
     */
    bool isMotor(int port)
    {
        return pros::v5::Device::get_plugged_type(port) == pros::v5::DeviceType::motor;
    }

    /**
     * Checks if a device is an IMU at the given port.
     *
     * @param port The port number of the device.
     *
     * @return True if the device is an IMU, false otherwise.
     *
     * @throws None
     */
    bool isImu(int port)
    {
        return pros::v5::Device::get_plugged_type(port) == pros::v5::DeviceType::imu;
    }

    /**
     * Checks if a device is a radio at the given port.
     *
     * @param port The port number of the device.
     *
     * @return True if the device is a radio, false otherwise.
     *
     * @throws None
     */
    bool isRadio(int port)
    {
        return pros::v5::Device::get_plugged_type(port) == pros::v5::DeviceType::radio;
    }

    /**
     * Checks if a device is a rotation sensor at the given port.
     *
     * @param port The port number of the device.
     *
     * @return True if the device is a rotation sensor, false otherwise.
     *
     * @throws None
     */
    bool isRotation(int port)
    {
        return pros::v5::Device::get_plugged_type(port) == pros::v5::DeviceType::rotation;
    }

    /**
     * Checks the given MotorGroup for any ports that are not motors or are not plugged in.
     *
     * @param group The MotorGroup to check.
     *
     * @return A vector of ports that are not motors or are not plugged in.
     *
     * @throws None
     */
    std::vector<int> checkMotorGroup(pros::v5::MotorGroup &group)
    {
        std::vector<int> ports;
        for (int port : group.get_port_all())
        {
            if (!isMotor(port))
                ports.push_back(port);
            if (isPluggedIn(port))
                ports.push_back(port);
        }
        return ports;
    }

    /**
     * Checks if a device at the given port is an IMU and it is plugged in.
     *
     * @param port The port number of the device.
     *
     * @return True if the device is an IMU and is plugged in, false otherwise.
     *
     * @throws None
     */
    bool checkImu(int port)
    {
        return pros::v5::Device::get_plugged_type(port) == pros::v5::DeviceType::imu && isPluggedIn(port);
    }

    /**
     * A function that checks a list of devices for being unplugged and returns a vector of ports that are unplugged.
     *
     * @param devices The vector of devices to check.
     *
     * @return A vector of ports that are unplugged.
     *
     * @throws None
     */
    std::vector<int> checkDevices(std::vector<pros::v5::Device> devices)
    {
        std::vector<int> ports;
        for (pros::v5::Device device : devices)
        {
            if (!isPluggedIn(device.get_port()))
                ports.push_back(device.get_port());
        }
        return ports;
    }

    /**
     * @brief Converts a `pros::v5::DeviceType` enum value to its corresponding string representation.
     *
     * @param type The `pros::v5::DeviceType` enum value to convert.
     *
     * @return A string representation of the `pros::v5::DeviceType` enum value. Returns "none" for `pros::v5::DeviceType::none`, "undefined" for `pros::v5::DeviceType::undefined`, "motor" for `pros::v5::DeviceType::motor`, "rotation" for `pros::v5::DeviceType::rotation`, "imu" for `pros::v5::DeviceType::imu`, "radio" for `pros::v5::DeviceType::radio`, "distance" for `pros::v5::DeviceType::distance`, "vision" for `pros::v5::DeviceType::vision`, "adi" for `pros::v5::DeviceType::adi`, "optical" for `pros::v5::DeviceType::optical`, "gps" for `pros::v5::DeviceType::gps`, "serial" for `pros::v5::DeviceType::serial`, and "unknown" for any other value.
     *
     * @throws None
     */
    const char *deviceType_to_string(pros::v5::DeviceType type)
    {
        // Maps `pros::v5::DeviceType` enum values to their corresponding string representations.
        // Returns "none" for `pros::v5::DeviceType::none`, "undefined" for `pros::v5::DeviceType::undefined`, "motor" for `pros::v5::DeviceType::motor`, "rotation" for `pros::v5::DeviceType::rotation`, "imu" for `pros::v5::DeviceType::imu`, "radio" for `pros::v5::DeviceType::radio`, "distance" for `pros::v5::DeviceType::distance`, "vision" for `pros::v5::DeviceType::vision`, "adi" for `pros::v5::DeviceType::adi`, "optical" for `pros::v5::DeviceType::optical`, "gps" for `pros::v5::DeviceType::gps`, "serial" for `pros::v5::DeviceType::serial`, and "unknown" for any other value.
        switch (type)
        {
        case pros::v5::DeviceType::none:
            return "none";
        case pros::v5::DeviceType::undefined:
            return "undefined";
        case pros::v5::DeviceType::motor:
            return "motor";
        case pros::v5::DeviceType::rotation:
            return "rotation";
        case pros::v5::DeviceType::imu:
            return "imu";
        case pros::v5::DeviceType::radio:
            return "radio";
        case pros::v5::DeviceType::distance:
            return "distance";
        case pros::v5::DeviceType::vision:
            return "vision";
        case pros::v5::DeviceType::adi:
            return "adi";
        case pros::v5::DeviceType::optical:
            return "optical";
        case pros::v5::DeviceType::gps:
            return "gps";
        case pros::v5::DeviceType::serial:
            return "serial";
        default:
            return "unknown";
        }
    }

    /**
     * A function that generates a string of plugged-in devices with their types and ports.
     *
     * @param devices The vector of devices to check for being plugged in.
     *
     * @return A C-style string of plugged-in devices with their types and ports.
     *
     * @throws None
     */
    const char *print_unplugged_devices(std::vector<pros::v5::Device> devices)
    {
        std::string output;
        for (pros::v5::Device device : devices)
        {
            if (isPluggedIn(device.get_port()))
                output +=
                    std::string(deviceType_to_string(pros::v5::Device::get_plugged_type(device.get_port()))) + ": " + std::to_string(device.get_port()) + ",\n";
        }
        return output.c_str();
    }

    /**
     * A function that continuously checks a list of devices for being unplugged and prints a message if a device is unplugged.
     *  NOTE: It stops checking for devices once a one device is unplugged. You will have to restart the program to reinitialize.
     * 
     * \example
     * ```cpp
     * Task t(safety::task_check_devices(master, { devices } ));
     * ```
     *
     * @param master The controller object used to rumble and print messages.
     * @param devices The vector of devices to check for being plugged in.
     *
     * @return None
     *
     * @throws None
     */
    int task_check_devices(pros::v5::Controller master, std::vector<pros::v5::Device> devices)
    {
        // Loop indefinitely
        while (true)
        {
            // Loop through each device in the vector
            for (pros::v5::Device &device : devices)
            {
                // Check if the device is unplugged
                if (!isPluggedIn(device.get_port()))
                {
                    // Rumble the controller and print a message
                    master.rumble("---");
                    master.print(0, 0, "DEVICE UNPLUGGED!!!");

                    return 1; // Return 1 to stop the task
                }
            }
            // Delay for 500ms before checking again
            pros::delay(500);
        }
    }

    
} // namespace

// Written by: Adam Salem for PROS 4.0
