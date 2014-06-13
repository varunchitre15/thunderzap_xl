#!/bin/bash
TOOLCHAIN="/root/toolchains/arm-eabi-linaro-4.6.2/bin/arm-eabi"
MODULES_DIR="../modules"
ZIMAGE="/root/tz/arch/arm/boot/zImage"
KERNEL_DIR="/root/tz"
MKBOOTIMG="/root/tz/tools/mkbootimg"
MKBOOTFS="/root/tz/tools/mkbootfs"
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
echo "Creating boot image"
$MKBOOTFS ramdisk/ > $KERNEL_DIR/ramdisk.cpio
cat $KERNEL_DIR/ramdisk.cpio | gzip > $KERNEL_DIR/root.fs
$MKBOOTIMG --kernel $ZIMAGE --ramdisk $KERNEL_DIR/root.fs --cmdline "console=ttyHSL0,115200,n8 androidboot.hardware=qcom user_debug=31 msm_rtb.filter=0x3F ehci-hcd.park=3 maxcpus=2" --base 0x80200000 --pagesize 2048 --ramdisk_offset 0x02000000 -o $KERNEL_DIR/boot.img
else
echo "Compilation failed! Fix the errors!"
fi
