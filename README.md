# TEV_JetsonXavierNX_Cboot

Create environment.
```
export TEGRA_TOP=$PWD
export GCC_DIR=<tool chain location>
export ARCH=arm64
export CROSS_COMPILE=${GCC_DIR}/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
export CROSS_COMPILE_AARCH64_PATH=${GCC_DIR}/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/
```
Compile cboot.
```
$ make -C ./bootloader/partner/t18x/cboot PROJECT=t194 TOOLCHAIN_PREFIX="${CROSS_COMPILE}" \
 DEBUG=2 BUILDROOT="${PWD}"/out NV_TARGET_BOARD=t194ref NV_BUILD_SYSTEM_TYPE=l4t NOECHO=@
```
Flash cboot.
```
$ sudo ./flash.sh -k cpu-bootloader --image cboot/out/build-t194/lk.bin jetson-xavier-nx-devkit-emmc mmcblk0p1
# You can swap 'bootloader/cboot_t194.bin' with 'out/lk.bin', remember to rename it.
```
