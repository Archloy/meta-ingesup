DESCRIPTION = "Open source SIP stack and media stack for presence, im/instant \
               messaging, and multimedia communication"
SECTION = "libs"
HOMEPAGE = "http://www.pjsip.org/"
# there are various 3rd party sources which may or may not be part of the
# build, there license term vary or are not explicitely specified.
LICENSE = "GPLv2+ & Proprietary"
 
DEPENDS = "alsa-lib libv4l openssl util-linux"
 
PARALLEL_MAKE = ""
 
SRC_URI = "http://www.pjsip.org/release/${PV}/pjproject-${PV}.tar.bz2 "
SRC_URI[md5sum] = "c347a672679e7875ce572e18517884b2"
SRC_URI[sha256sum] = "2f5a1da1c174d845871c758bd80fbb580fca7799d3cfaa0d3c4e082b5161c7b4"
LIC_FILES_CHKSUM = "file://README.txt;endline=16;md5=e7413c72dd9334edfa7dc723eed8644b"
 
S = "${WORKDIR}/pjproject-${PV}"
 
inherit autotools-brokensep pkgconfig pythonnative
 
export BUILD_SYS
export HOST_SYS
export STAGING_INCDIR
export STAGING_LIBDIR

EXTRA_OECONF += "STAGING_DIR=${STAGING_DIR_NATIVE} --enable-shared"
# webrtc fails compiling, emmintrin.h missing (the file is x86 specific, sse2)
EXTRA_OECONF_arm += " --disable-libwebrtc" 
 
do_configure_prepend () {
    export LD="${CC}"
    echo "export CFLAGS += -fPIC" > user.mak
    echo "export LDFLAGS += -fuse-ld=bfd" >> user.mak
}
 
do_compile_append() {
 
    cd ${S}/pjsip-apps/src/python
    oe_runmake
}
 
do_compile_prepend() {
    oe_runmake dep
}
 
do_install_prepend() {
    install -d ${D}/usr/bin
    install -m 755 ${S}/pjsip-apps/bin/pj* ${D}/usr/bin
}
 
do_install_append() {
    # remove the absolute path to the host's include dir
    sed -i 's:\-I/usr/include::' ${D}/usr/lib/pkgconfig/libpjproject.pc
    # remove the fdebug-prefix-map options
    sed -i 's:\-fdebug-prefix-map[a-zA-Z0-9\._\/=\-]*::g' ${D}/usr/lib/pkgconfig/libpjproject.pc
}
