SUMMARY = "Raspberry Pi LED Control Kernel Module"
DESCRIPTION = "A kernel module to control an LED via GPIO using /proc."
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

SRC_URI = "file://Makefile \
           file://ledcontrol.c \
           file://COPYING \
          "

S = "${WORKDIR}"

RPROVIDES:${PN} += "kernel-module-ledcontrol"

FILES:${PN} += "/lib/modules/${KERNEL_VERSION}/extra/ledcontrol.ko"
