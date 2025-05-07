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
 
 #include "lcd.h"
static lv_obj_t *scr;
static void create_buttons(conn_status_t all_conn)
{


    create_buttons_before_connecting();

}

static void create_buttons_before_connecting(void)
{
    lv_obj_t *connect_btn, *scan_btn;

    lcd_clear_screen(scr);

    connect_btn = lcd_create_button(scr, "Connect", 100, 50, -60, -20, NULL);
    scan_btn = lcd_create_button(scr, "Scan", 100, 50, 60, -20, NULL);
}
int main(void){

    int err;
    scr = lv_scr_act();
    err = lcd_init();
    if (err) {
        printk("Device not ready!\n");
        return 0;
    }
    printk("Display initialized.\n");
    create_buttons();
}