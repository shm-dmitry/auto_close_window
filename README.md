This project allows auto-open and auto-close your windows.
Project consists schematics of 3 modules and firmware for 2 controllers

In-door modules:
==============

1. Placed on window neare handle. It controls handle state (via hall sensor and magnet) and allows to you to push button open or close manually
Also this module connected to WIFI and allows to to control your window from any smart house server (via MQTT protocol).
2. Placed on up-side window frame. Contains servo, receives commands from module#1 and executes it.

Out-door module:
==============

1. Listen for a noise and check air quality. Sends information to your smart house via 443MHZ channel. 

Project status
==============

| Hardware | status |
| ---- | ---- |
| Indoor schema :: near-handle module | OK |
| Indoor schema :: servo module | OK |
| Outdoor module schema | not checked yet |

| Firmware | status |
| ---- | ---- |
| Indoor firmware :: hardware sensors - hall, switch and soft lock | OK |
| Indoor firmware :: touchpads | OK |
| Indoor firmware :: servo control and calibration | OK |
| Indoor firmware :: led indication | OK |
| Indoor firmware :: controller | OK |
| Outdoor firmware :: BMP280 | no |
| Outdoor firmware :: SGP30 | no |
| Outdoor firmware :: Noise sensor | no |
| Outdoor firmware :: Data transmitter | no |


