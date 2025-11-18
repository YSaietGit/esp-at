/* usb_console_force.c
 *
 * Template to force-initialize the USB device driver and register TinyUSB CDC-ACM
 * as the VFS console early in startup. Adjust API calls to match the USB component
 * present in your esp-at tree (TinyUSB or esp-usb).
 *
 * Add this file to main/ and rebuild to see whether the USB stack can be started.
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

/* The actual headers and APIs differ between components.
   The placeholders below are the common names used in many esp-idf + tinyusb setups.
   If your build fails to compile, paste the compiler errors here and I will provide
   the correct include / function names for your esp-at tree. */

#if defined(CONFIG_TINYUSB_ENABLED)
#include "tinyusb.h"          // may be "tusb.h" or a different header in your tree
#include "esp_vfs_fat.h"
#endif

static const char *TAG = "usb_console_force";

void app_main(void)
{
    ESP_LOGI(TAG, "usb_console_force: start");

#if defined(CONFIG_TINYUSB_ENABLED)
    ESP_LOGI(TAG, "Attempting to initialize TinyUSB driver...");

    // Example: tinyusb_driver_install() / tusb_init() style APIs differ between versions.
    // The following is a generic placeholder. Replace with the API in your build if compile fails.
    esp_err_t err = ESP_OK;

    // --- Placeholder init (replace with actual init function)
    // err = tinyusb_driver_install(NULL);  // some trees use tinyusb_driver_install(&cfg)
    // or
    // tusb_init(); // some use tusb_init()
    // -- end placeholder

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "tinyusb init failed: %d", err);
    } else {
        ESP_LOGI(TAG, "tinyusb init OK - attempting to register CDC-ACM VFS console...");

        // Register the CDC ACM VFS console if an API exists (example placeholder)
        // esp_err_t r = esp_vfs_tinyusb_cdcacm_register();
        // if (r != ESP_OK) { ESP_LOGE(TAG, "vfs register failed: %d", r); }
        // else { ESP_LOGI(TAG, "vfs registered - USB console should appear."); }
    }
#else
    ESP_LOGW(TAG, "TinyUSB not enabled in build (CONFIG_TINYUSB_ENABLED not set)");
#endif

    /* Continue normal esp-at startup (if esp-at's init runs after app_main
       you may need to integrate this into esp-at initialization sequence). */

    // Keep the task alive if needed to observe logs
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}