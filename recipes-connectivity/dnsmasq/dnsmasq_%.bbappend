# Customization of dnsmasq

# Files directory
FILESEXTRAPATHS_prepend := "${THISDIR}/dnsmasq:"

# Sources
SRC_URI_append = " \
    file://dnsmasq.conf \
"
