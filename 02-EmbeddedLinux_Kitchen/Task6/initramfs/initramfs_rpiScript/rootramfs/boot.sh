#!/bin/sh
echo "Starting boot.sh..." > /dev/console

# Mount necessary filesystems and run shell
mount -t proc none /proc
mount -t sysfs none /sys
mount -t devtmpfs none /dev
mount -t tmpfs none /tmp


# Mount boot partition (if /dev/mmcblk0p1 is your boot partition)
#mount -t vfat /dev/mmcblk0p1 /mnt/boot

echo "boot.sh completed successfully!" > /dev/console

# Run the shell
/sh
