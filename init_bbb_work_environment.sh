#!/bin/bash -e


#-------------------Defined Variables-------------------#
#Chose the location of your toolcain path
TOOLCHAIN_PATH_INSTALL="/opt/toolchain"

#Compiler Online Name
TOOLCHAIN_ONLINE_NAME="gcc-linaro-5.1-2015.08-x86_64_arm-linux-gnueabihf"

#Source of toolchian, subject to change when they release another version... needs to be imporved.
TOOLCHAIN_ONLINE_SOURCE="https://releases.linaro.org/components/toolchain/binaries/latest-5.1/arm-linux-gnueabihf/gcc-linaro-5.1-2015.08-x86_64_arm-linux-gnueabihf.tar.xz"

#Name of local toolchain
TOOLCHAIN_NAME="gcc-linaro.tar.gz"

#Location of Toolchain for the end user
TOOCHAIN_PATH=$TOOLCHAIN_PATH_INSTALL/$TOOLCHAIN_NAME

#This name needs to be available in your yum or debian repos
IDE=eclipse


#------------------Beginning of Script------------------#

echo "[ $0 ]: Are you sure you want to install [y]?"
read input

if [ "$input" != "y" ]; then
	echo "[ $0 ]: Oh.. Okay Bye!"
	exit
fi

#Fetch which operating system is running
OS=$(lsb_release -si)

if [ "$OS" == "Ubuntu" ]; then
	echo "[ $0 ]: Installing Eclipse"
	apt-get install eclipse -y
elif [ "$OS" == "Fedora" ]; then
	echo "[ $ls0 ]: Installing Eclipse"
	yum install eclipse -y
else
	echo "[ $0 ]: You don't have a valid distro for this script, Aborting!"
	exit
fi

mkdir -p $TOOLCHAIN_PATH_INSTALL

wget $TOOLCHAIN_ONLINE_SOURCE -O $TOOCHAIN_PATH
tar -xavf $TOOCHAIN_PATH -C $TOOLCHAIN_PATH_INSTALL

echo "[ $0 ]: Use the paths below as you wish"
echo "[ $0 ]: $TOOLCHAIN_PATH_INSTALL/$TOOLCHAIN_ONLINE_NAME/bin"
echo "[ $0 ]: $TOOLCHAIN_PATH_INSTALL/$TOOLCHAIN_ONLINE_NAME/lib"
echo "[ $0 ]: Finished Fetching toolchain"
