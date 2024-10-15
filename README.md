# TapTo Esp32 Launch Api
This libary provides a convenient, rest like client to launch games via the [TapTo](https://tapto.wiki/Main_Page) platform. The client utilizes the provided web [API](https://tapto.wiki/API) and handles the complexities of working with websockets synchronously.

## Required Libaries
ArduinoJson
ArdunioWebsockets
UUID

## Basic Usage

Setup a client and launch a game (launch expects a [TapScript](TapScript) formatted String).
```c++
TapToLaunchApi client;
client.url("ws://tapToIp:7497");
client.launch("**launch.random:snes,nes");
```
