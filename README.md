

LLDP (Link Layer Discovery Protocol) is a link-layer protocol used to exchange device information with directly connected peers.
It can advertise and collect details such as system name and description, port name and description, VLAN name, IP management address, and more.
The protocol is defined in IEEE 802.1AB and related specifications.

This library provides a lightweight and easy-to-use implementation of LLDP. Its minimal footprint and straightforward API design make it simple to integrate into networking applications, even in resource-constrained or embedded environments.

Currently, this library supports:
- IEEE 802.1AB

## Features
- Lightweight implementation of LLDP for Linux
- Easy integration into existing networking applications
- Supports core TLVs (System, Port, VLAN, IP management, et cetera)
- Easy to integrate into existing networking applications
- C/C++ support
- Includes test programs and example usage

## Build & Install
```sh
$ make build
$ ./autogen.sh
$ ./configure --prefix=$(pwd)/build
$ make
$ make install
```
This will install the library under `build` directory. You can change the install prefix using `--prefix=/path/to/dir`.

## Build Tests & Examples
```sh
$ ./autogen.sh
$ ./configure --enable-tests
$ make
$ ls tests
```
The `tests/` directory contains an example of sending a LLDP packet.

## License
See the LICENSE file for details.
