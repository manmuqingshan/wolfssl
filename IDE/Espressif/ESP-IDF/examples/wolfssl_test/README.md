# wolfSSL Crypt Test Example

This is the ESP32 Version of the [wolfSSL wolfcrypt test application](https://github.com/wolfSSL/wolfssl/tree/master/wolfcrypt/test).

For general information on [wolfSSL examples for Espressif](../README.md), see the
[README](https://github.com/wolfSSL/wolfssl/blob/master/IDE/Espressif/ESP-IDF/README.md) file.

## ESP Registry

The easiest way to get started with wolfSSL is by using the
[ESP Registry](https://www.wolfssl.com/wolfssl-now-available-in-espressif-component-registry/) examples.

```bash
. ~/esp/esp-idf/export.sh
idf.py create-project-from-example "wolfssl/wolfssl^5.6.0-stable:wolfssl_test"
cd wolfssl_benchmark
idf.py -b 115200 flash monitor
```

## VisualGDB

Open the VisualGDB Visual Studio Project file in the [VisualGDB directory](./VisualGDB/README.md) and click the "Start" button.
No wolfSSL setup is needed. You may need to adjust your specific COM port. The default is `COM20`.

## ESP-IDF Commandline (version 4.4 or greater for the ESP32)

1. `idf.py menuconfig` to configure the program.
    1-1. Example Configuration ->

    There are no parametric arguments. See [wolfcrypt/test](https://github.com/wolfSSL/wolfssl/tree/master/wolfcrypt/test).
    All features enabled in the `user_settings.h` will be tested.

When you want to run the test program

1. `idf.py -p <PORT> flash` to compile and load the firmware
2. `idf.py monitor` to see the message

See the README.md file in the upper level 'examples' directory for more information about examples.

Reminder than when building on WSL in `/mnt/c` there will be a noticeable performance degradation at compile time. Using `~/` will be faster at the cost of shared filesystems.

Example build on WSL, assuming `git clone` from `c:\workspace`:

```bash
WRK_IDF_PATH=/mnt/c/SysGCC/esp32/esp-idf/v5.2
# WRK_IDF_PATH=/mnt/c/SysGCC/esp32/esp-idf/master

echo "Run export.sh from ${WRK_IDF_PATH}"
. ${WRK_IDF_PATH}/export.sh

# switch to test example
cd /mnt/c/workspace/wolfssl-$USER/IDE/Espressif/ESP-IDF/examples/wolfssl_test

# Pick ESP-IDF install directory, this one for v5.2 in VisualGDB
. /mnt/c/SysGCC/esp32/esp-idf/v5.2/export.sh

# set target chipset
idf.py set-target esp32s3

# erase
idf.py erase-flash -p /dev/ttyS24 -b 115200

# start with a low upload speed, then increase as found operational
idf.py
# build and flash, in this example to COM24
idf.py build flash -p /dev/ttyS24 -b 115200 monitor
```

## ESP-IDF Commandline (version 3.5 or earlier for the ESP8266)


```bash
WRK_IDF_PATH=/mnt/c/SysGCC/esp8266/rtos-sdk/v3.4
. $WRK_IDF_PATH/export.sh

# install as needed / prompted
/mnt/c/SysGCC/esp8266/rtos-sdk/v3.4/install.sh

cd IDE/Espressif/ESP-IDF/examples/ESP8266

# adjust settings as desired
idf.py menuconfig

idf.py build flash -p /dev/ttyS55 -b 115200
```

## Espressif ESP8266 RTOS SDK Make Commandline

```bash
# Find the ESP8266 SDK directory, shown here for WSL (Windows C:\ESP8266\esp\ESP8266_RTOS_SDK)
cd /mnt/c/ESP8266/esp/ESP8266_RTOS_SDK

# Optionally run install as needed
./install.sh

# Setup SDK
. ./export.sh

# Find example to build
cd /mnt/c/workspace/wolfssl-gojimmypi/IDE/Espressif/ESP-IDF/examples/wolfssl_test

make clean

make

make flash

# or:
python /mnt/c/ESP8266/esp/ESP8266_RTOS_SDK/components/esptool_py/esptool/esptool.py --chip esp8266 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size 2MB 0x0 /mnt/c/workspace/wolfssl-gojimmypi/IDE/Espressif/ESP-IDF/examples/wolfssl_test/build/bootloader/bootloader.bin 0x10000 /mnt/c/workspace/wolfssl-gojimmypi/IDE/Espressif/ESP-IDF/examples/wolfssl_test/build/wolfssl_test.bin 0x8000 /mnt/c/workspace/wolfssl-gojimmypi/IDE/Espressif/ESP-IDF/examples/wolfssl_test/build/partitions_singleapp.bin
```

## Putty (via WSL)

Define a non-blank value for `ESPIDF_PUTTY_MONITOR` to launch `testMonitor.sh` output in putty.exe sessions from Windows.
Assumes `PUTTY_EXE="/mnt/c/tools/putty.exe"`.

```bash
export ESPIDF_PUTTY_MONITOR=true
```

## Example Output

Note the default wolfSSL `user_settings.h` is configured by default to be the most
compatible across the widest ranges of targets. Contact wolfSSL at support@wolfssl.com
for help in optimizing for your particular application, or see the
[docs](https://www.wolfssl.com/documentation/manuals/wolfssl/index.html).

Compiled and flashed with `idf.py build  flash -p /dev/ttyS7 -b 115200 monitor`:

```text
ets Jun  8 2016 00:22:57

rst:0x3 (SW_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:6612
load:0x40078000,len:14788
load:0x40080400,len:3792
entry 0x40080694
I (26) boot: ESP-IDF v4.4.1-dirty 2nd stage bootloader
I (26) boot: compile time 15:25:38
I (26) boot: chip revision: 1
I (29) boot_comm: chip revision: 1, min. bootloader chip revision: 0
I (37) boot.esp32: SPI Speed      : 40MHz
I (41) boot.esp32: SPI Mode       : DIO
I (46) boot.esp32: SPI Flash Size : 2MB
I (50) boot: Enabling RNG early entropy source...
I (56) boot: Partition Table:
I (59) boot: ## Label            Usage          Type ST Offset   Length
I (67) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (74) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (81) boot:  2 factory          factory app      00 00 00010000 00100000
I (89) boot: End of partition table
I (93) boot_comm: chip revision: 1, min. application chip revision: 0
I (100) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=16ca4h ( 93348) map
I (143) esp_image: segment 1: paddr=00026ccc vaddr=3ffb0000 size=024d4h (  9428) load
I (147) esp_image: segment 2: paddr=000291a8 vaddr=40080000 size=06e70h ( 28272) load
I (160) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=412d8h (266968) map
I (257) esp_image: segment 4: paddr=00071300 vaddr=40086e70 size=045a8h ( 17832) load
I (265) esp_image: segment 5: paddr=000758b0 vaddr=50000000 size=00010h (    16) load
I (270) boot: Loaded app from partition at offset 0x10000
I (270) boot: Disabling RNG early entropy source...
I (285) cpu_start: Pro cpu up.
I (286) cpu_start: Starting app cpu, entry point is 0x40081088
I (273) cpu_start: App cpu up.
I (300) cpu_start: Pro cpu start user code
I (300) cpu_start: cpu freq: 160000000
I (300) cpu_start: Application information:
I (305) cpu_start: Project name:     wolfssl_test
I (310) cpu_start: App version:      v5.5.3-stable-108-gbd7b442df-di
I (317) cpu_start: Compile time:     Nov 17 2022 15:24:40
I (323) cpu_start: ELF file SHA256:  90957eeb4f0d2246...
I (329) cpu_start: ESP-IDF:          v4.4.1-dirty
I (335) heap_init: Initializing. RAM available for dynamic allocation:
I (342) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (348) heap_init: At 3FFB2DF0 len 0002D210 (180 KiB): DRAM
I (354) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (360) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (367) heap_init: At 4008B418 len 00014BE8 (82 KiB): IRAM
I (374) spi_flash: detected chip: generic
I (378) spi_flash: flash io: dio
W (382) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (396) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
------------------------------------------------------------------------------
 wolfSSL version 5.5.3
------------------------------------------------------------------------------
error    test passed!
MEMORY   test passed!
base64   test passed!
asn      test passed!
RANDOM   test passed!
MD5      test passed!
MD4      test passed!
SHA      test passed!
SHA-256  test passed!
SHA-512  test passed!
Hash     test passed!
HMAC-MD5 test passed!
HMAC-SHA test passed!
HMAC-SHA256 test passed!
HMAC-SHA512 test passed!
HMAC-KDF    test passed!
TLSv1.3 KDF test passed!
GMAC     test passed!
DES      test passed!
DES3     test passed!
AES      test passed!
AES192   test passed!
AES256   test passed!
AES-GCM  test passed!
RSA      test passed!
PWDBASED test passed!
ECC      test passed!
ECC buffer test passed!
CURVE25519 test passed!
ED25519  test passed!
logging  test passed!
time test passed!
mutex    test passed!
Test complete
I (136548) wolfcrypt_test: Exiting main with return code:  0

I (136548) wolfssl_test: wolf_test_task complete success result code = 0
```

See the README.md file in the upper level 'examples' directory for [more information about examples](../README.md).
