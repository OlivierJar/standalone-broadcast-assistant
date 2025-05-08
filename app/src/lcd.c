#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <lvgl.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>

#include "lcd.h"




static lv_style_transition_dsc_t button_trans_dsc;
static bool msg_label_created;
/*
BUTTON
*/
static lv_style_t button_style;
static lv_style_t button_style_pressed;
static lv_style_prop_t button_props[] = { LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0 };

static void lcd_button_style_init(void)
{
    //initialize style
    lv_style_init(&button_style);
    //Radius of the edges of the button
    lv_style_set_radius(&button_style, 5);
    //Opacity
    lv_style_set_bg_opa(&button_style, LV_OPA_100);
    //Color
    lv_style_set_bg_color(&button_style, lv_palette_main(LV_PALETTE_DEEP_PURPLE));
    //Gradient color
    lv_style_set_bg_grad_color(&button_style,
                               lv_palette_darken(LV_PALETTE_DEEP_PURPLE, 1));
    //Gradient Direction
    lv_style_set_bg_grad_dir(&button_style, LV_GRAD_DIR_VER);
    //Border Opacity
    lv_style_set_border_opa(&button_style, LV_OPA_100);
    //BorderWidth
    lv_style_set_border_width(&button_style, 2);
    //BorderColor
    lv_style_set_border_color(&button_style,
                              lv_palette_darken(LV_PALETTE_DEEP_PURPLE, 2));
    //outline opacity
    lv_style_set_outline_opa(&button_style, LV_OPA_COVER);
    //outline color
    lv_style_set_outline_color(&button_style, lv_palette_darken(LV_PALETTE_DEEP_PURPLE, 3));
    //text color
    lv_style_set_text_color(&button_style, lv_palette_main(LV_PALETTE_AMBER));
    //padding
    lv_style_set_pad_all(&button_style, 10);
    //set the pressed style
    lv_style_init(&button_style_pressed);

    lv_style_set_outline_width(&button_style_pressed, 10);
    lv_style_set_outline_opa(&button_style_pressed, LV_OPA_TRANSP);

    lv_style_set_bg_color(&button_style_pressed, lv_palette_darken(LV_PALETTE_DEEP_PURPLE, 2));
    lv_style_set_bg_grad_color(&button_style_pressed,
                               lv_palette_darken(LV_PALETTE_DEEP_PURPLE, 4));

    lv_style_transition_dsc_init(&button_trans_dsc, button_props, lv_anim_path_linear,
                                 100, 0, NULL);
    lv_style_set_transition(&button_style_pressed, &button_trans_dsc);
}


lv_obj_t *lcd_create_button(lv_obj_t *parent, const char *text, int32_t w, int32_t h,
    lv_coord_t x, lv_coord_t y, lv_event_cb_t cb)
{
    lv_obj_t *button = lv_btn_create(parent);
    lv_obj_remove_style_all(button);
    lv_obj_add_style(button, &button_style, LV_STATE_DEFAULT);
    lv_obj_add_style(button, &button_style_pressed, LV_STATE_PRESSED);
    lv_obj_set_size(button, w, h);
    lv_obj_align(button, LV_ALIGN_CENTER, x, y);

    lv_obj_add_event_cb(button, cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label = lv_label_create(button);
    lv_label_set_text(label, text);
    lv_obj_center(label);

    return button;
}
/*
LABEL
*/
lv_obj_t *lcd_create_label(lv_obj_t *parent, const char *text, lv_coord_t x, lv_coord_t y)
{
    lv_obj_t *msg_label = lv_label_create(parent);
    lv_label_set_text(msg_label, text);
    lv_obj_align(msg_label, LV_ALIGN_CENTER, x, y);

msg_label_created = true;

return msg_label;
}
/*
UTIL
*/
void lcd_clear_screen(lv_obj_t *parent)
{
    k_sleep(K_MSEC(300));
    lv_obj_clean(parent);
    k_sleep(K_MSEC(300));}
void lcd_display_message(lv_obj_t *lbl, const char *msg)
{
    if(msg_label_created) {
        lv_label_set_text(lbl, msg);
    }
}

int lcd_init(void)
{
    lv_init();

    const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

    if (!device_is_ready(display_dev)) {
        return -1;
    }

    display_blanking_off(display_dev);
    //lcd_slider_style_init();
    lcd_button_style_init();
    //lcd_voice_icon_style_init();
    //lcd_mute_icon_style_init();

    return 0;
}