# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 7: switch root file system 😊


## 1. boot from the initramfs in the boot partition 

> extlinux.conf


``` 

DEFAULT linux
LABEL linux
    LINUX ../zImage
    FDT ../vexpress-v2p-ca9.dtb
    INITRD ../rootramfs.cpio
    APPEND console=ttyAMA0 rdinit=/sbin/init

```
>the cpio file  , we will use the basybox init so we need to setup the required etc configurations


![](1.png "")

![](2.png "")

![](3.png "")

> move rootramfs.cpio to the boot partition of the emulated sd card 
![](8.png "")

>open qemu 

qemu-system-arm -M vexpress-a9 -kernel u-boot -nographic -sd ../../sdcard/sd.img 

![](4.png "")


setenv ramdisk_addr_r 0x67000000

bootflow scan

![](5.png "")

![](6.png "")

## 2. change root fs to the rootfs partition 

mount --move /proc /newroot/proc
mount --move /sys /newroot/sys
mount --move /dev /newroot/dev


![](7.png "")


