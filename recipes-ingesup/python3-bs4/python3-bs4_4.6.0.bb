SUMMARY = "error-tolerant HTML parser for Python 3"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI[md5sum] = "c17714d0f91a23b708a592cb3c697728"
SRC_URI[sha256sum] = "808b6ac932dccb0a4126558f7dfdcf41710dd44a4ef497a0bb59a77f9f078e89"

HOMEPAGE = "http://www.crummy.com/software/BeautifulSoup/bs4/"

SECTION = "devel/python"

PYPI_PACKAGE = "beautifulsoup4"

inherit pypi setuptools3
