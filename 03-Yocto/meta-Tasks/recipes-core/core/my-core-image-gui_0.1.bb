SUMMARY = "This will create a GUI image with a Qt example"
DESCRIPTION = "The core image recipe for running Qt applications"
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

inherit core-image
inherit extrausers
inherit module

ROOT_PASSWORD = "123"
EXTRA_USERS_PARAMS = " usermod -p '$(openssl passwd -6 ${ROOT_PASSWORD})' root;"

# Enable important features
IMAGE_FEATURES = "splash ssh-server-dropbear weston package-management"

# Core packages adduser
IMAGE_INSTALL:append = " bash sudo tcpdump vim make freerdp netplan static-ip "

# Qt and UI-related packages 
IMAGE_INSTALL:append = " wayland weston-init connman-client myuiqt" 

# Example applications
IMAGE_INSTALL:append = " example hello hellobash calculator"

# Additional modules and tools 
IMAGE_INSTALL:append = "  vsomeiplibrary ledcontrol-mod ledcontrol-driver ledcontrol-platformdd1 uart-led"



IMAGE_ROOTFS_EXTRA_SPACE = "5242880"
