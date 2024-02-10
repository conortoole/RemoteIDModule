#include <zephyr.h>
#include <bluetooth/hci.h>
#include <bluetooth/bluetooth.h>
#include <sys/printk.h>
#include <bluetooth/conn.h>

// Define the advertising data
static uint8_t mfg_data[] = {
    /* Drone ID (Remote ID-compliant serial number) */
    'D', 'R', 'O', 'N', 'E', '_', 'I', 'D', '=', '1', '2', '3', '4', '5',
    /* Drone location and altitude */
    'L', 'O', 'C', '=', '3', '7', '.', '1', '2', '3', '4', '5', ',', 'A',
};

static const struct bt_data ad[] = {
    BT_DATA(BT_DATA_MANUFACTURER_DATA, mfg_data, sizeof(mfg_data)),
};

void main(void)
{
    int err;
    struct bt_le_ext_adv *adv;
    struct bt_le_adv_param adv_param;
    struct bt_le_ext_adv_start_param adv_start_param;

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


    // Initialize advertising parameters
    memset(&adv_param,  0, sizeof(adv_param));
    adv_param.interval_min = BT_GAP_ADV_FAST_INT_MIN_2; // Minimum advertising interval (for fast connection)
    adv_param.interval_max = BT_GAP_ADV_FAST_INT_MAX_2; // Maximum advertising interval (for fast connection)
    adv_param.options = BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_ONE_TIME; // Options for advertising
    adv_param.options = BT_LE_ADV_OPT_USE_NAME; // Include device name in advertising data

    printk("Advertising parameters initialized.\n");

    // Create the extended advertiser instance
    printk("adv_param: interval_min=%u, interval_max=%u, options=%u\n",
        adv_param.interval_min, adv_param.interval_max, adv_param.options);

    printk("adv: %p\n", adv);

    err = bt_le_ext_adv_create(&adv_param, NULL, &adv);
    if (err) {
        printk("Advertiser creation failed (%d)\n", err);
        return;
    }

    printk("Advertiser created.\n");

    // Set the advertising data
    err = bt_le_ext_adv_set_data(adv, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Failed to set advertising data (%d)\n", err);
        return;
    }

    printk("Advertising data set.\n");

    // Start advertising
    err = bt_le_ext_adv_start(adv, &adv_start_param);
    if (err) {
        printk("Failed to start advertising (%d)\n", err);
        return;
    }

    printk("Advertising started with device name '%s'\n", bt_get_name());

};