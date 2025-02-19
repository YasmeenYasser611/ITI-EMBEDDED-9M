# Yasmeen Yasser Mohamed
## Yocto Task1 : Hello World & TCPDump  😊

## Overview
- A **Hello World CMake project** into Yocto.
- The **tcpdump** network analysis tool into the image.


---

## 1️⃣ Setting Up the Hello World Application

## 1. create the layer for tasks 


![](1.png "")




## 2. create in it recipe for the task 

![](2.png "")

### ** Creating `main.c`**
Create a `main.c` file inside `recipes-Hello/Hello/ITI/`:

```c
#include <stdio.h>

int main(void)
{
	printf("Hello ITI \n");
	return 0;

}
```

### ** Creating `CMakeLists.txt`**
Create a `CMakeLists.txt` file inside `recipes-Hello/Hello/ITI/`:

```cmake
cmake_minimum_required(VERSION 3.2)
project(hello C)

if(DEFINED ENV{CC})
    set(CMAKE_C_COMPILER $ENV{CC})
endif()

add_executable(${PROJECT_NAME} main.c)

```

### ** Creating the BitBake Recipe (`Hello_0.1.bb`)**
Inside `recipes-Hello/Hello/`, create `Hello_0.1.bb`:

```bitbake
SUMMARY = "BitBake recipe using CMake"
DESCRIPTION = "Recipe created to compile main.c using CMake"
LICENSE = "CLOSED"

FILESEXTRAPATHS := "${THISDIR}/ITI:${FILESEXTRAPATHS}"

SRC_URI = "file://main.c \
           file://CMakeLists.txt"

S = "${WORKDIR}"
B = "${WORKDIR}/build"

DEPENDS = "cmake"

inherit cmake

do_configure() {
    cmake -S ${S} -B ${B}
}

do_compile() {
    cmake --build ${B} --verbose
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/hello ${D}${bindir}/hello
}

```

![](4.png "")


### **Step 3: Adding the Recipe to the Build**
Modify `local.conf` or create a custom image recipe and add:


![](5.png "")


![](6.png "")

Build the image:
```sh
bitbake core-image-minimal
```

![](7.png "")
---

## 2️⃣ Adding `tcpdump` to the Image

### **Step 1: Add the Networking Layer**

![](8.png "")

If not already added, include the networking layer:

```sh
bitbake-layers add-layer ../meta-openembedded/meta-networking/
bitbake-layers add-layer ../meta-openembedded/meta-python/
bitbake-layers add-layer ../meta-openembedded/meta-oe/
```
![](9.png "")

### **Step 2: Modify the Image to Include `tcpdump`**
In `local.conf` or your custom image recipe, add:

![](10.png "")

### **Step 3: Build and Flash the Image**
Run:
```sh
bitbake core-image-minimal
```
Flash the generated image to your device  ---> you could use balenaEtcher.

---

## 3️⃣ Testing the Build

### **Hello World Test**
After booting the image, run:
```sh
hello
```
Expected output:
```
Hello ITI
```

### **TCPDump Test**
To verify `tcpdump`, run:
```sh
tcpdump -D
```
This should list available interfaces.

![](3.png "")

---
