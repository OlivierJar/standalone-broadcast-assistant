#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <lvgl.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>

#include "lcd.h"
#include "display_manager.h"
int display_init(void)
{
    return lcd_init();

}
static void create_buttons_before_connecting(lv_obj_t* scr)
{
    lv_obj_t *connect_btn, *scan_btn;

    lcd_clear_screen(scr);

    connect_btn = lcd_create_button(scr, "Devices", 120, 50, -80, -50, NULL);
    scan_btn = lcd_create_button(scr, "Broadcasts", 120, 50, 80, -50, NULL);
}

void create_buttons(lv_obj_t* scr)
{
    create_buttons_before_connecting(scr);
}