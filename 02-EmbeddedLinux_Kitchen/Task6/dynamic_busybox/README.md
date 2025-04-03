# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 6: compile busybox dynamic 😊


1. after clone busybox repo go to its menuconfig and uncheck the static option , then after export the cross_compile make it it will generate busybox is dynamically linked

![](1.png "")

![](1_1.png "")
 
2. copy all the bin , sbin , user all the _install file contents to you sd card
![](2.png "")
![](3.png "")

3. you still need the shared libraries sysroot of the same compiler you compile the busybox by 
    
    take the sysroot/lib

![](4.png "")

![](5.png "")

    take the sysroot/usr/lib

![](6.png "")

![](7.png "")

4. open qemu to test :

![](8.png "")

![](9.png "")

![](10.png "")

![](11.png "")