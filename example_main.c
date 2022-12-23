#include "lvgl_manage.h"

/************
*** Global
*************/

/************
*** Style
*************/
static lv_style_t sty_lvgl_label;

/************
*** Obj repaint
*************/
static void main_bg_repaint(lv_obj_t * obj);
static void main_btn_repaint(lv_obj_t * obj);
static void main_btn_label_repaint(lv_obj_t * obj);
static void main_btn_lvgl_label_repaint(lv_obj_t * obj);

/************
*** Eve cb
*************/
static void main_btn_hello_cb(lv_event_t * e);

/************
*** Other
*************/

/* OBJ List main */
static obj_class_para main_list[] = {
    /* 0 */ {{"主界面", "main"}, OBJ_TYPE_SCREEN, {0, 0, 1024, 600}, 0xFF, main_bg_repaint},
    /* 1 */ {{"",""}, OBJ_TYPE_BUTTON, {0, 0, 300, 200}, 0, main_btn_repaint, main_btn_hello_cb},
    /* 2 */ {{"你好","Hello!"}, OBJ_TYPE_LABEL, {0, 0, 0, 0}, 1, main_btn_label_repaint},
    /* 3 */ {{"LVGL","LVGL"}, OBJ_TYPE_LABEL, {0, 0, 0, 0}, 1, main_btn_lvgl_label_repaint, NULL, &sty_lvgl_label},
};

/********************************************************************************
 * OBJ EVENT CB
 ********************************************************************************/

static void main_btn_hello_cb(lv_event_t * e)
{
    if (lv_event_get_code(e) == LV_EVENT_RELEASED) {
        LVM_LOGI("hello\n");
    }
}

/********************************************************************************
 * OBJ REPAINT
 ********************************************************************************/

static void main_bg_repaint(lv_obj_t * obj)
{
    lv_obj_set_style_bg_color(obj, lv_color_make(0x00, 0x06, 0x1c), 0);
}

static void main_btn_repaint(lv_obj_t * obj)
{
    lv_obj_center(obj);
}

static void main_btn_label_repaint(lv_obj_t * obj)
{
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, -30);
}

static void main_btn_lvgl_label_repaint(lv_obj_t * obj)
{
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 30);
}

/********************************************************************************
 * OBJ STYLE INIT
 ********************************************************************************/

/**
 * @brief Init main obj style
 * 
 */
static void init_main_style(void)
{
    lv_style_reset(&sty_lvgl_label);
    lv_style_init(&sty_lvgl_label);
    lv_style_set_text_color(&sty_margin_textarea, lv_color_make(0xff, 0x00, 0x00));
}


/********************************************************************************
 * OTHER PRIVATE FUNCTION
 ********************************************************************************/

/********************************************************************************
 * PUBLIC API
 ********************************************************************************/

/**
 * @brief Delete the main funtion
 * 
 */
void delete_main_list(void)
{
    if (main_list->obj != NULL) {
        lv_obj_del(main_list->obj);
        main_list->obj = NULL;
    }
}

/**
 * @brief Create a main list 
 * 
 */
void create_main_list(void)
{
    obj_list list_main = {
        .name = "main",
        .plist = main_list,
        .obj_num = NUMBER_OF_OBJ_LIST(main_list),
        .style_init = init_main_style,
    };

    create_obj_list(&list_main);
}
