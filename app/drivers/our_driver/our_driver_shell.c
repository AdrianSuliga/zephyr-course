#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

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

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmds,
    SHELL_CMD_ARG(fetch, NULL, "Turn LED ON", cmd_sample_fetch_handler, 2, 0),
    SHELL_CMD_ARG(read, NULL, "Turn LED OFF", cmd_channel_get_handler, 2, 0),
    SHELL_CMD_ARG(info, NULL, "Get driver name and readiness", cmd_info_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(sensor, &our_driver_subcmds, "Set of commands for our driver", NULL);
