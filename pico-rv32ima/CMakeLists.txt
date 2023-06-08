add_executable(pico-rv32ima
    main.c
	sd_hw_config.c
	psram.c
	cache.c
	emulator.c
    console.c
)

# Add the standard library and FatFS/SPI to the build
target_link_libraries(pico-rv32ima
	pico_stdlib 
	FatFs_SPI 
	pico_time
	pico_multicore
	hardware_vreg
)

# pico_define_boot_stage2(slower_boot2 ${PICO_DEFAULT_BOOT_STAGE2_FILE})
# target_compile_definitions(slower_boot2 PRIVATE PICO_FLASH_SPI_CLKDIV=4)

# pico_set_boot_stage2(pico-rv32ima slower_boot2)

pico_set_binary_type(pico-rv32ima copy_to_ram)
pico_add_extra_outputs(pico-rv32ima)

