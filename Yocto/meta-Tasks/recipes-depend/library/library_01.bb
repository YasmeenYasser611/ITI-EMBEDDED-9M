SUMMARY = "Math library"
DESCRIPTION = "A shared math library"
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

SRC_URI = "file://libmath.c file://libmath.h"

PROVIDES = "libmath"

S = "${WORKDIR}"
B = "${WORKDIR}/build"

do_compile() {
    mkdir -p ${B}
    ${CC} ${CFLAGS} ${LDFLAGS} -fPIC -shared ${S}/libmath.c -o ${B}/libmath.so.1 -Wl,-soname,libmath.so.1
    ln -sf libmath.so.1 ${B}/libmath.so
}

do_install() {
    install -d ${D}${libdir}
    install -m 0755 ${B}/libmath.so.1 ${D}${libdir}/
    ln -sf libmath.so.1 ${D}${libdir}/libmath.so

    install -d ${D}${includedir}
    install -m 0644 ${S}/libmath.h ${D}${includedir}/
}

FILES_${PN} = "${libdir}/libmath.so.*"
FILES_${PN}-dev = "${libdir}/libmath.so ${includedir}/libmath.h"
INSANE_SKIP_${PN} += "dev-so"


