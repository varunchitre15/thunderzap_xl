TOOLCHAIN="/home/varunchitre15/toolchains/arm-eabi-linaro-4.6.2/bin/arm-eabi"
MODULES_DIR="/home/varunchitre15/kernel/kernel/modules"
KERNEL_DIR="/home/varunchitre15/kernel/kernel"
make ARCH=arm CROSS_COMPILE=$TOOLCHAIN- sa77_defconfig
make ARCH=arm CROSS_COMPILE=$TOOLCHAIN- -j8
if [ -a $KERNEL_DIR/arch/arm/boot/zImage ];
then
echo "Copying modules"
find -name '*.ko' -exec cp -av {} $MODULES_DIR/ \;
cd $MODULES_DIR
echo "Stripping modules for size"
for m in $(find . | grep .ko | grep './')
do echo $m
$TOOLCHAIN-strip --strip-unneeded $m
done
else
echo "Compilation failed! Fix the errors!"