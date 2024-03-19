#include <zephyr.h>
#include <bluetooth/hci.h>
#include <bluetooth/bluetooth.h>
#include <sys/printk.h>
#include <bluetooth/conn.h>
#include <bluetooth/gap.h>

// Define the advertising data
static uint8_t mfg_data[] = {
    /* Initial advertising data */
    '!', '!', '!', '!', '!', '-', '0', 
    '!', '!', '!', '!', '!', '!', '!',
    '!', '!', '!', '!', '!', '!', '!',
    '!', '!', '!', '!', '!', '!', '!',
    '!'
};

static const struct bt_data ad[] = {
    BT_DATA(BT_DATA_MANUFACTURER_DATA, mfg_data, sizeof(mfg_data)),
};
    
static uint8_t counter = 0;
static uint8_t test[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

// Function to update advertising data
void update_advertising_data(void) {
    // Update mfg_data with new data
    // This is just an example. You should implement the logic to update the data.
    mfg_data[6] = test[counter];
    counter++; 
    counter = counter % 26;

    printk("Advertising data updated: %s\n", mfg_data);

    // Update the advertising data
    bt_le_adv_update_data(ad, ARRAY_SIZE(ad), NULL, 0);
}

void main(void) {
    int err;
    struct bt_le_adv_param adv_param = {
        .options = BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_USE_NAME,
        .interval_min = BT_GAP_ADV_FAST_INT_MIN_2,
        .interval_max = BT_GAP_ADV_FAST_INT_MAX_2,
    };

    printk("Starting Bluetooth Beacon...\n");

    // Enable Bluetooth
    err = bt_enable(NULL);
    if (err) {
        printk("Bluetooth initialization failed (%d)\n", err);
        return;
    }

    printk("Bluetooth enabled.\n");

    // Set the device name
    err = bt_set_name("MyDeviceName");
    if (err) {
        printk("Setting device name failed (%d)\n", err);
        return;
    }

    printk("Device name set to '%s'\n", bt_get_name());

    // Start advertising
    err = bt_le_adv_start(&adv_param, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Failed to start advertising (%d)\n", err);
        return;
    }

    printk("Advertising started with device name '%s'\n", bt_get_name());

    // Call update_advertising_data() periodically
    while (1) {
        k_sleep(K_MSEC(5)); // Sleep for  seconds
        update_advertising_data(); // Update advertising data
    }
}
