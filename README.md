# Alarm-with-MQTT
Designed a very rough alarm with 2 ESP 8266 with Wi-Fi chip and a Raspberry PI carries out the task of Broker (check MQTT protocol)
There are 5 main components:
  1. Raspberry PI: It's a very powerful machine that carries out the task of MQTT Broker, that is, of directing messages between components using those that are called           Topics. It is both registered in a topic and publishes in it. The program that does this is the mqtt_broker.py
  2. ESP-8266: less computing power for a minor job. It's like an Arduino, so it controls inputs and outputs of certain gates. It works in C++ language. The dope thing is        that you can link these devices to Wi-Fi, so it can connect with the Broker.
  3. Motion alarm: it links with wire to the ESP-8266 and detects movement and sends a signal to the chip. 
  4. Numeric Keypad: it's the one that turns on/off the alarm by inserting a correct sequence of numbers. Even this component links wirely to the ESP-8266.
  5. Wi-Fi: obviously you'll need a Wi-Fi connection and with that the access to change the TCP and UDP gates and unlock the one of the MQTT protocol.

Alarm Operation
All components are connected to Wi-Fi. When the correct code is entered on the numeric keypad, the motion sensor activates and starts sending to the Broker whether or not it detects movement. At the same time as activating the sensor, the keypad activates a part of the script inside the broker that inserts the alarm status into the database: 1 if on 0 if off. The database is also useful because the alarm status can be changed inside the site, saving the data of the person who inserts it (email, ip). If the alarm detects movement inside the room when it is on, the Broker sends an email directly to the owner of the alarm.

There are various upgrades that can be made, such as an LCD screen on the keypad, a device that makes a sound when the code is wrong or when the motion sensor detects something and after 't' period of time the code is not entered.

It is not a very big project also due to budget, I hope it can help someone.
