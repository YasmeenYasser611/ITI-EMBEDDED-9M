SUMMARY = "Raspberry Pi LED Control Kernel Module"
DESCRIPTION = "A kernel module to control an LED via GPIO using /dev."
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

SRC_URI = "file://Makefile \
           file://gpio_driver.c \
           file://gpio_device.c \
           file://device.h \
           file://COPYING \
          "

S = "${WORKDIR}"

RPROVIDES:${PN} += "kernel-module-ledcontroldriver"

FILES:${PN} += " \
    /lib/modules/${KERNEL_VERSION}/extra/gpio_device.ko \
    /lib/modules/${KERNEL_VERSION}/extra/gpio_driver.ko \
"