#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

static const struct device *our_driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

int main(void)
{
    struct sensor_value val;

    while (true) {
        LOG_INF("LED ON");
        sensor_sample_fetch(our_driver);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
        
        LOG_INF("LED OFF");
        sensor_channel_get(our_driver, SENSOR_CHAN_PRIV_START, &val);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }

    return 0;
}
