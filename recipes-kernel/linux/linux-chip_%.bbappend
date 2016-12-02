FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
SRC_URI_append_chip += " \
	file://0001-Update-dts.patch \
	file://defconfig \
	"

