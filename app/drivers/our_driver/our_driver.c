#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "our_driver_extension.h"

LOG_MODULE_REGISTER(OurDriver, LOG_LEVEL_DBG);

#define DT_DRV_COMPAT our_driver

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static uint32_t calibration_value = OUR_DRIVER_CALIBRATION_DEFAULT;

int our_sensor_sample_fetch(const struct device *dev,
				            enum sensor_channel chan)
{
    gpio_pin_set_dt(&led, 1);
    return 0;
}

int our_sensor_channel_get(const struct device *dev,
				           enum sensor_channel chan,
				           struct sensor_value *val)
{
    gpio_pin_set_dt(&led, 0);
    return 0;
}

static DEVICE_API(sensor, api_our_driver) = {
    .sample_fetch = our_sensor_sample_fetch,
    .channel_get = our_sensor_channel_get,
};

int modify_device_instance(const struct device *dev, uint32_t new_value)
{
    LOG_INF("Callibration value for %s chagned from %u to %u",
            dev->name,
            *((uint32_t*)dev->data),
            new_value);
    
    *((uint32_t*)dev->data) = new_value;
    
    return 0;
}

static int init(const struct device *dev)
{
    if (!gpio_is_ready_dt(&led)) {
        return 1;
    }

    return gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}

DEVICE_DT_INST_DEFINE(0, init, NULL, (void*)&calibration_value, NULL, POST_KERNEL, 80, &api_our_driver);
