# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
#
# The following license files were not able to be identified and are
# represented as "Unknown" below, you will need to check them yourself:
#   LICENSE
MAINTAINER = "Yasmeen Yasser <yasmeenyasser611@gmail.com>"
LICENSE = "GPL-2.0-or-later"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0-or-later;md5=fed54355545ffd980b814dab4a3b312c"
SRC_URI = "git://github.com/COVESA/vsomeip.git;protocol=https;branch=release_3.5.4"

SRCREV = "${AUTOREV}"

DEPENDS = "boost dlt-daemon googletest"

S = "${WORKDIR}/git"

inherit cmake pkgconfig

EXTRA_OECMAKE = "-DINSTALL_LIB_DIR:PATH=${baselib} \
                 -DINSTALL_CMAKE_DIR:PATH=${baselib}/cmake/vsomeip3 \
                "

do_compile:append() {
    cmake_runcmake_build --target examples
}

do_install:append() {
    install -d ${D}${sysconfdir}/vsomeip
    mv ${D}/usr/etc/vsomeip/* ${D}${sysconfdir}/vsomeip/ 2>/dev/null || true
    rmdir ${D}/usr/etc/vsomeip ${D}/usr/etc 2>/dev/null || true
    
    # Install the library
    install -d ${D}${libdir}

    # Install actual shared libraries (with version numbers)
    for lib in libvsomeip3 libvsomeip3-cfg libvsomeip3-e2e libvsomeip3-sd; do
        install -m 0755 ${B}/${lib}.so.* ${D}${libdir}/
    done

    # Ensure .so files are symlinks (for -dev package)
    for lib in libvsomeip3 libvsomeip3-cfg libvsomeip3-e2e libvsomeip3-sd; do
        ln -sf ${lib}.so.3 ${D}${libdir}/${lib}.so
    done

}

