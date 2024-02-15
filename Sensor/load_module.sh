#!/bin/bash


rm -rf /dev/hc-sr04

insmod hc_sr04.ko

drv_major=$(awk "/hc-sr04/ {print \$1}" /proc/devices)

mknod /dev/hc-sr04 c $drv_major 0
