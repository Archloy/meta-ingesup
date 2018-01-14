SUMMARY = "Google lib phone number"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=363822a4d0f7a74c43ecdc2a4c11ae64"

SRC_URI += "https://github.com/googlei18n/libphonenumber/archive/v${PV}.tar.gz \
"

SRC_URI[md5sum] = "0f7d7b257366f20baac0ff26caf54c94"
SRC_URI[sha256sum] = "9bbbfbbd57a0c10f0982c9b14d83edca2d6b5f9a636a9cae1420b8509308c140"



S = "${WORKDIR}/libphonenumber-${PV}/cpp"

DEPENDS += " gtest boost protobuf icu "
RDEPENDS_${PN} = "protobuf"

inherit cmake
