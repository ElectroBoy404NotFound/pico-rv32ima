#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include "hardware/vreg.h"

#include "tusb.h"

#include "ff.h"
#include "hw_config.h"

#include "sdram.h"
#include "emulator.h"
#include "cdc_console.h"

const char ramFilename[] = "0:ram.bin";
const char *const imageFilename = "0:Image";

void core1_entry();

int main()
{
	//vreg_set_voltage(VREG_VOLTAGE_MAX); // overvolt the core just a bit
	//set_sys_clock_khz(375000, true);	// overclock to 375 MHz (from 125MHz)
	sleep_ms(5);

	tusb_init();

	queue_init(&screen_queue, sizeof(char), IO_QUEUE_LEN);
	queue_init(&kb_queue, sizeof(char), IO_QUEUE_LEN);

	multicore_reset_core1();
	multicore_fifo_drain();
	multicore_launch_core1(core1_entry);

	while (true)
	{
		tud_task();
		cdc_task();
	}
}

void core1_entry()
{
	sd_card_t *pSD0 = sd_get_by_num(0);
	FRESULT fr = f_mount(&pSD0->fatfs, pSD0->pcName, 1);
	if (FR_OK != fr)
		cdc_panic("SD mount error: %s (%d)\n", FRESULT_str(fr), fr);

	fr = openSDRAMfile(ramFilename, ram_amt);
	if (FR_OK != fr && FR_EXIST != fr)
		cdc_panic("Error opening RAM file: %s (%d)\n", ramFilename, FRESULT_str(fr), fr);
	cdc_printf("RAM file opened sucessfuly!\n");

	fr = loadFileIntoRAM(imageFilename, 0);
	if (FR_OK != fr)
		cdc_panic("Error loading image: %s (%d)\n", FRESULT_str(fr), fr);
	cdc_printf("Image loaded sucessfuly!\n");

	rvEmulator();

	fr = closeSDRAMfile();
	if (FR_OK != fr)
		cdc_panic("Error closing RAM file: %s (%d)\n", FRESULT_str(fr), fr);
	f_unmount(pSD0->pcName);

	while (true)
		tight_loop_contents();
}
