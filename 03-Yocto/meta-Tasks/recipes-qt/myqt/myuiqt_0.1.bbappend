SUMMARY = "This will create GUI image with QT example"
DESCRIPTION = "Qt application"
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"

inherit systemd

SRC_URI:append = " file://qt.service"

# Ensure systemd service starts on boot
SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "qt.service"

do_install:append() {
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/qt.service ${D}${systemd_system_unitdir}/
}

FILES:${PN} += "${systemd_system_unitdir}/qt.service"
