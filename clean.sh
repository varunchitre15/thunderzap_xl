KERNEL_DIR="/root/tz"
make ARCH=arm CROSS_COMPILE=~/toolchains/arm-eabi-linaro-4.6.2/bin/arm-eabi- -j8 clean mrproper
rm -rf $KERNEL_DIR/ramdisk.cpio
rm -rf $KERNEL_DIR/root.fs
rm -rf $KERNEL_DIR/boot.img
