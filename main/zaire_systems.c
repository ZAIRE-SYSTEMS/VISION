#include <globalVar.h>
#include <zaire_systems.h>

bool is_esp_now_active;
int is_setting_on = false;
bool is_walkie_on = false;
bool is_walkie_mute = true;
uint8_t current_BT_vol = 11;
int top_speed_gps = 0;
user_prefs_t    g_user_prefs;
system_prefs_t  g_system_prefs;
device_state_t  g_device_state;
walkie_peer_zState_t g_walkie_peer_info[8];
device_info_t   g_device_info;

zaire_err_t zaire_systems_init(void)
{
    if(zaire_systems_rst_all_pins() != ZAIRE_OK)return ZAIRE_ERR;
    if(zaire_systems_spiffs_init() != ZAIRE_OK)return ZAIRE_ERR;
    //if(zaire_cam_init() != ZAIRE_OK)return ZAIRE_ERR;
    //if(zaire_i2s_init() != ZAIRE_OK)return ZAIRE_ERR;
    if(zaire_network_init() != ZAIRE_OK)return ZAIRE_ERR;

    return ZAIRE_OK;
}

zaire_err_t zaire_systems_rst_all_pins(void)
{
    uint8_t pins[30] = {GPIO_NUM_0,GPIO_NUM_1,GPIO_NUM_2,GPIO_NUM_3,GPIO_NUM_4,GPIO_NUM_5,GPIO_NUM_6,
                            GPIO_NUM_7,GPIO_NUM_8,GPIO_NUM_9,GPIO_NUM_10,GPIO_NUM_11,GPIO_NUM_12,
                            GPIO_NUM_13,GPIO_NUM_14,GPIO_NUM_15,GPIO_NUM_16,GPIO_NUM_17,GPIO_NUM_18,GPIO_NUM_19,
                            GPIO_NUM_20,GPIO_NUM_21,GPIO_NUM_38,GPIO_NUM_40,GPIO_NUM_41,GPIO_NUM_42,GPIO_NUM_45, 
                            GPIO_NUM_46 , GPIO_NUM_47 , GPIO_NUM_48};

    for(int i=0;i<30;i++){
        if(gpio_reset_pin(pins[i]) != ZAIRE_OK){
            return ZAIRE_ERR;
        }
    }
    return ZAIRE_OK;
}

zaire_err_t zaire_systems_spiffs_init(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = "storage",   // <-- must match your partition CSV label
        .max_files = 10,
        .format_if_mount_failed = true  // set false in production once stable
    };

    if(esp_vfs_spiffs_register(&conf) != ZAIRE_OK)return ZAIRE_ERR;
   

    size_t total = 0, used = 0;
    if(esp_spiffs_info(conf.partition_label, &total, &used) != ZAIRE_OK) return ZAIRE_ERR;
    printf("total: %d used: %d\n", total, used);
  
    // Optional: list files for sanity
    DIR *d = opendir("/spiffs");
    if (d) {
        struct dirent *e;
        closedir(d);
    }
    return ZAIRE_OK;
}