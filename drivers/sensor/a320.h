#pragma once
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>
struct a320_data {
    uint16_t x_position;
    uint16_t y_position;
};

struct a320_config {
    struct i2c_dt_spec bus;
    struct k_mutex polling_mutex;
#if DT_INST_NODE_HAS_PROP(0, nrst_gpios)
    struct gpio_dt_spec nrst_gpio;
#endif
#if DT_INST_NODE_HAS_PROP(0, motion_gpios)
    struct gpio_dt_spec motion_gpio;
#endif
#if DT_INST_NODE_HAS_PROP(0, orient_gpios)
    struct gpio_dt_spec orient_gpio;
#endif
#if DT_INST_NODE_HAS_PROP(0, shutdown_gpios)
    struct gpio_dt_spec shutdown_gpio;
#endif
};

static const struct a320_config a320_cfg_0 = {
    .bus = I2C_DT_SPEC_INST_GET(0),
#if DT_INST_NODE_HAS_PROP(0, nrst_gpios)
    .nrst_gpio = GPIO_DT_SPEC_INST_GET(0, reset_gpios),
#endif
#if DT_INST_NODE_HAS_PROP(0, motion_gpios)
    .motion_gpio = GPIO_DT_SPEC_INST_GET(0, reset_gpios),
#endif
#if DT_INST_NODE_HAS_PROP(0, orient_gpios)
    .orient_gpio = GPIO_DT_SPEC_INST_GET(0, reset_gpios),
#endif
#if DT_INST_NODE_HAS_PROP(0, shutdown_gpios)
    .shutdown_gpio = GPIO_DT_SPEC_INST_GET(0, reset_gpios),
#endif
};

// A320 Register Defines
#define Product_ID 0x00
#define Revision_ID 0x01
#define Motion 0x02
#define Delta_X 0x03
#define Delta_Y 0x04
#define SQUAL 0x05
#define Shutter_Upper 0x06
#define Shutter_Lower 0x07
#define Maximum_Pixel 0x08
#define Pixel_Sun 0x09
#define Minimum_Pixel 0x0a
#define Pixel_Grab 0x0b
#define CRC0 0x0c
#define CRC1 0x0d
#define CRC2 0x0e
#define CRC3 0x0f

#define Self_Test 0x10
#define Configuration_Bits 0x11
#define LED_Control 0x1a
#define IO_Mode 0x1c
#define Motion_Control 0x1d
#define Observation 0x2e
#define Soft_RESET 0x3a
#define Shutter_Max_Hi 0x3b
#define Shutter_Max_Lo 0x3c
#define Inverse_Revision_ID 0x3e
#define Inverse_Product_ID 0x3f
#define OFN_Engine 0x60
#define OFN_Resolution 0x62
#define OFN_Speed_Control 0x63
#define OFN_Speed_ST12 0x64
#define OFN_Speed_ST21 0x65
#define OFN_Speed_ST23 0x66
#define OFN_Speed_ST32 0x67
#define OFN_Speed_ST34 0x68
#define OFN_Speed_ST43 0x69
#define OFN_Speed_ST45 0x6a
#define OFN_Speed_ST54 0x6b
#define OFN_AD_CTRL 0x6d
#define OFN_AD_ATH_HIGH 0x6e
#define OFN_AD_DTH_HIGH 0x6f
#define OFN_AD_ATH_LOW 0x70
#define OFN_AD_DTH_LOW 0x71
#define OFN_Quantize_CTRL 0x73
#define OFN_XYQ_THRESH 0x74
#define OFN_FPD_CTRL 0x75
#define OFN_Orientation_CTRL 0x77

/* Detection */
#define BIT_MOTION_MOT (1 << 7)
#define BIT_MOTION_OVF (1 << 4)