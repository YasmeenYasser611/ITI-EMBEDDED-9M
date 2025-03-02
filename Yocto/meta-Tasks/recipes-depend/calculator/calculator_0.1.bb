SUMMARY = "Create calculator app"
DESCRIPTION = "A calculator application using libmath"
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"

LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

SRC_URI = "file://main.c"

DEPENDS = "libmath"
RDEPENDS_${PN} = "libmath"

S = "${WORKDIR}"
B = "${WORKDIR}/build"

do_compile() {
    mkdir -p ${B}
    ${CC} ${CFLAGS} ${LDFLAGS} -I${STAGING_INCDIR} -L${STAGING_LIBDIR} -Wl,-rpath-link,${STAGING_LIBDIR} -o ${B}/calculator ${S}/main.c -lmath
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/calculator ${D}${bindir}/
}

FILES_${PN} = "${bindir}/calculator"
