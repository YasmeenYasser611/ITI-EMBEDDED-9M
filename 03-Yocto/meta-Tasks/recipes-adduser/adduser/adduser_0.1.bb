SUMMARY = "Add a new user to the system"
DESCRIPTION = "Creates a new user with a predefined password and sudo privileges"
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

inherit useradd

RDEPENDS:${PN} += " bash sudo shadow"

NEWUSER = "yasmeen"

#openssl passwd -6 "root"
PASSWD = "\$6\$FcD2cvMqF.cgMbXD\$.ct5ejZZeGXj56KBE0k2NC4EBHD0CZk.5m/r8mZUe8AWYuyppFgU3EmsY98QDHMfVbjLe4W60toMZ2bRTbul31"
USERADD_PACKAGES = "${PN}"

# Adding user with home directory, password, default shell, and sudo group
USERADD_PARAM:${PN} += " -d /home/${NEWUSER} -p '${PASSWD}' -s /bin/bash -G sudo ${NEWUSER}"

FILES:${PN} += "/home/${NEWUSER}" 