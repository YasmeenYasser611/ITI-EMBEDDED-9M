DESCRIPTION = "echo hello using bash "
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"

LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

SRC_URI = "file://hellobash"

RDEPENDS:${PN} = " bash"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/hellobash ${D}${bindir}/
}

FILES_${PN} = "${bindir}/hellobash"