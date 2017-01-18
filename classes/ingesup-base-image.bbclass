DESCRIPTION = "Basic image"
LICENSE = "MIT"

# set password to ingesup
inherit extrausers
EXTRA_USERS_PARAMS = " \
    usermod -P ingesup root; \
    "

inherit core-image

# Package gesture
IMAGE_FEATURES += "package-management"

# SSH gesture
IMAGE_FEATURES += "ssh-server-dropbear"

SENSOR_INSTALL = " \
    	ds18b20 \
"

HOTSPOT_INSTALL = " \
    	hostapd \
  	dnsmasq \
"

# Audio
ALSA_INSTALL = " \
    	alsa-utils \
    	alsa-tools \
"

CORE_OS_INSTALL = " \
    	dbus \
    	bluez5 \
    	sysfsutils \ 	
    	kernel-image \
        kernel-modules \
        kernel-devicetree \
"

IMAGE_INSTALL += " \
	${CORE_OS_INSTALL} \
	psplash \
	rtl8723bs-bt \
	openssh-sftp-server \
	packagegroup-distro-base \
	packagegroup-machine-base \
	${ALSA_INSTALL} \
	${SENSOR_INSTALL} \
	${HOTSPOT_INSTALL} \
	packagegroup-tools-io \
    	${CORE_IMAGE_EXTRA_INSTALL} \
"

# some default locales
IMAGE_LINGUAS ?= "fr-fr en-us"

export IMAGE_BASENAME = "base-image"

