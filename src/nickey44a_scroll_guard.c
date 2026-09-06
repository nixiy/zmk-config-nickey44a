/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#define DT_DRV_COMPAT nixiy_input_processor_scroll_guard

#include <zephyr/device.h>
#include <zephyr/input/input.h>
#include <zephyr/sys/util.h>

#include <drivers/input_processor.h>

#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int scroll_guard_handle_event(const struct device *dev, struct input_event *event,
                                     uint32_t limit, uint32_t unused,
                                     struct zmk_input_processor_state *state) {
    ARG_UNUSED(dev);
    ARG_UNUSED(unused);
    ARG_UNUSED(state);

    if (event->type != INPUT_EV_REL ||
        (event->code != INPUT_REL_WHEEL && event->code != INPUT_REL_HWHEEL)) {
        return ZMK_INPUT_PROC_CONTINUE;
    }

    if (event->value > (int32_t)limit || event->value < -(int32_t)limit) {
        LOG_WRN("Discarded anomalous scroll delta %d (limit %u)", event->value, limit);
        return ZMK_INPUT_PROC_STOP;
    }

    return ZMK_INPUT_PROC_CONTINUE;
}

static struct zmk_input_processor_driver_api scroll_guard_driver_api = {
    .handle_event = scroll_guard_handle_event,
};

#define SCROLL_GUARD_INST(n)                                                                     \
    DEVICE_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL,                              \
                          CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &scroll_guard_driver_api);

DT_INST_FOREACH_STATUS_OKAY(SCROLL_GUARD_INST)
