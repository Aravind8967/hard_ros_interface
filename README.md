# hard_ros_interface

hear I wrought a aduino code to control motors, led with ROS
to do this you should install rosserial package 
after this you can copy past code and note connection must be as per program

hear I am using Arduino mega and L293D DC-driver

led pin = 52
motor = M1 (on driver)
servo_signal_pin = 22
ultrasonic_trig = 51 
ultrasonic_echo = 50

after the connection fallow the bellow procedure

in 1st terminal write

roscore

2nd terminal
rosrun rosserial_arduino serial_node.py /dev/ttyUSB0           (if you are using Arduino mega)
rosrun rosserial_arduino serial_node.py /dev/ttyACM0           (if you are using Arduino uno)

3rd terminal
rostopic list   ( hear you can see all the publisher and subcriber nodes)

= = = = To subscribe ultrasonic data copy bellow command = = = =

rostopic echo /ultra

= = = = To run motor forward, backward and stop = = = =

rostopic pub /motor_forward std_msgs/String "data: ''"       ( forward )
rostopic pub /motor_backard std_msgs/String "data: ''"       ( backwad )
rostopic pub /motor_stop std_msgs/String "data: ''"          ( stop )

= = = = To control servo insert angle at last = = = = 

rostopic pub /servo std_msgs/UInt16 "data: 90"               ( cahange the angle as you need replace angle with 90 )

= = = = To control LED = = = = 

rostopic pub /toggle_led std_msgs/Empty "{}"
