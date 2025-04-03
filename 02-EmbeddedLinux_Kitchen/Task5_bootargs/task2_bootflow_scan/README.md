# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 5: using bootflow scan in qemu😊

1. ensue that your emulated sd card have the following in the boot partition :
   - u-boot
   - zIMage 
   - vexpress-v2p-ca9.dtb
   - extlinux
        - extlinux.conf


 2. > the extlinux.conf :

```
DEFAULT linux
LABEL linux
    LINUX ../zImage
    FDT ../vexpress-v2p-ca9.dtb
    APPEND console=ttyAMA0 root=/dev/mmcblk0p2 init=/sbin/init

```


3. run qemu :

![](1.png "")
 

 4.just run bootflow scan 

 ![](2.png "")

 ![](3.png "")