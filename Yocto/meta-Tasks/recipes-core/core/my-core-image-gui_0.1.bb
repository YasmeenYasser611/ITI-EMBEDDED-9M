SUMMARY = "This will create a GUI image with a Qt example"
DESCRIPTION = "The core image recipe for running Qt applications"
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

inherit core-image

IMAGE_FEATURES="splash ssh-server-dropbear weston package-management"

# Add the Qt application package to the image
IMAGE_INSTALL:append=" myuiqt qtwayland qtquickcontrols2 bash connman-client"

IMAGE_ROOTFS_EXTRA_SPACE = "5242880"