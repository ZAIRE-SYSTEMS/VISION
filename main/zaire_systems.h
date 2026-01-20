#ifndef ZAIRE_SYSTEMS_H
#define ZAIRE_SYSTEMS_H

#include "globalVar.h"


#include <u8g2.h>
#include <u8g2_esp32_hal.h>
#include <esp_camera.h>
#include <usb_device_uvc.h>
#include <uvc_frame_config.h>

//initialize error types
typedef enum{
    ZAIRE_OK = 0,
    ZAIRE_ERR = !ZAIRE_OK
} zaire_err_t;


//initialize ZAIRE SYSTEMS 
#define SHORT_PRESS_DELAY   250
#define LONG_PRESS_DELAY    1500
zaire_err_t zaire_systems_init(void);
zaire_err_t zaire_systems_rst_all_pins(void);
zaire_err_t zaire_systems_spiffs_init(void);


//SYSTEM BUTTONS CONFIG
#define HIGH                        0x01
#define LOW                         0x00
#define WALKIE_BTN                  GPIO_NUM_21
#define PURPOSE_LEFT                GPIO_NUM_45
#define PURPOSE_RIGHT               GPIO_NUM_48


//ZAIRE CAMERA CONFIG
#define CAMERA_INCLUDED
#define PWDN_GPIO_NUM               (-1)
#define RESET_GPIO_NUM              (-1)
#define XCLK_GPIO_NUM               GPIO_NUM_15
#define SIOD_GPIO_NUM               CAMERA_I2C_SDA_PIN
#define SIOC_GPIO_NUM               CAMERA_I2C_SCL_PIN

#define Y9_GPIO_NUM                 GPIO_NUM_16
#define Y8_GPIO_NUM                 GPIO_NUM_17
#define Y7_GPIO_NUM                 GPIO_NUM_18
#define Y6_GPIO_NUM                 GPIO_NUM_12
#define Y5_GPIO_NUM                 GPIO_NUM_10
#define Y4_GPIO_NUM                 GPIO_NUM_8
#define Y3_GPIO_NUM                 GPIO_NUM_9 // 1
#define Y2_GPIO_NUM                 GPIO_NUM_11 //0

#define VSYNC_GPIO_NUM              GPIO_NUM_6
#define HREF_GPIO_NUM               GPIO_NUM_7
#define PCLK_GPIO_NUM               GPIO_NUM_13
#define UVC_MAX_FRAMESIZE_SIZE     (60*1024)
zaire_err_t zaire_cam_init(void);

//LIGHTS CONFIG
#define FRONT_WHITE_LED             GPIO_NUM_3
#define BACK_STRIP_LED              GPIO_NUM_46
#define LED_STRIP_LED_NUMBERS       10
#define LED_STRIP_RMT_RES_HZ        (10 * 1000 * 1000)
#define AMBER_R                     255
#define AMBER_G                     100
#define AMBER_B                     0
typedef enum{
    NORMAL = 0,
    MASTER_PAIRING = 1,
    SLAVE_PAIRING = 2,
    SYNC_PAIRING = 3,
    REMOTE_PAIRING = 4
}led_target_stage_t;
extern led_target_stage_t led_target_stage;
typedef enum {
    LED_OFF = 0,
    FRONT_WHITE_ON = 1,
    LOW_BATTERY = 2,
    BACK_BRAKE_ON = 1,
    LEFT_TURN = 2,
    RIGHT_TURN = 3
}led_target_mode_t;
extern led_target_mode_t led_target_mode[2];
led_strip_handle_t configure_led_stip();
void led_welcome_animation(led_strip_handle_t led_strip);
void led_front_white_on(void);
void led_front_white_off(void);
void led_battery_low_on(void);
void led_battery_low_off(void);
void led_right_turn(led_strip_handle_t led_strip);
void led_left_turn(led_strip_handle_t led_strip);
void led_brake_red(led_strip_handle_t led_strip);
void led_pairing_master_search_blue(led_strip_handle_t led_strip);
void led_pairing_slave_search_blue(led_strip_handle_t led_strip);
void led_pairing_sync_blue(led_strip_handle_t led_strip);
void led_pairing_complete(led_strip_handle_t led_strip);
void led_pairing_remote(led_strip_handle_t led_strip);
void led_off_all(led_strip_handle_t led_strip);

//I2C PINS CONFIG
#define CAMERA_I2C_MASTER_NUM           I2C_NUM_1
#define CAMERA_I2C_SCL_PIN              GPIO_NUM_5  
#define CAMERA_I2C_SDA_PIN              GPIO_NUM_4

//I2S PINS CONFIG
#define WALKIE_I2S_BCK_MIC              GPIO_NUM_2
#define WALKIE_I2S_BCK_SPK              GPIO_NUM_39
#define WALKIE_I2S_WS_MIC               GPIO_NUM_38
#define WALKIE_I2S_WS_SPK               GPIO_NUM_40
#define WALKIE_I2S_MIC                  GPIO_NUM_43
#define WALKIE_I2S_SPK                  GPIO_NUM_44
#define WALKIE_I2S_SAMPLE_RATE          15500//16000
extern const i2s_port_t REC_I2S_PORT;
extern const i2s_port_t SPK_I2S_PORT;
extern int32_t samples_32bit[128];
extern int16_t samples_16bit[128];
extern uint8_t samples_8bit[128];
extern int16_t receive_16bit[128];
extern int16_t output_16bit[256];
zaire_err_t zaire_i2s_init(void);
int I2Sread(int16_t *samples, int count);
void I2Swrite(int16_t *samples, int count);
void covert_bit(int16_t *temp_samples_16bit, uint8_t *temp_samples_8bit, uint8_t len);

//NETWORK
#define NETWORK_MAX_CONN            9
#define NETWORK_SETTINGS_SSID       "ZAIRE VIEW PORTAL"
zaire_err_t zaire_network_init();
zaire_err_t zaire_network_settings_mode();
zaire_err_t zaire_network_standard_mode();
zaire_err_t zaire_network_pairing_mode_master();
zaire_err_t zaire_network_pairing_mode_slave();
void wifi_send_ap_bssid();
zaire_err_t esp_now_mesh_init(void);
void send_data_to_mesh(uint8_t data);
void detach_peer_from_mesh(uint8_t position);
void peer_leave_mesh(void);
void esp_now_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
void esp_now_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int data_len);


//DNS SERVER
extern char dns_server_ssid[128];
extern char dns_server_bssid[128];
#define DNS_PORT                53
#define DNS_TASK_STACK_SIZE     8192
#define DNS_TASK_PRIORITY       3

//HTTP SERVER
#define MAX_HTTP_RECV_BUFFER    512


#ifdef __cplusplus
extern "C" {
#endif
void start_dns_server(void);
void stop_dns_server(void);
void register_dns_catch_all(httpd_handle_t server);
#ifdef __cplusplus
}
#endif

//SETTINGS-WEBSERVER
extern TaskHandle_t dns_task_handle;
extern httpd_handle_t web_server;
httpd_handle_t start_webserver(void);
esp_err_t main_page_get_handler(httpd_req_t *req);


//PEER MESH SYSTEM
#define DEVICE_PAIRING_NAME         "zairesystemsPairing_0" 
#define ESP_NOW_CHANNEL             7
#define DEFAULT_SCAN_LIST_SIZE      10
#define WALKIE_REQUEST_STA_MAC      0xA1
#define WALKIE_PAIRING_START        0xB0 //Alert pairing session has begun
#define WALKIE_PAIRING_DONE         0xB1 //Alert pairing session done
#define WALKIE_PAIRING_CANCEL       0xB3 //Alert pairing session being canceled
#define WALKIE_REMOVE_PEER_P0       0xC0 //Alert other devices to remove us from mesh - POSITION 0 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P1       0xC1 //Alert other devices to remove us from mesh - POSITION 1 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P2       0xC2 //Alert other devices to remove us from mesh - POSITION 2 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P3       0xC3 //Alert other devices to remove us from mesh - POSITION 3 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P4       0xC4 //Alert other devices to remove us from mesh - POSITION 4 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P5       0xC5 //Alert other devices to remove us from mesh - POSITION 5 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P6       0xC6 //Alert other devices to remove us from mesh - POSITION 6 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P7       0xC7 //Alert other devices to remove us from mesh - POSITION 7 [peer_mesh_position]
#define WALKIE_REMOVE_PEER_P8       0xC8 //Alert other devices to remove us from mesh - POSITION 8 [peer_mesh_position]

extern uint8_t new_peers;
extern uint8_t device_sta_mac[6];
extern uint8_t peer_addresses[NETWORK_MAX_CONN][6];
extern uint8_t peers_in_mesh; // 1 is us
extern uint8_t peer_mesh_position; // our position in mesh -> important for removal 

void request_sta_mac_addr(uint8_t *mac_addr);
void add_pairing_new_mesh(uint8_t *addr);


//ZAIRE WALKIE SYSTEM
#define MAX_WALKIE_PEERS 9
extern bool walkie_speak;
extern bool sendOver;
extern bool recOver;
extern bool speakOut;

typedef enum{
    NONE = 0,
    MASTER = 1,
    SLAVE = 2,
    SYNC = 3
}walkie_pairing_mode_t;
extern walkie_pairing_mode_t walkie_pairing_mode;
extern bool is_walkie_in_pairing_session;

void walkie_pairing_sequence(void);
void walkie_pairing_master(void);
void walkie_pairing_slave(void);
void walkie_pairing_sync_master(void);
void walkie_pairing_sync_slave(uint8_t *addr);
void walkie_discover_peers(void);
void walkie_pairing_close_down(void); //Turn off display after pairing session
void walkie_pairing_cancel_master(void); //Cancel pairing session MASTER
void walkie_pairing_cancel_slave(void); //Cancel pairing session SLAVE
void walkie_mute(void);
void walkie_sendData(const uint8_t *data, uint16_t len);


// ======================
// 1. USER SETTINGS (stored in NVS, survives reboot)
// ======================
typedef struct {
    char user_name[64];      // "Alex", "ZAIRE Rider", etc.
    char device_name[64];    // "ZAIRE-VISION-001", "SnowBeast"
} user_prefs_t;

// ======================
// 2. SYSTEM SETTINGS (user preferences, stored in NVS)
// ======================
typedef struct {
    uint8_t first_boot;              // 0 = new device, 1 acc in device
    uint8_t device_lang;            // 0 = English, 1 = French, etc.
    uint8_t units;                    // 0 = metric (km/h, m), 1 = imperial (mph, ft)
    uint8_t theme;                   // 0 = light, 1 = dark
    uint8_t lower_bt_volume_on_walkie;// 0 = no, 1 = yes
    uint8_t auto_bt_on_powerup;       // 0 = off, 1 = on
    uint8_t device_auto_record;      // 0 = off, 1 = on
    uint8_t device_mute_record_audio; // 0 = off, 1 = on
    // Add more user prefs here later (vibration, HUD brightness, etc.)
} system_prefs_t;

// ======================
// 3. DEVICE STATE (live/runtime data, NOT saved to flash)
// ======================
typedef struct {
    uint16_t photos_count;            // current number of photos in /media/photos/
    uint16_t videos_count;
    bool     bt_connected;            // is Bluetooth currently linked?
    bool     bt_audio_active;         // is audio streaming?
    char     bt_device_name[64];      // "Alex’s iPhone",
    uint8_t  walkie_peers_count;       // how many walkie helmets/goggles are connected
    bool     walkie_active;           // is walkie-talkie session running?
    bool     walkie_paired;           // has at least one peer been paired ever?
    float    top_speed;               // current session best (in current units)
    uint16_t top_height;              // meters or feet
    float    top_accel;               // ft/s or m/s²
    // Add live sensors here: battery %, temperature, GPS fix, etc.
} device_state_t;

// ======================
// 4. WALKIE PEER INFO STRUCTURE AND GLOBAL ARRAY
// ======================

typedef struct {
    uint8_t  id;                        // 0–8 → matches array index
    char     name[32];                  // "Alex", "Helmet #5"
    char     last_position[64];         // "Ridge lookout", "GPS: 46.8123,-121.7456"
    uint32_t last_comm_timestamp;       // Unix timestamp (seconds since 1970)
    int16_t  rssi;                      // signed! RSSI is always negative (-30 to -100)
    uint8_t  battery_level;             // 0–100%
    uint8_t  __padding[1];              // align to 128 bytes (nice for flash/JSON)
} walkie_peer_zState_t;

// ======================
// 5. DEVICE ENCODED INFO
// ======================

typedef struct {
    /* =========================
       DEVICE IDENTITY
       ========================= */
    char manufacturer[32];        // "ZAIRE SYSTEMS"
    char model_name[16];           // "ZAIRE-HELMET" - "ZAIRE VISION"
    char serial_number[24];        // Unique per unit

    /* =========================
       HARDWARE
       ========================= */
    char hardware_version[16];     // "H1.1"
    char led_hw_version[16];       // "L1.1"
    uint8_t has_leds;

    /* =========================
       REMOTE MODULE (optional)
       ========================= */
    uint8_t has_remote;
    char remote_hw_version[16];    // "R1.0"
    char remote_chip[16];          // "ESP32-S3"
    char remote_firmware[16];      // "REMOTE-0.3.1"
    char remote_serial[24];

    /* =========================
       FIRMWARE
       ========================= */
    char firmware_ver_mcu[16];     // ESP32 controller
    char firmware_ver_mpu[16];     // Allwinner / Vision OS

    /* =========================
       BUILD INFO
       ========================= */
    char build_date[16];            // YYYY-MM-DD
    char build_time[16];            // HH:MM:SS
    char build_type[8];             // DEBUG / RELEASE

} device_info_t;


// ======================
// Global instances
// ======================
extern user_prefs_t    g_user_prefs;
extern system_prefs_t  g_system_prefs;
extern device_state_t  g_device_state;
extern walkie_peer_zState_t g_walkie_peer_info[8];
extern device_info_t   g_device_info;


#endif // ZAIRE_SYSTEMS_H