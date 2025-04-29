DESCRIPTION = "UART to GPIO LED control script"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

SRC_URI = "file://uart-led.py \
           file://uart-led.service"

RDEPENDS:${PN} += "python3-core python3-pyserial"

S = "${WORKDIR}"

inherit systemd

SYSTEMD_SERVICE:${PN} = "uart-led.service"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/uart-led.py ${D}${bindir}/uart-led.py

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${S}/uart-led.service ${D}${systemd_system_unitdir}/uart-led.service
}

FILES:${PN} += "${systemd_system_unitdir}/uart-led.service"

