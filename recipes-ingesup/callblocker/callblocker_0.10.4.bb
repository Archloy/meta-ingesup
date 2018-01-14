SUMMARY = "Loy embedded Qt test"

LICENSE = "WTFPL"
LIC_FILES_CHKSUM = "file://LICENCE;md5=8365d07beeb5f39d87e846dca3ae7b64"

SRC_URI = "https://github.com/pamapa/callblocker/archive/v${PV}.tar.gz \
"

SRC_URI[md5sum] = "b1e1ec27227a1f90fc82af445e244f5d"
SRC_URI[sha256sum] = "8005ddf34ebd8fdd17b613424ffeef40ffa2107b5d4298cedc6ea666e511f84b"

PACKAGE_ARCH = "${MACHINE_ARCH}"

S = "${WORKDIR}/${PN}-${PV}"

DEPENDS += " pjproject json-c libphonenumber"
RDEPENDS_${PN} = "python3 python3-bs4 python3-ldif3 python3-vobject"

inherit autotools 
