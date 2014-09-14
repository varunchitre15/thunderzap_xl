ccflags-y := -O3 -mcpu=cortex-a7 -mtune=cortex-a7 -marm -mfpu=neon-vfpv4 -mvectorize-with-neon-quad -munaligned-access
obj-$(CONFIG_ION) +=	ion.o ion_heap.o ion_system_heap.o ion_carveout_heap.o ion_iommu_heap.o ion_cp_heap.o
obj-$(CONFIG_CMA) += ion_cma_heap.o
obj-$(CONFIG_ION_TEGRA) += tegra/
obj-$(CONFIG_ION_MSM) += msm/
