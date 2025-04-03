# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 6: using rootramfs in rpi and init process is script 😊


1. prepare the init script that fist mountvirtual folders then run sh shell:


``` bash

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

```

![](1.png "")
 
2. put the init.cpio in sd card and complete the extlinux.conf file 

``` c

DEFAULT linux
LABEL linux
    LINUX ../Image
    FDT ../bcm2837-rpi-3-b-plus.dtb
    INITRD ../init.cpio
    APPEND 8250.nr_uarts=2 console=ttyS0,115200n8 rdinit=/boot.sh

```



 3. run minicom and but the bootflow scan in bootcmd so everything run automatic after autoboot

 ![](2.png "")



4. run again and everthing will done automatically:

![](3.png "")

5. the script is run success and you arm in ram you could remove sd card  , you could check the video :) : 

![](4.png "")


![](5.png "")