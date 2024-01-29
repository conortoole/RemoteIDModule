#include "GPSMod.h"

// Define a structure to hold UART configuration parameters
struct uart_config uart_cfg = {
    .baudrate = 115200,
    .data_bits = UART_CFG_DATA_BITS_8,
    .parity = UART_CFG_PARITY_NONE,
    .stop_bits = UART_CFG_STOP_BITS_1,
};

// void GPS_connect(struct GPS *gps) {
    
// }

// bool GPS_is_connected(struct GPS *gps) {
//     return gps->connected;
// }

// Initialize the GPS module
void GPS_init(struct GPS *gps){
    // Get the UART device binding for UART_0
    printk("begin gps initialization\n");
    gps->uart_dev = device_get_binding("UART_0");
    printk("device get binding success\n");
    
    if (!gps->uart_dev) {
        printk("Cannot find UART_1!\n");
    }

    // Configure the UART with the defined parameters
    uart_configure(gps->uart_dev, &uart_cfg);
    printk("gps configured\n");

    gps->gps_data_index = 0;
    gps->longitude = 0;
    gps->latitude = 0;
}

// Update the GPS data
// void GPS_update_data(struct GPS *gps) {
//     uint8_t rx_data;

//     // Poll for incoming data from the UART
//     if (uart_poll_in(gps->uart_dev, &rx_data) == 0){
//         if (rx_data == '\n') {
//             // If a newline character is received, terminate the GPS data string and print it
//             gps->gps_data[gps->gps_data_index] = '\0';
//             printk("GPS Data: %s\n", gps->gps_data);
//             gps->gps_data_index = 0;
//         } else {
//             // If a character other than newline is received, store it in the GPS data buffer
//             if (gps->gps_data_index < 256 - 1) {
//                 gps->gps_data[gps->gps_data_index++] = rx_data;
//             } else {
//                 // If the GPS data buffer is full, print an overflow message and reset the buffer
//                 printk("GPS Data Buffer Overflow\n");
//                 gps->gps_data_index = 0;
//             }
//         }
//     }
// }

// Get the GPS data
uint8_t* GPS_get_data(struct GPS *gps) {
    return gps->gps_data;
}
