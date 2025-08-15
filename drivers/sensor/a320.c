#define DT_DRV_COMPAT avago_a320

#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/crc.h>
#include <zephyr/logging/log.h>

#include "a320.h"

LOG_MODULE_REGISTER(A320, CONFIG_SENSOR_LOG_LEVEL);

static int a320_read_reg(const struct device *dev, uint8_t reg_addr) {
    const struct a320_config *cfg = dev->config;
    uint8_t value = 0;

    if (!i2c_reg_read_byte_dt(&cfg->bus, reg_addr, &value)) {
        return value;
    }

    LOG_ERR("failed to read 0x%x register", reg_addr);
    return -1;
}

static int a320_sample_fetch(const struct device *dev, enum sensor_channel chan) { return 0; }

static int a320_channel_get(const struct device *dev, enum sensor_channel chan,
                            struct sensor_value *val) {
    const uint8_t ifmotion = a320_read_reg(dev, Motion);
    const uint8_t ovflow = a320_read_reg(dev, Motion);
    if ((ifmotion & BIT_MOTION_MOT) && !(ovflow & BIT_MOTION_OVF)) {
        val->val1 = a320_read_reg(dev, Delta_X);
        val->val2 = a320_read_reg(dev, Delta_Y);
        LOG_DBG("you get the x value : %d", val->val1);
        LOG_DBG("you get the y value : %d", val->val2);
    } else{
        val->val1 = 0;
        val->val2 = 0;}
    return -1;
}

static const struct sensor_driver_api a320_driver_api = {
    .sample_fetch = a320_sample_fetch,
    .channel_get = a320_channel_get,
};

static int a320_init(const struct device *dev) {

    const struct a320_config *cfg = dev->config;
    if (!device_is_ready(cfg->bus.bus)) {
        LOG_ERR("I2C bus %s is not ready!", cfg->bus.bus->name);
        return -EINVAL;
    }
    a320_read_reg(dev, Motion);
    a320_read_reg(dev, Motion);
    a320_read_reg(dev, Delta_X);
    a320_read_reg(dev, Delta_Y);
    LOG_DBG("A320 Init done, Ready to read data.");

    return 0;
}

#define A320_DEFINE(inst)                                                                          \
    struct a320_data a3200_data_##inst;                                                            \
    static const struct a320_config a3200_cfg_##inst = {.bus = I2C_DT_SPEC_INST_GET(inst)};        \
    DEVICE_DT_INST_DEFINE(inst, a320_init, NULL, &a3200_data_##inst, &a3200_cfg_##inst,            \
                          POST_KERNEL, 60, &a320_driver_api);

DT_INST_FOREACH_STATUS_OKAY(A320_DEFINE)