#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <our_driver_extension.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    while (true) {
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }

    return 0;
}
