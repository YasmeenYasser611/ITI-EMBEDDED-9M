SUMMARY = "QT Application - Caps Lock Light Controller"
DESCRIPTION = "Qt6 application running on Yocto with systemd"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

SRC_URI = "git://github.com/YasmeenYasser611/ITI_9M_QT.git;protocol=https;branch=main"

inherit cmake

S = "${WORKDIR}/git/CapsLock_Task3"

DEPENDS = "qtbase qtdeclarative qtquickcontrols2"

RDEPENDS:${PN}="qtwayland"

do_configure() {
    cmake -S ${WORKDIR} -B ${B}
}

do_compile() {
    cmake --build ${B}
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/qtapp ${D}${bindir}/CapsLock_Task3
}

