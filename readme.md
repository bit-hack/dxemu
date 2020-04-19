# DXEMU

DXEMU is an emulation layer for playing old games that require an early version of DirectX.

The primary use here is to enable old games that use DirectX to be fully playable again with modern versions of Windows.
It reimplements the DirectDraw and DirectInput API using only portable Win32 and GDI calls.

Modern operating systems and hardware have developed far from what was in use at the time these old games were released.
This has lead to many problems when running old games as many incompatibilities have developed.
By reimplementing the DirectX APIs we can provide the same interface an old game expects and emulate the expected behaviour correctly for modern PCs.


## Using DXEMU

- Unzip the latest DLL files from the release folder into the same folder as your games executable


## Features

- Bypass "exlusive mode" allowing old games to run in a window, cooperatively with other applications.
- Fix color palette issues when using original DirectDraw.


## Supported games

- Fallout 1
- Fallout 2


## Roadmap

- Reduce keyboard and mouse input lag
- Support more games
- Support more DirectDraw and DirectInput functionality
- Implement DirectSound API
- Implement a config file for customizations
- Implement a log file for diagnostics


## Screenshots

![](screenshots/fallout.jpg?raw=true "Fallout 1")
