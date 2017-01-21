do_deploy_append() {
	# Enable the onboard ALSA audio by default
	echo "dtparam=audio=on" >> ${DEPLOYDIR}/bcm2835-bootfiles/config.txt
}
