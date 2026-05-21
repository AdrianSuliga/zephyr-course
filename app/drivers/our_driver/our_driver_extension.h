#ifndef OUR_DRIVER_EXTENSION_H
#define OUR_DRIVER_EXTENSION_H

#ifdef __cplusplus
extern "C" {
#endif

#define OUR_DRIVER_CALIBRATION_DEFAULT 2137

int modify_device_instance(const struct device *dev, uint32_t new_value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OUR_DRIVER_EXTENSION_H */
