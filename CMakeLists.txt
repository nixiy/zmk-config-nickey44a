# SPDX-License-Identifier: GPL-2.0-or-later

zephyr_library()
# The guard implements ZMK's input-processor API, whose public header is
# provided by the ZMK application rather than the Zephyr SDK.
zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)
zephyr_library_sources(src/nickey44a_iqs7211e_init.c)
zephyr_library_sources(src/nickey44a_scroll_guard.c)
