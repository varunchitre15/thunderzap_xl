KERNEL_DIR="/root/tz"
make ARCH=arm CROSS_COMPILE="/root/linaro/4.8.3-2013.11.20131205/bin/arm-linux-gnueabihf-" -j8 clean mrproper
rm -rf $KERNEL_DIR/ramdisk.cpio
rm -rf $KERNEL_DIR/root.fs
rm -rf $KERNEL_DIR/boot.img
