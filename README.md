# VCP Graphical Central
A graphical central app for interacting with the VCP volume control service and its included services (AICS and VOCS).

**Note:** If you haven't started a Zephyr project yet, first refer to the [Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) and install all dependencies. It is recommended to follow the path that involves using a virtual Python environment.

# Hardware requirement
To run this app, an ‘nRF5340DK’ board and an ‘adafruit_2_8_tft_touch_v2’ LCD display module are needed.

# For development
For developers of the application, first do a fork of the repo. Then do the following:

Make a local workspace folder (to hold the repo, zephyr and west modules):

```
mkdir my-workspace
cd my-workspace
```

Clone the repo:

```
git clone git@github.com:<your handle>/standalone-broadcast-assistant.git
```

Initialize west and update dependencies:

```
west init -l vcp-graphical-central
west update
```

# For normal use (non-development)
This repo contains a stand alone Zephyr application that can be fetched and initialized like this:

```
west init -m https://github.com/astraeuslabs/vcp-graphical-central --mr main my-workspace
```

Then use west to fetch dependencies:

```
cd my-workspace
west update
```



# Build and flash
Go to the repo folder:

```
cd standalone-broadcast-assistant
```

## Build

### nRF5340 DK board
The nRF5340 DK has two cores - one for the application and one dedicated for the network (bluetooth controller).
The bluetooth controller can be builded from zephyr/samples/bluetooth/hci_ipc:
```
west build -b nrf5340dk/nrf5340/cpunet  -d build/hci_ipc ../zephyr/samples/bluetooth/hci_ipc --pristine -- -DCONF_FILE=nrf5340_cpunet_iso-bt_ll_sw_split.conf
```
### Application
```
west build -b nrf5340dk/nrf5340/cpuapp -d build/app app --pristine -- -DSHIELD=adafruit_2_8_tft_touch_v2
```

## Flash

### nRF5340 DK board
Clear all mem for the two cores with the recover command:
```
nrfjprog --recover --coprocessor CP_NETWORK
nrfjprog --recover
```
And flash with the west command:
```
west flash -r nrfjprog -d build/hci_ipc
```
### Application
```
west flash -r nrfjprog -d build/app
```