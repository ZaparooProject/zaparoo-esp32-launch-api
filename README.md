# Zaparoo Esp32 Launch Api
This libary provides a convenient, rest like client to launch games via the [Zaparoo](https://tapto.wiki/Main_Page) platform. The client utilizes the provided web [API](https://tapto.wiki/API) and handles the complexities of working with websockets synchronously within a Ardunio loop. You can install the libary like any other ardunio libary.

## Required Libaries
* ArduinoJson
* ArdunioWebsockets
* UUID

## Basic Usage

Setup a client and launch a game (launch expects a [ZapScript](https://wiki.zaparoo.org/ZapScript) formatted String).
```c++
ZaparooLaunchApi client;
String zapUrl = "ws://ZaparooIp:7497" + String(ZaparooLaunchApi::wsPath);
client.url(zapUrl);
client.launch("**launch.random:snes,nes");
```
## Example Projects
In addtion to the included example, here are some projects using this library.
* [Zaparoo Esp32](https://github.com/ZaparooProject/zaparoo-esp32)
