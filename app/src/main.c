/*
 * Copyright (c) 2024 Demant A/S
 * SPDX-License-Identifier: Apache-2.0
 */

 #include <errno.h>
 #include <stdlib.h>
 #include <string.h>
 #include <lvgl.h>
 #include <zephyr/kernel.h>
 #include <zephyr/sys/printk.h>
 #include "display_manager.h"
 #include "lcd.h"
static lv_obj_t* scr;




int main(void){

    int err;
    scr = lv_scr_act();
    err = display_init();
    if (err) {
        printk("Device not ready!\n");
        return 0;
    }
    printk("Display initialized.\n");
    create_devices_page(scr);
    while (1) {
        lv_task_handler();
        k_sleep(K_MSEC(50));
    }
}