gpio.mode(3, gpio.INPUT)
gpio.mode(4, gpio.OUTPUT)
gpio.write(4, gpio.HIGH)
tmr.delay(1000000)   -- wait 2,000,000 us = 2 second
gpio.write(4, gpio.LOW)
if(gpio.read(3)==0) then os.exit(nil) end

pwm.setup(3,300,100)
pwm.setup(4,300,100)
pwm.setup(5,300,100)
pwm.setup(6,300,100)


pwm.start(3)
pwm.start(4)
pwm.start(5)
pwm.start(6)
v=400
pwm.setduty(3,v)
pwm.setduty(4,v)
pwm.setduty(5,v)
pwm.setduty(6,v)
