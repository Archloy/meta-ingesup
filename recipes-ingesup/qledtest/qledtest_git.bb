SUMMARY = "Loy embedded Qt test"

LICENSE = "WTFPL"
LIC_FILES_CHKSUM = "file://LICENCE;md5=8365d07beeb5f39d87e846dca3ae7b64"

SRCREV = "${AUTOREV}"

SRC_URI = "git://github.com/Archloy/qledtests.git \
           http://www.wtfpl.net/txt/copying;name=LICENCE \
"

SRC_URI[LICENCE.md5sum] = "8365d07beeb5f39d87e846dca3ae7b64"
SRC_URI[LICENCE.sha256sum] = "0356258391e190dc1d44ea01565cfe627fe44e27dad693a0a54c2483a7b223e5"

PR = "r0"

PACKAGE_ARCH = "${MACHINE_ARCH}"

S = "${WORKDIR}/git"

DEPENDS = " qtbase"

inherit qmake5
