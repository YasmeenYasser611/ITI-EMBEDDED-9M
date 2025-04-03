# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 5: using boot args in qemu😊

1. ensue that your emulated sd card have the following in the boot partition :
   - u-boot
   - zIMage 
   - vexpress-v2p-ca9.dtb

2. ensue that your emulated sd card have the following in the boot partition:
   - /sbin/init.

 > the init.c :

```c 

#include "stdio.h"



int main(void)
{
	printf("hello kernel \n");

	return 0;

}

```


3. run qemu :

![](1.png "")

4. set bootargs 
> setenv bootargs "console=ttyAMA0 root=/dev/mmcblk0p2 init=/sbin/init"

>saveenv

>fatload mmc 0:1 $kernel_addr_r zImage

>fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb

>bootz $kernel_addr_r - $fdt_addr_r 

![](2.png "")

5. load kernel and dtb file then boot 

![](3.png "")

> you will note that the hello kernel is printed 

![](4.png "")


## what about make script to do all of this :


```bash
setenv bootargs "console=ttyAMA0 root=/dev/mmcblk0p2 init=/sbin/init"

# Step 1: Check if zImage exists on SD card and load it
if fatload mmc 0:1 $kernel_addr_r zImage; then
    echo "zImage exists on SD card. Loading it...";
else
    echo "zImage does not exist on SD card. Trying TFTP...";

    # Step 2: Try to load zImage from TFTP
    if tftp $kernel_addr_r zImage; then
        echo "zImage successfully loaded from TFTP.";
    else
        echo "Failed to get zImage from TFTP. ";
        exit 1
    fi
fi

# Step 3: Check if device tree exists on SD card and load it
if fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb; then
    echo "Device tree blob exists on SD card. Loading it...";
else
    echo "Device tree blob does not exist on SD card. Trying TFTP...";

    # Step 4: Try to load device tree from TFTP
    if tftp $fdt_addr_r vexpress-v2p-ca9.dtb; then
        echo "Device tree blob successfully loaded from TFTP.";
    else
        echo "Failed to get device tree blob from TFTP.";
        exit 1
    fi
fi

# Step 5: Boot the kernel
echo "Booting the kernel...";
bootz $kernel_addr_r - $fdt_addr_

```



![](6.png "")


![](7.png "")














