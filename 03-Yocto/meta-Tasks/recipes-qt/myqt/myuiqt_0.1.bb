SUMMARY = "QT Application - Caps Lock Light Controller"
DESCRIPTION = "Qt6 application running on Yocto with systemd"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"

SRC_URI = "git://github.com/YasmeenYasser611/headlight-qt.git;protocol=https;branch=main;"

SRCREV = "64a0b01f5bcf5d404324bf76844d12b4ae141ae8"

inherit qt6-cmake qt6-paths

S = "${WORKDIR}/git"

DEPENDS += " \
    qtbase \
    qtdeclarative-native \
    qtmultimedia \
    qtwayland \
    qtlocation \
    qtpositioning \
    qtquick3d \
    qtquicktimeline \
    qttools \
    qtapplicationmanager-native \
"

RDEPENDS:${PN} += " \
    qtbase \
    qtdeclarative \
    qtmultimedia \
    qtwayland \
    qtlocation \
    qtpositioning \
    qtquick3d \
    qtquicktimeline \
    qttools \
    qtapplicationmanager \
"

FILES_${PN}:append = " ${bindir}"
APP_NAME="Qt-App-LED"


