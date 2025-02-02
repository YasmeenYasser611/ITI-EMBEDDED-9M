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

![](4.png "")

![](5.png "")

![](6.png "")

## 2. change root fs to the rootfs partition 

![](7.png "")


