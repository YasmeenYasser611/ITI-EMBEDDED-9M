
install_to_bindir_do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/hello ${D}${bindir}/hello
}
EXPORT_FUNCTIONS do_install


