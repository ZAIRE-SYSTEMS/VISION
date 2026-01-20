idf_component_register(SRCS
                    "settings_config.c"
                    "dns_server.c"
                    "led_config.c"
                    "task_config.c"
                    "walkie_config.c"
                    "zaire_network_config.c"
                    "zaire_i2s_config.c"
                    "zaire_cam_config.c"
                    "zaire_systems.c"
                    "main.c"
                    INCLUDE_DIRS ".")



spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)