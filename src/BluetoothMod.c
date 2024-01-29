#include "BluetoothMod.h"

// Structure to hold Bluetooth data
struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),    //0, 1
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0xaa, 0xfe),      //2, 3, 4
	BT_DATA_BYTES(BT_DATA_SVC_DATA16,              		//5
		      0xfe,                    //6
		      0x10,                    //7
		      0x00,                    //8
		      'S',                     //9
		      't',                     //10
			  'a',                     //11
			  'r',                     //12
			  't',                     //13
			  'i',                     //14
			  'n',                     //15
			  'g',                     //16
			  '-',                     //17
			  'R',                     //18
			  'e',                     //19
			  'm',                     //20
			  'o',                     //21
			  't',                     //22
			  'e',                     //23
			  '-',                     //24
			  'I',                     //25
			  'D',                     //26
			  '-',                     //27
			  'B',                     //28
			  'e',                     //29
			  'a',                     //30
			  'c',                     //31
			  'o',                     //32
			  'n'	                   //33
              )
};

// Structure to hold Bluetooth service data
static const struct bt_data sd[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

// void Bluetooth_connect(struct Bluetooth* bluetooth) {
	
// }

// bool Bluetooth_is_connected(struct Bluetooth* bluetooth) {
// 	return bluetooth->connected;
// }

void Bluetooth_set_device_name(struct Bluetooth* bluetooth) {
	char name[30] = DEVICE_NAME;
	strcpy(bluetooth->DeviceName, name);
}

void Bluetooth_set_adata(struct Bluetooth* bluetooth) {
	bluetooth->AData = ad;
}

void Bluetooth_set_sdata(struct Bluetooth* bluetooth) {
	bluetooth->SData = sd;
}

void Bluetooth_init(struct Bluetooth* bluetooth) {
	printk("beginning Bluetooth initialization\n");
	Bluetooth_set_device_name(bluetooth);
	Bluetooth_set_adata(bluetooth);
	Bluetooth_set_sdata(bluetooth);
	bluetooth->connected = false;
	printk("bluetooth completed\n");
}

void Bluetooth_update_adata(struct Bluetooth* bluetooth, uint8_t* newData) { //new data is 29 bytes long
	memcpy(ad[2].data, newData, 29);
	//printk()
}	

bt_ready_cb_t Bluetooth_ready(struct Bluetooth* bluetooth, int err) {
	char addr_s[30];
	bt_addr_le_t addr = {0};
	bt_ready_cb_t ready = 0;
	size_t count = 1;

	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		//return 1;
	}

	printk("Bluetooth initialized\n");

	err = bt_le_adv_start(BT_LE_ADV_NCONN_IDENTITY, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return ready;
	}

	bt_id_get(&addr, &count);
	bt_addr_le_to_str(&addr, addr_s, sizeof(addr_s));

	printk("Beacon started, advertising as %s\n", addr_s);

	return ready;
}
