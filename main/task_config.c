#include "globalVar.h"
#include "zaire_systems.h"


TaskHandle_t walkie_btn_task_handler = NULL;
TaskHandle_t purpose_left_btn_task_handler = NULL;
TaskHandle_t purpose_right_btn_task_handler = NULL;
TaskHandle_t display_task_handler = NULL;
TaskHandle_t bk3266_task_handler = NULL;
TaskHandle_t walkie_task_handler = NULL;
TaskHandle_t led_strip_task_handler = NULL;

static bool right_special_click = false;


void purpose_right_btn_task_run(void *vpParam){
    
    while (1)
    {
        // if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
            
        //     vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //     if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
        //         vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
        //         while (1){ // While on hold, decrease BT volume 0-16

        //             bk3266_send_cmd(PLAYER_VOL_UP);
        //             printf("vol up\n");
        //             vTaskDelay(pdMS_TO_TICKS(750));
        //             if(gpio_get_level(PURPOSE_RIGHT) != HIGH)break;
        //         }
            
        //     }else{
        //         vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //         if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == HIGH && gpio_get_level(WALKIE_BTN) == LOW){
        //             vTaskDelay(pdMS_TO_TICKS(250));
        //             while (1){ // While on hold, go back to prev media track 
        //                 bk3266_send_cmd(PLAYER_MEDIA_NXT);
        //                 printf("next\n");
        //                 vTaskDelay(pdMS_TO_TICKS(2500));
        //                 if(gpio_get_level(PURPOSE_RIGHT) != HIGH) break;
        //             }

        //         }else{ // Turn on Goggle display -> Cycle through display menu
        //             // if(display_special_on == false){
        //             //     display_en = HIGH;
        //             //     display_timer = 3000;
        //             //     display_button_target +=1;
        //             //     if(display_button_target > 6)display_button_target = 1;
        //             //     display_quick_show_menu();
        //             // }else{
        //             //     right_special_click = true;
        //             // }
        //         }
        //     }
        //}

        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
}

void purpose_left_btn_task_run(void *vpParam){
    
    while (1)
    {
        // if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){

        //     vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //     if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
        //         vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
        //         while (1){ // While on hold, increase bt volume 0-16
        //             bk3266_send_cmd(PLAYER_VOL_DWN);
        //             vTaskDelay(pdMS_TO_TICKS(750));
        //             printf("vol dwn\n");
        //             if(gpio_get_level(PURPOSE_LEFT) != HIGH)break;
        //         }
            
        //     }else{
        //         vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //         if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
        //             vTaskDelay(pdMS_TO_TICKS(250));
        //             while (1){ // while on hold, go to next media track
        //                 printf("prev\n");
        //                 bk3266_send_cmd(PLAYER_MEDIA_PRV);
        //                 vTaskDelay(pdMS_TO_TICKS(2500));
        //                 if(gpio_get_level(PURPOSE_LEFT) != HIGH) break;
        //             }

        //         }else{
        //             bk3266_PP_CALL();
        //             printf("PP\n");
        //             vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //         }
        //     }
        // }else if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH) {
        //     vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //     if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
            
        //         vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //     }else if(gpio_get_level(PURPOSE_LEFT) == HIGH && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH){
        //         vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
        //         double_quick_buzz();
        //         camera_take_picture();
        //         printf("photo\n");
        //         vTaskDelay(pdMS_TO_TICKS(LONG_PRESS_DELAY));
        //     }
            
        //}
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }
}

void walkie_btn_task_run(void *vpParam){
    
    while (1)
    {
        // if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH){
        //     vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //     if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == HIGH){
        //         if(is_walkie_on || is_walkie_mute == false){
        //             while (gpio_get_level(WALKIE_BTN) == HIGH){
        //                 walkie_speak = true;
        //                 printf("on\n");
        //                 vTaskDelay(pdMS_TO_TICKS(10));
        //             }
        //             walkie_speak = false;
        //             vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));
        //         }
        //     }else if(gpio_get_level(PURPOSE_LEFT) == LOW && gpio_get_level(PURPOSE_RIGHT) == LOW && gpio_get_level(WALKIE_BTN) == LOW){
        //          if(is_walkie_on == true){walkie_mute(); vTaskDelay(pdMS_TO_TICKS(SHORT_PRESS_DELAY));}
        //     }
        // }
        vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));
    }

}

void led_strip_run_task(void *vpParam){

        led_strip_handle_t led_strip = configure_led_stip();
        led_welcome_animation(led_strip);

        while (1)
        {
            vTaskDelay(pdMS_TO_TICKS(TASK_HOLD_DELAY));

        }
        

}