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
/*
Event to happen in the case of clicking in "Devices" Button
*/
void devices_btn_event(lv_event_t *e){
    printk("Devices click event");
}
/*
Event to happen in the case of clicking in "Broadcasts" Button
*/
void broadcasts_btn_event(lv_event_t *e){
    printk("Broadcasts click event");
}
void create_navigation_buttons(lv_obj_t* scr){
    lv_obj_t *devices_btn, *broadcasts_btn;
    devices_btn = lcd_create_button(scr, "Devices", 140, 50, -75, -80, devices_btn_event);
    broadcasts_btn = lcd_create_button(scr, "Broadcasts", 140, 50, 75, -80, broadcasts_btn_event);
}
void create_devices_page(lv_obj_t* scr)
{

    lcd_clear_screen(scr);
    create_navigation_buttons(scr);

}


void create_buttons(lv_obj_t* scr)
{
    create_buttons_before_connecting(scr);
}