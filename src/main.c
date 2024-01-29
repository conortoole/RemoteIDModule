#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/uart.h>

#include "BluetoothMod.h"
#include "GPSMod.h"

#define SLEEP_TIME_MS   500

uint8_t test[] = {        		
    't',                     
    'e',                     
    's',                     
    't'             
};

void Bluetooth_signal(struct Bluetooth* bluetooth) {
    int err = 0;

    printk("Starting Beacon\n");

    // Enable Bluetooth
    err = bt_enable(Bluetooth_ready(bluetooth, err));
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
    }
}

void main(void)
{
    printk("hello world\n");
    struct GPS gps;
    struct Bluetooth bluetooth;
    //bool devices_connected = true;

    // Initialize GPS module
    GPS_init(&gps);
    printk("gps configured\n");
    // Initialize Bluetooth module
    Bluetooth_init(&bluetooth);
    // Wait until both devices are connected
    // while (!devices_connected) {
    //     devices_connected = Bluetooth_is_connected(&bluetooth) && GPS_is_connected(&gps);
    //     printk("waiting for devices to connect\n");
    // }

    bool loop_sequence = true;

    //Main loop
    while (loop_sequence) {
        printk("top of loop\n");
        // Update GPS data
        //GPS_update_data(&gps);
        // Update Bluetooth packet data with GPS data
        Bluetooth_update_adata(&bluetooth, test); 
        printk("a Data updated\n");
        // Send Bluetooth signal
        //Bluetooth_signal(&bluetooth); //FAILS TO START ADVERTISING
        printk("end of loop\n");
        // Sleep for a specified time
        k_msleep(SLEEP_TIME_MS);
    }
}