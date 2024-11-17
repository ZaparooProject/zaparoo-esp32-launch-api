# TapTo Esp32 Launch Api
This libary provides a convenient, rest like client to launch games via the [Zaparoo](https://tapto.wiki/Main_Page) platform. The client utilizes the provided web [API](https://tapto.wiki/API) and handles the complexities of working with websockets synchronously within a Ardunio loop.

## Required Libaries
* ArduinoJson
* ArdunioWebsockets
* UUID

## Basic Usage

Setup a client and launch a game (launch expects a [TapScript](TapScript) formatted String).
```c++
TapToLaunchApi client;
client.url("ws://tapToIp:7497");
client.launch("**launch.random:snes,nes");
```
## Example Projects
In addtion to the included example, here are some projects using this library.
* [Zaparoo Esp32](https://github.com/v1605/Zaparoo-esp32)
