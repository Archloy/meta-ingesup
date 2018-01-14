SUMMARY = "ldif3 - generate and parse LDIF data (see RFC 2849)."

LICENSE = "BSD"

LIC_FILES_CHKSUM = "file://LICENSE;md5=e81fae01548e44120f5440ecb83c76cd"

SRC_URI = "https://github.com/xi/ldif3/archive/${PV}.tar.gz"

SRC_URI[md5sum] = "f586d93fdeb2e16ee9d80d707ab682fe"
SRC_URI[sha256sum] = "47e3a963d0ae0b8a97abe5721d40aaa5f20b9d9c74eec040c02e3e5fa0aec47a"

HOMEPAGE = "https://github.com/xi/ldif3"

SECTION = "devel/python"

PYPI_PACKAGE = "ldif3"

S = "${WORKDIR}/ldif3-${PV}"

inherit setuptools3
