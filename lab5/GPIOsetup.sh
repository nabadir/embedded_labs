
echo 13 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio13/direction
echo 1 > /sys/class/gpio/gpio13/value

echo 12 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio12/direction
echo 1 > /sys/class/gpio/gpio12/value

echo 11 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio11/direction
echo 1 > /sys/class/gpio/gpio11/value

echo 10 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio10/direction
echo 1 > /sys/class/gpio/gpio10/value

echo 0 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio0/direction
echo 1 > /sys/class/gpio/gpio0/value