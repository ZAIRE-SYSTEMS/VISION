#include <globalVar.h>



void app_main(void)
{
    zaire_err_t ret;
    // Initialize NVS -- ALWAYS FIRST
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    if(ret != ZAIRE_OK)esp_restart();

    // Initialize ZAIRE Systems
    if(zaire_systems_init() != ZAIRE_OK){printf("INIT Failed!\n");vTaskDelay(4000 / portTICK_PERIOD_MS);esp_restart();}

    

    xTaskCreate(walkie_btn_task_run, "walkie_btn_task_run", 8184, NULL, 4, &walkie_btn_task_handler);
    xTaskCreate(purpose_left_btn_task_run, "purpose_left_btn_task_run", 4096, NULL, 4, &purpose_left_btn_task_handler);
    xTaskCreate(purpose_right_btn_task_run, "purpose_right_btn_task_run", 4096, NULL, 4, &purpose_right_btn_task_handler);
    xTaskCreate(led_strip_run_task, "LED STRIP TASK", 4096, NULL, 2, &led_strip_task_handler);


    led_strip_handle_t led_strip = configure_led_stip();
    led_welcome_animation(led_strip);

    printf("ZAIRE System Initialized Successfully!\n");
    ret = zaire_network_settings_mode();
    if(ret != ZAIRE_OK){printf("NETWORK INIT Failed!\n");vTaskDelay(4000 / portTICK_PERIOD_MS);esp_restart();}
    start_dns_server();
}



