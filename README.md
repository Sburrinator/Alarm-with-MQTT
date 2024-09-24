# Alarm-with-MQTT
Designed a very rough alarm with 2 ESP 8266 with Wi-Fi chip and a Raspberry PI carries out the task of Broker (check MQTT protocol)
There are 5 main components:
  1. Raspberry PI: It's a very powerful machine that carries out the task of MQTT Broker, that is, of directing messages between components using those that are called           Topics. It is both registered in a topic and publishes in it. The program that does this is the mqtt_broker.py
  2. ESP-8266: less computing power for a minor job. It's like an Arduino, so it controls inputs and outputs of certain gates. It works in C++ language. The dope thing is        that you can link these devices to Wi-Fi, so it can connect with the Broker.
  3. Motion alarm: it links with wire to the ESP-8266 and detects movement and sends a signal to the chip. 
  4. Numeric Keypad: it's the one that turns on/off the alarm by inserting a correct sequence of numbers. Even this component links wirely to the ESP-8266.
  5. Wi-Fi: obviously you'll need a Wi-Fi connection and with that the access to change the TCP and UDP gates and unlock the one of the MQTT protocol.
