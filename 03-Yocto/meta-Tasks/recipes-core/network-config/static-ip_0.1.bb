SUMMARY = "Static IP configuration for eth0"
DESCRIPTION = "This recipe sets a static IP using Netplan and applies it via a systemd service."
LICENSE = "CLOSED"
SRC_URI = "file://01-netplan-config.yaml \
           file://netplan-apply.service"

S = "${WORKDIR}"

inherit systemd

do_install() {
    # Install Netplan configuration file
    install -d ${D}${sysconfdir}/netplan
    install -m 0644 ${WORKDIR}/01-netplan-config.yaml ${D}${sysconfdir}/netplan/01-netplan-config.yaml

    # Install systemd service
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/netplan-apply.service ${D}${systemd_system_unitdir}/netplan-apply.service
}

FILES_${PN} += "${sysconfdir}/netplan/01-netplan-config.yaml"
FILES_${PN} += "${systemd_system_unitdir}/netplan-apply.service"

# Enable systemd service
SYSTEMD_SERVICE:${PN} = "netplan-apply.service"
