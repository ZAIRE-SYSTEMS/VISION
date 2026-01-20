#ifndef GLOBALVAR_H
#define GLOBALVAR_H




#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>

#include <nvs.h>
#include <nvs_flash.h>

#include <sys/unistd.h>
#include <sys/stat.h>

#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <freertos/task.h>
#include <freertos/ringbuf.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

#include <esp_flash.h>
#include <esp_wifi.h>
#include <esp_netif.h>
#include <esp_timer.h>
#include <esp_now.h>
#include <esp_mac.h>
#include <esp_err.h>
#include <esp_log.h>
#include <esp_spiffs.h>
#include <esp_event.h>
#include <esp_vfs.h>
#include <esp_vfs_fat.h>
#include <esp_http_server.h>
#include <esp_netif_ip_addr.h>
#include <esp_system.h>

#include <lwip/sockets.h>
#include <lwip/inet.h>

#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/i2s.h>
#include <driver/uart.h>
#include <led_strip.h>

// Include ZAIRE SYSTEMS
#include "zaire_systems.h"

//BT JDY-67 COMMANDS
#include "jdy_cmd_list.h"


//Task
#define TASK_HOLD_DELAY             (10)
#define TASK_HOLD_DELAY_FIVE_SEC    (1000 * 5)
#define TASK_HOLD_DELAY_MINUTE      (1000 * 60)
extern TaskHandle_t walkie_btn_task_handler;
extern TaskHandle_t purpose_left_btn_task_handler;
extern TaskHandle_t purpose_right_btn_task_handler;
extern TaskHandle_t display_task_handler;
extern TaskHandle_t jdy67_task_handler;
extern TaskHandle_t walkie_task_handler;
extern TaskHandle_t led_strip_task_handler;

void walkie_btn_task_run(void *vpParam);
void purpose_left_btn_task_run(void *vpParam);
void purpose_right_btn_task_run(void *vpParam);
void display_task_run(void *vpParam);
void display_timer_run(void *vpParam);
void jdy67_task_run(void *vpParam);
void walkie_task_run(void *vpParm);
void led_strip_run_task(void *vpParam);

#endif // GLOBALVAR_H