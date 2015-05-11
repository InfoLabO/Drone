# DRONE

## Monitoring battery voltage

### General information

Since the battery model used has no protection circuit integrated, it is important to monitor it. Over emptying battery could irremediably damage it. The capacity of a LiPo Battery is related to its voltage.

To monitor the battery an Arduino analog port is used. A voltage divider assembly is used to respect the maximum voltage recommended for this kind of port

### LiPo cell voltage

We use the 3 cells 3700mAh 35C KyPOM battery.

Battery specifications :
* Recommended minimum cell voltage : x.xV
* Recommended maximum cell voltage : 4.2V

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

