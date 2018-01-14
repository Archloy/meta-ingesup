BBCLASSEXTEND="native"
inherit native

SRC_URI += "file://native_cmakeAddCommand.patch \
"

require libphonenumber.inc 

do_install(){
    echo "nothing to install"
}

