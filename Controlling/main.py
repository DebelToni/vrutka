from gpiozero import PWMLED,LED,RotaryEncoder
import time
from time import sleep
#import RPi.GPIO as GPIO
import threading

#red = PWMLED(18)
m_pwm = PWMLED(12)
m_break = LED(6)
# m_enc = RotaryEncoder(14,2,max_steps=10000)
target = 0
pw = 0.0
kp=0.2
"""
def work (): 
	global pw
	global kp
	global target

	threading.Timer(1, work).start ()
	err=0.0
	err= m_enc.steps-target*100/60
	m_enc.steps=0
	pw = pw + kp*err
	print('Error:Mew Power: ',(err, pw))
work ()
"""
try:
    while True:
	    print('Set target (r/min): ')
	    target=int(input())
	    print('New target: ',target,'r/min')
	    m_break.on()
	    m_pwm.value=1-target/100
except KeyboardInterrupt:
	pass
finally:
#	red.close()
	m_pwm.close()
	m_break.close()
#	m_enc.close()
