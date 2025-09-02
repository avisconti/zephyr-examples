/*
 * Copyright (c) 2025 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>
#include <zephyr/sys/util.h>

#ifdef CONFIG_LIS2DW12_TRIGGER
static void lis2dw12_wakeup_handler(const struct device *dev,
				    const struct sensor_trigger *trig)
{
	sensor_sample_fetch_chan(dev, SENSOR_CHAN_ACCEL_XYZ);
	printk("wake-up detected\n");
}
#endif

static void lis2dw12_config(const struct device *lis2dw12)
{
	struct sensor_value odr_attr, fs_attr;
	struct sensor_value wakeup_threshold;

	/* set LIS2DW12 accel/gyro sampling frequency to 100 Hz */
	odr_attr.val1 = 100;
	odr_attr.val2 = 0;

	if (sensor_attr_set(lis2dw12, SENSOR_CHAN_ACCEL_XYZ,
			    SENSOR_ATTR_SAMPLING_FREQUENCY, &odr_attr) < 0) {
		printk("Cannot set sampling frequency for LIS2DW12 \n");
		return;
	}

	sensor_g_to_ms2(2, &fs_attr);

	if (sensor_attr_set(lis2dw12, SENSOR_CHAN_ACCEL_XYZ,
			    SENSOR_ATTR_FULL_SCALE, &fs_attr) < 0) {
		printk("Cannot set full scale for LIS2DW12 \n");
		return;
	}

	wakeup_threshold.val1 = 2;
	wakeup_threshold.val2 = 0;

	if (sensor_attr_set(lis2dw12, SENSOR_CHAN_ACCEL_XYZ,
			    SENSOR_ATTR_UPPER_THRESH, &wakeup_threshold) < 0) {
		printk("Cannot set threshold\n");
		return;
	}

#ifdef CONFIG_LIS2DW12_TRIGGER
	struct sensor_trigger trig;

	trig.type = SENSOR_TRIG_MOTION;
	trig.chan = SENSOR_CHAN_ACCEL_XYZ;
	sensor_trigger_set(lis2dw12, &trig, lis2dw12_wakeup_handler);
#endif
}

int main(void)
{
	const struct device *const lis2dw12 = DEVICE_DT_GET_ONE(st_lis2dw12);

	if (!device_is_ready(lis2dw12)) {
		printk("%s: device not ready.\n", lis2dw12->name);
		return 0;
	}

	lis2dw12_config(lis2dw12);

	while (1) {
		k_sleep(K_SECONDS(5));
	}
}
