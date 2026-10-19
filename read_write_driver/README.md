Read Write Character Driver
This project demonstrates a simple Linux Character Driver that supports read and write operations using copy_to_user() and copy_from_user() APIs.

Files
Driver Source
read_write_driver.c
Implements:

Module initialization and cleanup
Driver registration
Read operation
Write operation
User Application
app_read_write.c
Used to:

Open the device file
Read data from the driver
Display received data on the terminal
Build the Driver
Create the following Makefile:

obj-m += read_write_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
Compile:

make
Expected output:

read_write_driver.ko
Insert Driver
Load the module:

sudo insmod read_write_driver.ko
Verify:

dmesg
Example:

chrdev registered with Major Number:240
Get Major Number
cat /proc/devices
Example:

240 read_write_fs
Create Device Node
Create device file using the major number obtained above:

sudo mknod /dev/read_write_fs c 240 0
Change permission:

sudo chmod 666 /dev/read_write_fs
Verify:

ls -l /dev/read_write_fs
Compile User Application
gcc app_read_write.c -o app_read_write
Write Data to Driver
Write data into the driver buffer:

echo "Hello Driver" > /dev/read_write_fs
Check kernel logs:

dmesg
Expected:

Write Operation
File Offset:0, Copy byte size:13
Read Data Using Application
Run:

./app_read_write /dev/read_write_fs
Example output:

Hello Driver
The application:

Opens the device file.
Reads one byte at a time.
Prints received data using putchar().
Closes the device file.
Monitor Driver Messages
In another terminal:

sudo dmesg -w
This continuously displays driver log messages.

Remove Driver
Remove module:

sudo rmmod read_write_driver
Verify:

dmesg
Expected:

This is my_module_exit
Complete Test Flow
make

sudo insmod read_write_driver.ko

cat /proc/devices

sudo mknod /dev/read_write_fs c <major_number> 0

sudo chmod 666 /dev/read_write_fs

gcc app_read_write.c -o app_read_write

echo "Hello Driver" > /dev/read_write_fs

./app_read_write /dev/read_write_fs

sudo rmmod read_write_driver
Expected Result
Driver registers successfully.
Device node is created.
Data written from user space reaches the driver through copy_from_user().
Data read by the application comes from the driver through copy_to_user().
Driver messages are visible using dmesg.
