KERNEL_DIR="/root/tz"
make ARCH=arm CROSS_COMPILE=~/toolchains/arm-eabi-linaro-4.6.2/bin/arm-eabi- -j8 clean mrproper
rm $KERNEL_DIR/ramdisk.cpio
rm $KERNEL_DIR/root.fs
rm $KERNEL_DIR/boot.img
