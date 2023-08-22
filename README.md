This project allows auto-open and auto-close your windows.
Project consists schematics of 3 modules and firmware for 2 controllers

Project re-started

In-door modules:
==============

1. Placed on window neare handle. It controls handle state (via hall sensor and magnet) and allows to you to push button open or close manually
Also this module connected to WIFI and allows to to control your window from any smart house server (via MQTT protocol).
2. Placed on up-side window frame. Contains servo, receives commands from module#1 and executes it.

Out-door module:
==============

1. Listen for a noise and check air quality. 

Project status
==============

| Hardware | status |
| ---- | ---- |
| Indoor schema :: near-handle module | no |
| Indoor schema :: servo module | no |
| Indoor schema :: digital channel to outdoor schema | no |
| Outdoor module schema :: microcontroller and its periphery | no |
| Outdoor module schema :: sensors | no |

| Board | status |
| ---- | ---- |
| Indoor board :: near-handle module | no |
| Indoor board :: servo module | no |
| Outdoor module board | no |

| Firmware | status |
| ---- | ---- |
| Indoor firmware :: hardware sensors - hall, switch and soft lock | no |
| Indoor firmware :: buttons | no |
| Indoor firmware :: servo control and calibration | no |
| Indoor firmware :: led indication | no |
| Indoor firmware :: controller | no |
| Outdoor firmware :: BMP280 | no |
| Outdoor firmware :: SGP30 | no |
| Outdoor firmware :: Noise sensor | no |
| Outdoor firmware :: Sensor value filters and controller | no |
| Outdoor firmware :: Data transmitter | no |
