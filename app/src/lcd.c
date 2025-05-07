#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <lvgl.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>

#include "lcd.h"

static lv_style_t button_style;
static lv_style_t button_style_pressed;

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

    lv_style_set_outline_opa(&button_style, LV_OPA_COVER);
    lv_style_set_outline_color(&button_style, lv_palette_darken(LV_PALETTE_DEEP_PURPLE, 3));

    lv_style_set_text_color(&button_style, lv_palette_main(LV_PALETTE_AMBER));
    lv_style_set_pad_all(&button_style, 10);

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