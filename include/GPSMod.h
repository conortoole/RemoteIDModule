#ifndef GPS_H
#define GPS_H

#include <zephyr.h>                 // Include the Zephyr RTOS header file
#include <device.h>                 // Include the device header file
#include <devicetree.h>             // Include the devicetree header file
#include <drivers/uart.h>           // Include the UART driver header file

struct GPS {
    const struct device *uart_dev;  // Pointer to the UART device structure
    uint8_t gps_data[256];          // Buffer to store GPS data
    int gps_data_index;             // Index to keep track of the GPS data buffer
    int longitude;                  // Variable to store the longitude value
    int latitude;                   // Variable to store the latitude value
    bool connected;                 // Flag to indicate if GPS is connected
};

void GPS_init(struct GPS *gps);     // Function to initialize the GPS module

void GPS_update_data(struct GPS *gps);   // Function to update the GPS data

uint8_t* GPS_get_data(struct GPS *gps);  // Function to get the GPS data

#endif // GPS_H
