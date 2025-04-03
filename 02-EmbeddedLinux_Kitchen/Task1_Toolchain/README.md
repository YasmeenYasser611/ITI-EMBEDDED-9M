# Yasmeen Yasser Mohamed
# EmbeddedLinuxKitchen_Task1:)
>### 1. Create a Custom Toolchain with crosstool-ng

    using musl library

![](1.png "")


    using  glibc library

![](2.png "")

    using uclibc library

![](3.png "")  

    the toolchain generated:

![](4.png "")


### 2. create c file and compile it using  gcc from our toolchainn

main.c 

``` 
#include <stdio.h>

int main() {
    printf("Hello, World from ARM Cortex-A9!\n");
    return 0;
}


```


![](5.png "")

### 3.install  qemu to emulate arm cortex a9

![](6.png "")


![](7.png "")

### 4.to link the program dynamically and use QEMU export the sysroot path for QEMU

![](8.png "")




