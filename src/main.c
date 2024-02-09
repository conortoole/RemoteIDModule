#include <zephyr.h>
#include <bluetooth/hci.h>
#include <bluetooth/bluetooth.h>
#include <sys/printk.h>
#include <bluetooth/conn.h>

// Define the advertising data
static uint8_t mfg_data[] = { 0xff, 0xff, 0x00 };

static const struct bt_data ad[] = {
	BT_DATA(BT_DATA_MANUFACTURER_DATA, mfg_data, 3),
};

void main(void)
{
    int err;
    struct bt_le_ext_adv *adv;
    struct bt_le_adv_param adv_param;
    struct bt_le_ext_adv_start_param adv_start_param;

    printk("Starting Bluetooth Beacon...\n");

    // Initialize advertising parameters
    memset(&adv_start_param, 0, sizeof(adv_start_param));
    adv_start_param.timeout = 0; // No timeout
    adv_start_param.num_events = 0; // Advertise indefinitely

    // Create the extended advertiser instance
    err = bt_le_ext_adv_create(&adv_param, NULL, &adv);
    if (err) {
        printk("Advertiser creation failed (%d)\n", err);
        return;
    }

    // Set the advertising data
    err = bt_le_ext_adv_set_data(adv, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Failed to set advertising data (%d)\n", err);
        return;
    }

    // Start advertising
    err = bt_le_ext_adv_start(adv, &adv_start_param);
    if (err) {
        printk("Failed to start advertising (%d)\n", err);
        return;
    }

    printk("Advertising started.\n");
};