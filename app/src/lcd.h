#ifndef __LCD_H
#define __LCD_H

#define LCD_X_MAX   160
#define LCD_X_MIN   -160
#define LCD_Y_MAX   120
#define LCD_Y_MIN   -120

//initialize lcd component styles
int lcd_init(void);
void lcd_clear_screen(lv_obj_t *parent);
lv_obj_t *lcd_create_button(lv_obj_t *parent, const char *text, int32_t w, int32_t h,
    lv_coord_t x, lv_coord_t y, lv_event_cb_t cb);
lv_obj_t *lcd_create_label(lv_obj_t *parent, const char *text, lv_coord_t x, lv_coord_t y);

#endif /* __LCD_H */
