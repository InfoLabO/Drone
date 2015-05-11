# DRONE

## Monitoring the battery voltage

### General

Since most of the model aircraft batteries have not protection circuit integrated, it is important to monitoring the battery to be sure that we do not over empty it. Over emptying battery could irremediably damage it. The capacity of a LiPo Battery is related to the voltage of it.

The monitoring is done by using an analog port of Arduino board. Since the maximum voltage recommended for theses port is 5V (for 5V board like Uno or Leonardo), we use a voltage divider. The ratio we use is 1/n where n is the cell number of the battery.

### LiPo cell voltage

We use the 3 cells 3700mAh 35C KyPOM battery.

Battery specifications :
* Recommended minimum cell voltage : x.xV
* Recommended maximum cell voltage : x.xV

Our library :
* Minimum cell voltage alert : x.xV
* Low cell voltage alert : x.xV
* 25% capacity before low voltage alert : x.xV
* 50% capacity : x.xV
* 75% capacity : x.xV
* 100% capacity : x.xV

### Experimentation

Since the ground is a convention, all grounds have to be joined.
On the drone this should not be a problem since there is only one current source. But if you use different current sources for the monitored one and the Arduino board during experimentation do not forget to joined grounds together.

### Todo

* Integrate the relation between capacity percent and voltage.
* Make a library from the loop function.

