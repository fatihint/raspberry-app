#!/bin/sh

echo 21 > /sys/class/gpio/export
echo 16 > /sys/class/gpio/export
echo 27 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio21/direction
echo in > /sys/class/gpio/gpio16/direction
echo out > /sys/class/gpio/gpio27/direction
