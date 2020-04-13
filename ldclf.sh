#!/bin/bash
SRC_LOCATION=path_to_source
NAME=capslockfix
SYS_LOOKUP=/etc/modules
SYS_LOC=/lib/modules/$(uname -r)/kernel/drivers/leds/

if ! grep -q -x $NAME $SYS_LOOKUP; then
	printf "\n$NAME\n" >> $SYS_LOOKUP
	echo "Added $NAME to $SYS_LOOKUP"
fi

cd $SRC_LOCATION
echo "cded to $SRC_LOCATION"
echo "Cleaning..."
make clean
echo "Compiling..."
make
cp "$NAME.ko" $SYS_LOC
echo "Copied $NAME.ko to $SYS_LOC"
echo "Running depmod..."
depmod

if lsmod | grep -q -w $NAME; then
	rmmod $NAME
	echo "Unloaded module $NAME."
fi

echo "Loading module $NAME..."
modprobe $NAME

if ! lsmod | grep -q -w $NAME; then
	echo "Error. $NAME couldn't be loaded."
else
	echo "$NAME loaded."
fi
