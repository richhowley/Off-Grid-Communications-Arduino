# Off Grid Communications Arduino

This is the Arduino part of an off-grid comminication system that uses Arduinos with HC-12 transceiver modules.  This program facilitates commuincation between HC-12 radios and a web browser. Node.js is used with socket.io for event-based communication with the browser, the node-serialport module is used to read to and write from the serial port.

Arduino acts as a traffic cop routing messages recieved on the serial port, from the browser, to the HC-12 and messages recieved from the HC-12 to the serial port, destined for the browser.

