#!/bin/bash
TOOLCHAIN="/root/toolchains/arm-eabi-linaro-4.6.2/bin/arm-eabi"
MODULES_DIR="../modules"
ZIMAGE="/root/tz/arch/arm/boot/zImage"
KERNEL_DIR="/root/tz"
if [ -a $KERNEL_DIR/arch/arm/boot/zImage ];
then
rm $ZIMAGE
rm $MODULES_DIR/*
fi
make ARCH=arm CROSS_COMPILE=$TOOLCHAIN- cyanogenmod_taoshan_defconfig
make ARCH=arm CROSS_COMPILE=$TOOLCHAIN- -j8
if [ -a $ZIMAGE ];
then
echo "Copying modules"
rm $MODULES_DIR/*
find . -name '*.ko' -exec cp {} $MODULES_DIR/ \;
cd $MODULES_DIR
echo "Stripping modules for size"
$TOOLCHAIN-strip --strip-unneeded *.ko
zip -9 modules *
cd $KERNEL_DIR
else
echo "Compilation failed! Fix the errors!"
fi
