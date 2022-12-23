#include "lvgl_manage.h"

/* Currently loaded interface. */
static lv_obj_t * screen_obj = NULL;
static sys_para_t sys_para = {
    .language = SYS_LANGUAGE_CHINESE,
};

/**
 * @brief Regrest Obj Create CB.
 */
static const obj_create obj_regrest[OBJ_TYPE_ALWAYS_LAST] = {
    {.type = OBJ_TYPE_SCREEN, .obj_create_cb = lv_obj_create},
    {.type = OBJ_TYPE_OBJ, .obj_create_cb = lv_obj_create},
    {.type = OBJ_TYPE_BUTTON, .obj_create_cb = lv_btn_create},
    {.type = OBJ_TYPE_LABEL, .obj_create_cb = lv_label_create},
    {.type = OBJ_TYPE_CHART, .obj_create_cb = lv_chart_create},
    {.type = OBJ_TYPE_IMG, .obj_create_cb = lv_img_create},
    {.type = OBJ_TYPE_BTNMATRIX, .obj_create_cb = lv_btnmatrix_create},
    {.type = OBJ_TYPE_TABLE, .obj_create_cb = lv_table_create},
    {.type = OBJ_TYPE_DROPDOWM, .obj_create_cb = lv_dropdown_create},
    {.type = OBJ_TYPE_SLIDER, .obj_create_cb = lv_slider_create},
    {.type = OBJ_TYPE_TEXTAREA, .obj_create_cb = lv_textarea_create},
    {.type = OBJ_TYPE_KEYBOARD, .obj_create_cb = lv_keyboard_create},
    {.type = OBJ_TYPE_LINE, .obj_create_cb = lv_line_create},
    {.type = OBJ_TYPE_BAR, .obj_create_cb = lv_bar_create},
    {.type = OBJ_TYPE_ROLLER, .obj_create_cb = lv_roller_create},
    {.type = OBJ_TYPE_SWITCH, .obj_create_cb = lv_switch_create},
    {.type = OBJ_TYPE_CALENDAR, .obj_create_cb = lv_calendar_create},
    //Add more...
};


/**
 * @brief Create a obj of list.
 * 
 * @return int 
 */
static int create_obj_of_list(obj_class_para * para)
{
    /* Step1: Create obj. */
    for (uint8_t i=0; i<OBJ_TYPE_ALWAYS_LAST; i++) {
        if (obj_regrest[i].type == para->type) {
            if (para->type == OBJ_TYPE_SCREEN) {
                para->obj = obj_regrest[i].obj_create_cb(NULL);
                screen_obj = para->obj;
                lv_scr_load(para->obj);
            } else if (para->type == OBJ_TYPE_LABEL) {
                para->obj = obj_regrest[i].obj_create_cb(para->father_obj);
                switch (sys_para.language) {
                    case SYS_LANGUAGE_ENGLISH:
                        lv_label_set_text(para->obj, para->name.English);
                        break;  //SYS_LANGUAGE_ENGLISH
                    case SYS_LANGUAGE_CHINESE:
                        lv_label_set_text(para->obj, para->name.Chinese);
                        break;  //SYS_LANGUAGE_CHINESE
                    
                    default:
                        break;  //default
                }
            } else {
                para->obj = obj_regrest[i].obj_create_cb(para->father_obj);
            }
            break;
        }
    }

    if (para->obj == NULL) {
        if (para->name.English != NULL) {
            LVM_LOGE("Obj \"%s\" Type Err!", para->name.English);
        }
        
        return CREATE_TYPE_ERR;
    }

    /* Step2: Add event cb. */
    if (para->event_cb != NULL) {
        lv_obj_add_event_cb(para->obj, para->event_cb, LV_EVENT_ALL, NULL);
    }

    /* Step3: Set pos and size. */
    lv_obj_set_pos(para->obj, para->ps.pos_x, para->ps.pos_y);
    if(para->ps.size_w * para->ps.size_h != 0) {
        lv_obj_set_size(para->obj, para->ps.size_w, para->ps.size_h);
    }

    /* Step4: Add style. */
    if (para->style != NULL) {
        lv_obj_add_style(para->obj, para->style, 0);
    }

    /* Step5: Repaint. */
    if (para->repaint_cb != NULL) {
        para->repaint_cb(para->obj);
    }
        
    return CREATE_NO_ERR;
}

/**
 * @brief Create a obj list.
 * 
 * @param list 
 * @return int 
 */
int create_obj_list(obj_list * list_para)
{
    int ret = CREATE_NO_ERR;
    obj_class_para * plist = list_para->plist;
    
    if (list_para->obj_num == 0 || plist->obj != NULL || plist == NULL) {
        if (list_para->name != NULL) {
            LVM_LOGE("List para \"%s\" Type Err!", list_para->name);
        }
        return CREATE_LIST_PARA_ERR;
    }

    if (list_para->style_init != NULL) {
        list_para->style_init();
    }

    for (int i=0; i<list_para->obj_num; i++) {
        if (plist[i].father_index < i) {
            plist[i].father_obj = plist[plist[i].father_index].obj;
        } else if (plist[i].father_index == 0xf0) {
            plist[i].father_obj = lv_layer_top();  // 0xf0 means top
        } else {
            plist[i].father_obj = screen_obj;
        }
        ret = create_obj_of_list(&plist[i]);
        if (ret != CREATE_NO_ERR) {
            return ret;
        }
    }

    return CREATE_NO_ERR;
}

/**
 * @brief LVGL Start
 * 
 * @return int 
 */
int lvgl_start(void)
{
    create_main_list();

    return 0;
}