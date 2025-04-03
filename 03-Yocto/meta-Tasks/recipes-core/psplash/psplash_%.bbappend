SUMMARY = "Append the splash recipe"
DESCRIPTION = "Adding splash service"
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:remove = "file://psplash.png"
SRC_URI += "file://splash.jpg\
        file://psplash-poky-img.h\
	    file://psplash.service \
"

# inherit systemd
# SYSTEMD_SERVICE:${PN} = "psplash.service"
# SYSTEMD_AUTO_ENABLE:${PN} = "enable"

# # SYSTEMD_SERVICE:${PN} += "psplash.service"
# # SYSTEMD_AUTO_ENABLE:${PN} = "enable"

# do_install:append() {
#     install -d ${D}${systemd_unitdir}/system
#     install -m 0644 ${WORKDIR}/psplash.service ${D}${systemd_unitdir}/system/
# }

# # FILES:${PN}:append = " ${systemd_system_unitdir}/psplash.service"