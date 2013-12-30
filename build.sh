#!/bin/bash
TOOLCHAIN="/home/varunchitre15/toolchains/arm-eabi-linaro-4.6.2/bin/arm-eabi"
MODULES_DIR="../modules"
ZIMAGE="/home/varunchitre15/kernel/kernel/arch/arm/boot/zImage"
KERNEL_DIR="/home/varunchitre15/kernel/kernel"
if [ -a $KERNEL_DIR/arch/arm/boot/zImage ];
then
rm $ZIMAGE
rm $MODULES_DIR/*
fi
make ARCH=arm CROSS_COMPILE=$TOOLCHAIN- sa77_defconfig
make ARCH=arm CROSS_COMPILE=$TOOLCHAIN- -j8
if [ -a $KERNEL_DIR/arch/arm/boot/zImage ];
then
echo "Copying modules"
find . -name '*.ko' -exec cp {} $MODULES_DIR/ \;
cd $MODULES_DIR
echo "Stripping modules for size"
$TOOLCHAIN-strip --strip-unneeded *.ko
cd $KERNEL_DIR
else
echo "Compilation failed! Fix the errors!"
fi
