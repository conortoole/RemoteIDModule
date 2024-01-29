// BluetoothMod.h

#ifndef BLUETOOTHMOD_H
#define BLUETOOTHMOD_H

#include <zephyr/types.h>
#include <stddef.h>
#include <sys/util.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <zephyr.h>                 // Include the Zephyr RTOS header file
// #include <device.h>                 // Include the device header file
// #include <devicetree.h>             // Include the devicetree header file


#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

// Structure to hold Bluetooth information
struct Bluetooth {
    char DeviceName[30];
    struct bt_data *AData;
    const struct bt_data *SData;
	bool connected;
};

// Function to connect to Bluetooth device
void Bluetooth_connect(struct Bluetooth* bluetooth);

// Function to check if Bluetooth device is connected
bool Bluetooth_is_connected(struct Bluetooth* bluetooth);

// Function to set the device name in Bluetooth structure
void Bluetooth_set_device_name(struct Bluetooth* bluetooth);

// Function to set the advertising data in Bluetooth structure
void Bluetooth_set_adata(struct Bluetooth* bluetooth);

// Function to set the service data in Bluetooth structure
void Bluetooth_set_sdata(struct Bluetooth* bluetooth);

// Function to initialize Bluetooth structure
void Bluetooth_init(struct Bluetooth* bluetooth);

// Function to update the advertising data in Bluetooth structure
void Bluetooth_update_adata(struct Bluetooth* bluetooth, uint8_t* newData);

// Callback function to handle Bluetooth readiness
bt_ready_cb_t Bluetooth_ready(struct Bluetooth* bluetooth, int err);

#endif //BLUETOOTHMOD_H