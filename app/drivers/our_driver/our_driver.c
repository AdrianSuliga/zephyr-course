#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT our_driver

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_NODELABEL(green_led), gpios);

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

static int init(const struct device *dev)
{
    if (!gpio_is_ready_dt(&led)) {
        return 1;
    }

    return gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_our_driver);
