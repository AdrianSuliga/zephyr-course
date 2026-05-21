#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include "our_driver_extension.h"

static int cmd_sample_fetch_handler(const struct shell *sh, int argc, char **argv)
{
    const struct device *driver = shell_device_get_binding(argv[1]);
    if (!driver) {
        shell_error(sh, "Could not find device %s", argv[1]);
        return -EFAULT;
    }

    int ret = sensor_sample_fetch(driver);
    if (ret != 0) {
        shell_error(sh, "Could not fetch sample, error %d", ret);
        return -EFAULT;
    }

    return 0;
}

static int cmd_channel_get_handler(const struct shell *sh, int argc, char **argv)
{
    const struct device *driver = shell_device_get_binding(argv[1]);
    if (!driver) {
        shell_error(sh, "Could not find device %s", argv[1]);
        return -EFAULT;
    }

    struct sensor_value val;

    int ret = sensor_channel_get(driver, SENSOR_CHAN_PRIV_START, &val);
    if (ret != 0) {
        shell_error(sh, "Could not get channel, error %d", ret);
        return -EFAULT;
    }

    return 0;
}

static int cmd_info_handler(const struct shell *sh, int argc, char **argv)
{
    const struct device *driver = shell_device_get_binding(argv[1]);
    if (!driver) {
        shell_error(sh, "Could not find device %s", argv[1]);
        return -EFAULT;
    }

    shell_info(sh, "Sensor \"%s\" is %s", driver->name, device_is_ready(driver) ? "ready" : "not ready");

    return 0;
}

static int cmd_set_handler(const struct shell *sh, int argc, char **argv)
{
    const struct device *driver = shell_device_get_binding(argv[1]);
    if (!driver) {
        shell_error(sh, "Could not find device %s", argv[1]);
        return -EFAULT;
    }

    int ret;
    uint32_t new_calibration_value = atoi(argv[2]);
    
    if (0 <= new_calibration_value && new_calibration_value <= 3000) {
        ret = modify_device_instance(driver, new_calibration_value);
        if (ret != 0) {
            shell_error(sh, "Failed to set %s calibration value to %u", argv[1], new_calibration_value);
            return ret;
        }

        return 0;
    } else {
        shell_error(sh, "Calibration value outside of range (0 - 3000)");
        return -ERANGE;
    }
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmds,
    SHELL_CMD_ARG(fetch, NULL, "Turn LED ON\nUsage: fetch <driver_name>", cmd_sample_fetch_handler, 2, 0),
    SHELL_CMD_ARG(read, NULL, "Turn LED OFF\nUsage: read <driver_name>", cmd_channel_get_handler, 2, 0),
    SHELL_CMD_ARG(info, NULL, "Get driver name and readiness\nUsage: info <driver_name>", cmd_info_handler, 2, 0),
    SHELL_CMD_ARG(set, NULL, "Set sensor calibration value (0 - 3000)\n Usage: set <driver_name> <value>", cmd_set_handler, 3, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(sensor, &our_driver_subcmds, "Set of commands for our driver", NULL);
