#!/bin/bash -e


#-------------------Defined Variables-------------------#
#Main Envrionment Install Location
BBB_WORKSPACE_PATH="/opt/BBB_WorkSpace"

#Compiler Online Name
TOOLCHAIN_ONLINE_NAME="gcc-linaro-5.1-2015.08-x86_64_arm-linux-gnueabihf"

#Source of toolchian, subject to change when they release another version... needs to be imporved.
TOOLCHAIN_ONLINE_SOURCE="https://releases.linaro.org/components/toolchain/binaries/latest-5.1/arm-linux-gnueabihf/gcc-linaro-5.1-2015.08-x86_64_arm-linux-gnueabihf.tar.xz"

#Name of local toolchain
TOOLCHAIN_NAME="gcc-linaro.tar.gz"

#Location of Toolchain for the end user
TOOCHAIN_PATH=$TOOLCHAIN_PATH_INSTALL/$TOOLCHAIN_NAME

#Check to see if we are root
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root, Bailing out!"
   exit 1
fi

#------------------Beginning of Script------------------#
function install()
{

	#Check if Previous Version was installed
	if [ -d "$BBB_WORKSPACE_PATH" ]; then
	 	echo "[ $0 ]: Seems like you have a previous version installed please do <sudo $0 -uninstall> to uninstall it."
	 	exit 1
	fi

	echo "[ $0 ]: Are you sure you want to install [y]?"
	read input

	if [ "$input" != "y" ]; then
		echo "[ $0 ]: Oh.. Okay Bye!"
		exit 1
	fi

	ARCH=$(uname -p)

	if [ "$ARCH" == "x86_64" ]; then
		online_ide_source="http://eclipse.mirror.rafal.ca/technology/epp/downloads/release/luna/SR2/eclipse-cpp-luna-SR2-linux-gtk-x86_64.tar.gz"
	elif [ "$ARCH" == "i386" ]; then
		online_ide_source="http://eclipse.mirror.rafal.ca/technology/epp/downloads/release/luna/SR2/eclipse-cpp-luna-SR2-linux-gtk.tar.gz"
	else
		echo "[ $0 ]: You don't have a valid Archatecture for this script, Aborting!"
		exit
	fi

	#Install IDE
	mkdir -p $BBB_WORKSPACE_PATH

	echo "[ $0 ]: Fetching Eclipse Online Source"
	wget $online_ide_source -O $BBB_WORKSPACE_PATH/eclipse.tar.gz
	tar -xavf $BBB_WORKSPACE_PATH/eclipse.tar.gz -C $BBB_WORKSPACE_PATH

	ln -s $BBB_WORKSPACE_PATH/eclipse/eclipse /usr/bin/eclipse

	echo "[ $0 ]: Fetching Toolchian Linaro Online Source"
	wget $TOOLCHAIN_ONLINE_SOURCE -O $BBB_WORKSPACE_PATH/$TOOLCHAIN_NAME
	tar -xavf $BBB_WORKSPACE_PATH/$TOOLCHAIN_NAME -C $BBB_WORKSPACE_PATH

	#GTFO
	echo "[ $0 ]: Now go to your Eclipse executable found in $BBB_WORKSPACE_PATH/eclipse/ and point the cross compiler to the following paths."
	echo "[ $0 ]: $BBB_WORKSPACE_PATH/$TOOLCHAIN_ONLINE_NAME/bin"
	echo "[ $0 ]: $BBB_WORKSPACE_PATH/$TOOLCHAIN_ONLINE_NAME/lib"
	echo "[ $0 ]: Finished Installing Eclipse and fetching arm toolchain"

}


function uninstall
{
	echo "[ $0 ]: Are you sure you want to remove Eclipse and $TOOLCHAIN_ONLINE_NAME [y]?"
	read input

	if [ "$input" != "y" ]; then
		echo "[ $0 ]: Oh.. Okay Bye!"
		exit 1
	fi

	rm /usr/bin/eclipse
	rm $BBB_WORKSPACE_PATH -r

	echo "[ $0 ]: Finished Removing Eclipse and arm toolchain"
}

function show_help()
{
   echo "[ $0 ]: You have to chose the following arguments:"
   echo "< -install >   - Installs Eclipse and Arm Toolchain"
   echo "< -uninstall > - Removes Eclipse and Arm ToolChain"  
   echo "< -help >      - Shows this message"    
}


case "${1}" in
    "-install")
        install ;;
    "-uninstall")
        uninstall ;;
	"-remove")
	    uninstall ;; 
	"-help")
	    show_help ;;   
	*)
		show_help ;;
esac
