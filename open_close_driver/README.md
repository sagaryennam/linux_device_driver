Linux Character Device Driver - Open and Release
Step 1: Create Driver Source File
Create a driver source file:

open_release_driver.c
This file should contain:

Required Linux kernel header files
Module initialization function
Module exit function
Character device registration
Open callback function
Release callback function
File operations structure
Module license information
The open callback should print the Major and Minor number whenever the device is opened.

Step 2: Create Makefile
Create a Makefile for building the kernel module.

Build the driver:

make
Step 3: Insert the Driver
Load the driver into the kernel:

sudo insmod open_release_driver.ko
Verify:

lsmod | grep open_release_driver
dmesg | tail
Step 4: Get Major and Minor Numbers
Check the kernel log:

dmesg | tail
Example:

Major = 240 Minor = 0
Step 5: Create Device Node
Create the device file using the Major and Minor numbers obtained from the driver:

sudo mknod /dev/open_release_driver c 240 0
Give appropriate permissions:

sudo chmod 666 /dev/open_release_driver
Verify:

ls -l /dev/open_release_driver
Step 6: Create User Application
Create an application file:

app_open_release.c
The application should:

Include <fcntl.h>
Open the device node using open()
Close the device using release()
Example device path:

fd = open("/dev/open_release_driver", O_RDONLY);
Compile:

gcc app_open_release.c -o app_open_release
Step 7: Execute the Application
Run:

./app_open_release
or

./app_open_release /dev/open_release_driver
Step 8: Verify Driver Open and Release Callbacks
When the application opens the device:

open("/dev/open_release_driver", O_RDONLY);
the driver's open() callback is invoked.

Kernel log output:

Device Opened
Major Number = 240
Minor Number = 0
When the application terminates and releases the device, the driver's release() callback is invoked.

Kernel log output:

Device Closed
Check the messages using:

dmesg | tail
Step 9: Remove the Driver
sudo rmmod open_release_driver

