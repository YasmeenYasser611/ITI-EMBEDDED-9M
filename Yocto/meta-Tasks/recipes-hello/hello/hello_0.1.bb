SUMMARY = "BitBake recipe using CMake"
DESCRIPTION = "Recipe created to compile main.c using CMake"
LICENSE = "CLOSED"

FILESEXTRAPATHS := "${THISDIR}/ITI:${FILESEXTRAPATHS}"

SRC_URI = "file://main.c \
           file://CMakeLists.txt"

S = "${WORKDIR}"
B = "${WORKDIR}/build"

DEPENDS = "cmake"

inherit cmake

do_configure() {
    cmake -S ${S} -B ${B}
}

do_compile() {
    cmake --build ${B} --verbose
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/hello ${D}${bindir}/hello
}

