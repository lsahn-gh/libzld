LLDP(Link Layer Discovery Protocol) is a link layer protocol for gathering any information such as System name and description, Port name and description, VLAN name, IP management address and so on. These information is specified in IEEE 802.1AB and others.Currently this library supports the below specifications.

1. IEEE 802.1AB

## Build/Install Library
```sh
$ ./autogen.sh
$ ./configure
$ make
$ make install
```

## Build Tests and Examples
```sh
$ ./autogen.sh
$ ./configure --enable-tools
$ make
$ ls tools
```

