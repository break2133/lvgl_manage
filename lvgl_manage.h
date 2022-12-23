#ifndef _LVGL_MANAGE_H_
#define _LVGL_MANAGE_H_


#include "lvgl.h"
#include "example_main.h"
 
#define SYS_LANGUAGE_ENGLISH    0
#define SYS_LANGUAGE_CHINESE    1

#define NUMBER_OF_OBJ_LIST(_para_) (sizeof(_para_) / sizeof(_para_[0]))

#define LVGL_MANAGE_USE_LOG 1

#if LVGL_MANAGE_USE_LOG
    /* Customize your own log */
    #if !USE_PC_SIM
    #define LVM_LOGE(...)        LOG_E(__VA_ARGS__)
    #define LVM_LOGW(...)        LOG_W(__VA_ARGS__)
    #define LVM_LOGI(...)        LOG_I(__VA_ARGS__)
    #define LVM_LOGD(...)        LOG_D(__VA_ARGS__)
    #else
    #define LVM_LOGE(...)        printf(__VA_ARGS__)
    #define LVM_LOGW(...)        printf(__VA_ARGS__)
    #define LVM_LOGI(...)        printf(__VA_ARGS__)
    #define LVM_LOGD(...)        printf(__VA_ARGS__)
    #endif
#else
    #define LVM_LOGE(...)        (void)0
    #define LVM_LOGW(...)        (void)0
    #define LVM_LOGI(...)        (void)0
    #define LVM_LOGD(...)        (void)0
#endif 

typedef enum
{
    CREATE_NO_ERR=0,
    CREATE_TYPE_ERR,
    CREATE_LIST_PARA_ERR,
}CREATE_ERR;

typedef enum
{
    OBJ_TYPE_SCREEN = 0,
    OBJ_TYPE_OBJ,
    OBJ_TYPE_BUTTON,
    OBJ_TYPE_LABEL,
    OBJ_TYPE_CHART,
    OBJ_TYPE_IMG,
    OBJ_TYPE_BTNMATRIX,
    OBJ_TYPE_TABLE,
    OBJ_TYPE_DROPDOWM,
    OBJ_TYPE_SLIDER,
    OBJ_TYPE_TEXTAREA,
    OBJ_TYPE_KEYBOARD,
    OBJ_TYPE_LINE,
    OBJ_TYPE_BAR,
    OBJ_TYPE_ROLLER,
    OBJ_TYPE_SWITCH,
    OBJ_TYPE_CALENDAR,
    //Add more...
    OBJ_TYPE_ALWAYS_LAST,
} obj_type;

typedef struct 
{
    obj_type type;
    lv_obj_t * (*obj_create_cb)(lv_obj_t *);
} obj_create;

typedef struct
{
    lv_coord_t pos_x;
    lv_coord_t pos_y;
    lv_coord_t size_w;
    lv_coord_t size_h;
} pos_size;

typedef struct
{
   const char *Chinese;
   const char *English;
   //Add more...
} obj_name;


/**
 * @brief Parameters of an obj. 
 *        The data structure of an interface should be defined as an array. 
 */
typedef struct 
{
    obj_name name;                      //Obj Name(Multilingual).
    obj_type type;                      //Obj Type.
    pos_size ps;                        //Position and size of obj.
    int father_index;                   //Parent obj index in obj list.
    void (*repaint_cb)(lv_obj_t *);     //Repaint Callback Function.
    lv_event_cb_t event_cb;             //Event Callback Function.
    lv_style_t * style;                 //Point to the style to be added.
    lv_obj_t * father_obj;              //Parent obj.
    lv_obj_t * obj;                     //Point to this obj.
} obj_class_para;

typedef struct
{
    obj_class_para *plist;      //Point to first address of obj list.
    char *name;                 //Obj list name.
    void (*style_init)(void);   //Initialize all styles used by objects in the list.
    int obj_num;                //Number of obj list.
} obj_list;

typedef struct 
{
    uint8_t language;
}sys_para_t;


/************
 * OUT API
 ***********/
int create_obj_list(obj_list * list_para);
int lvgl_start(void);

#endif  //_LVGL_MANAGE_H_
