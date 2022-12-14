/**
 * Copyright (c) 2019-2021, NVIDIA Corporation.  All Rights Reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation.  Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation
 * is strictly prohibited.
 */

#define MODULE  TEGRABL_ERR_LINUXBOOT

#include "build_config.h"
#include <tegrabl_error.h>
#include <tegrabl_debug.h>
#include <tegrabl_malloc.h>
#include <tegrabl_blockdev.h>
#include <tegrabl_file_manager.h>
#include <tegrabl_sdram_usage.h>
#include <tegrabl_binary_types.h>
#include <tegrabl_linuxboot_utils.h>
#include <tegrabl_devicetree.h>
#include <tegrabl_exit.h>
#include <linux_load.h>
#if defined(CONFIG_ENABLE_EXTLINUX_BOOT)
#include <extlinux_boot.h>
#endif
#include <fixed_boot.h>
#if defined(CONFIG_ENABLE_A_B_SLOT)
#include <tegrabl_a_b_boot_control.h>
#endif

#define KERNEL_DTBO_PART_SIZE	 (1024 * 1024 * 1)

struct tegrabl_img_dtb_fdt {
	char *img_name_str;
	char *dtb_name_str;
	uint32_t img_bin_type;
	uint32_t dtb_bin_type;
	uint32_t preload_dtb_bin_type;
} img_dtb_fdt_table[] = {
	{
		.img_name_str = "kernel",
		.dtb_name_str = "kernel-dtb",
		.img_bin_type = TEGRABL_BINARY_KERNEL,
		.dtb_bin_type = TEGRABL_BINARY_KERNEL_DTB,
		.preload_dtb_bin_type = TEGRABL_DT_KERNEL
	},
#if defined(CONFIG_ENABLE_L4T_RECOVERY)
	{
		.img_name_str = "recovery",
		.dtb_name_str = "recovery-dtb",
		.img_bin_type = TEGRABL_BINARY_RECOVERY_IMG,
		.dtb_bin_type = TEGRABL_BINARY_RECOVERY_DTB,
		.preload_dtb_bin_type = TEGRABL_DT_INVALID
	},
#endif
};

static tegrabl_error_t
tegrabl_load_from_partition(struct tegrabl_kernel_bin *kernel,
			    void **boot_img_load_addr, void **dtb_load_addr,
			    void **kernel_dtbo,
			    void *data, uint32_t data_size,
			    bool boot_to_recovery)
{
	uint32_t boot_img_size;
	tegrabl_error_t err = TEGRABL_NO_ERROR;
	struct tegrabl_img_dtb_fdt *img_dtb_fdt = NULL;

	TEGRABL_UNUSED(kernel_dtbo);
	TEGRABL_UNUSED(boot_to_recovery);

#if defined(CONFIG_ENABLE_L4T_RECOVERY)
	img_dtb_fdt = boot_to_recovery ? &img_dtb_fdt_table[1] : &img_dtb_fdt_table[0];
#else
	img_dtb_fdt = &img_dtb_fdt_table[0];
#endif

	/* Load boot image from memory */
	if (!kernel->load_from_storage) {
		pr_info("Loading kernel from memory ...\n");
		if (!data) {
			err = TEGRABL_ERROR(TEGRABL_ERR_INVALID, 0);
			pr_error("Found no kernel in memory\n");
			goto fail;
		}
		*boot_img_load_addr = data;
		boot_img_size = data_size;
		goto boot_image_load_done;
	}

	err = tegrabl_load_binary(img_dtb_fdt->img_bin_type, boot_img_load_addr,
					&boot_img_size);
	if (err != TEGRABL_NO_ERROR) {
		goto fail;
	}
#if defined(CONFIG_ENABLE_SECURE_BOOT)
	err = tegrabl_validate_binary(img_dtb_fdt->img_bin_type, img_dtb_fdt->img_name_str, BOOT_IMAGE_MAX_SIZE,
					*boot_img_load_addr, &boot_img_size);
	if (err != TEGRABL_NO_ERROR) {
		goto fail;
	}
#else
	/* When BCH is not available, then binary size cannot be known so use buffer size */
	boot_img_size = BOOT_IMAGE_MAX_SIZE;
#endif  /* CONFIG_ENABLE_SECURE_BOOT */
	err = tegrabl_verify_boot_img_hdr(*boot_img_load_addr, boot_img_size);
	if (err != TEGRABL_NO_ERROR) {
		goto fail;
	}

boot_image_load_done:
#if defined(CONFIG_DT_SUPPORT)
	/* Check whether kernel dtb is already loaded in memory */
	err = tegrabl_dt_get_fdt_handle(img_dtb_fdt->preload_dtb_bin_type, dtb_load_addr);
	if ((err != TEGRABL_NO_ERROR) || (*dtb_load_addr == NULL)) {
		/* Load kernel dtb or recovery dtb */
		err = tegrabl_load_binary(img_dtb_fdt->dtb_bin_type,
						dtb_load_addr, NULL);
		if (err != TEGRABL_NO_ERROR) {
			goto fail;
		}
	} else {
		pr_info("kernel-dtb is already loaded\n");
	}

#if defined(CONFIG_ENABLE_SECURE_BOOT)
	err = tegrabl_validate_binary(img_dtb_fdt->dtb_bin_type, img_dtb_fdt->dtb_name_str, DTB_MAX_SIZE,
					*dtb_load_addr, NULL);
	if (err != TEGRABL_NO_ERROR) {
		goto fail;
	}
#endif /* CONFIG_ENABLE_SECURE_BOOT */
#endif /* CONFIG_DT_SUPPORT */

#if defined(CONFIG_DT_SUPPORT)
#if defined(CONFIG_ENABLE_DTB_OVERLAY)
		/* kernel_dtbo should also be protected by verified boot */
		*kernel_dtbo = tegrabl_malloc(KERNEL_DTBO_PART_SIZE);
		if (!*kernel_dtbo) {
			pr_error("Failed to allocate memory\n");
			err = TEGRABL_ERROR(TEGRABL_ERR_NO_MEMORY, 0);
			return err;
		}

		err = tegrabl_load_binary(TEGRABL_BINARY_KERNEL_DTBO, kernel_dtbo, NULL);
		if (err != TEGRABL_NO_ERROR) {
			pr_error("Error %u loading kernel-dtbo\n", err);
			goto fail;
		}
		pr_info("kernel DTBO @ %p\n", kernel_dtbo);
#endif /* CONFIG_ENABLE_DTB_OVERLAY */

#else
		*dtb_load_addr = NULL;
#endif /* CONFIG_DT_SUPPORT */

fail:
	return err;
}

tegrabl_error_t fixed_boot_load_kernel_and_dtb(struct tegrabl_kernel_bin *kernel,
											   void **boot_img_load_addr,
											   void **dtb_load_addr,
											   void **kernel_dtbo,
											   void **ramdisk_load_addr,
											   void *data,
											   uint32_t data_size,
											   uint32_t *kernel_size,
											   uint64_t *ramdisk_size)
{
	tegrabl_error_t err = TEGRABL_NO_ERROR;
#if defined(CONFIG_ENABLE_EXTLINUX_BOOT)
	struct tegrabl_bdev *bdev = NULL;
	struct tegrabl_fm_handle *fm_handle = NULL;
	bool kernel_from_rootfs;
#endif
#if defined(CONFIG_ENABLE_L4T_RECOVERY)
	struct tegrabl_kernel_bootctrl bootctrl;
	bool boot_to_recovery = false;
#endif

	pr_info("########## Fixed storage boot ##########\n");

	if ((boot_img_load_addr == NULL) || (dtb_load_addr == NULL)) {
		pr_error("Invalid args passed\n");
		err = TEGRABL_ERROR(TEGRABL_ERR_INVALID, 1);
		goto fail;
	}

#if defined(CONFIG_ENABLE_L4T_RECOVERY)
	tegrabl_get_kernel_bootctrl(&bootctrl);
	if (bootctrl.mode == BOOT_TO_RECOVERY_MODE) {
		boot_to_recovery = true;
	}
#if defined(CONFIG_ENABLE_A_B_SLOT)
	/* If no rootfs available, load recovery kernel */
	if (tegrabl_a_b_rootfs_is_all_unbootable(NULL)) {
		boot_to_recovery = true;
	}
#endif

	if (boot_to_recovery) {
		/* Load recovery kernel and kernel-dtb */
		err = tegrabl_load_from_partition(kernel, boot_img_load_addr,
						  dtb_load_addr, kernel_dtbo,
						  data, data_size,
						  true);
		if (err != TEGRABL_NO_ERROR) {
			pr_error("Load recovery image failed, err: %u\n", err);
			pr_trace("Trigger SoC reset\n");
			tegrabl_reset();
		}
		goto fail;
	}
#endif

#if defined(CONFIG_ENABLE_EXTLINUX_BOOT)
	/* Publish partitions of storage device*/
	bdev = tegrabl_blockdev_open(TEGRABL_STORAGE_SDMMC_USER, 3);
	if (bdev == NULL) {
		err = TEGRABL_ERROR(TEGRABL_ERR_OPEN_FAILED, 0);
		goto fail;
	}
	tegrabl_fm_publish(bdev, &fm_handle);

	err = extlinux_boot_load_kernel_and_dtb(fm_handle, boot_img_load_addr, dtb_load_addr, kernel_size,
											&kernel_from_rootfs);
	if (err == TEGRABL_NO_ERROR) {
		/* If kernel is loaded from rootfs, we need to continue to load ramdisk.
		 * Note: if kernel is loaded from partition, it contains ramdisk already.
		 */
		if (kernel_from_rootfs == true) {
			err = extlinux_boot_load_ramdisk(fm_handle, ramdisk_load_addr, ramdisk_size);
			if (err == TEGRABL_NO_ERROR) {
				extlinux_boot_set_status(true);
			} else {
				pr_error("Failed loading ramdisk\n");
			}
		}
		goto fail;  /* There is no fallback for ramdisk, so let caller handle the error */
	}
	pr_error("Failed extlinux boot.\n");
	goto fail;
#else
	TEGRABL_UNUSED(ramdisk_load_addr);
	TEGRABL_UNUSED(kernel_size);
	TEGRABL_UNUSED(ramdisk_size);
#endif

	/* Load normal kernel and kernel-dtb */
	err = tegrabl_load_from_partition(kernel, boot_img_load_addr,
					  dtb_load_addr, kernel_dtbo,
					  data, data_size,
					  false);
	if (err != TEGRABL_NO_ERROR) {
		pr_error("Storage boot failed, err: %u\n", err);
#if defined(CONFIG_ENABLE_A_B_SLOT)
		pr_error("A/B loader failure\n");
		pr_trace("Trigger SoC reset\n");
		tegrabl_reset();
#endif
	}

fail:
#if defined(CONFIG_ENABLE_EXTLINUX_BOOT)
	if (fm_handle != NULL) {
		tegrabl_fm_close(fm_handle);
	}
#endif

	return err;
}
