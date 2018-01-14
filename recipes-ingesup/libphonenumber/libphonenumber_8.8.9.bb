PACKAGE_ARCH = "${MACHINE_ARCH}"

DEPENDS+=" libphonenumber-native "

SRC_URI += "file://target_cmakeAddCommand.patch \
"
NATIVE_TOOLS_DIR="${BASE_WORKDIR}/${BUILD_SYS}/${PN}-native/${PV}-${PR}/build/tools"
export NATIVE_TOOLS_DIR

require libphonenumber.inc
