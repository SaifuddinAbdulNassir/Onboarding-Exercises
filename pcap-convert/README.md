# Onboarding Exercises

## Project

* pcap-convert

This exercise takes a PCAP file as input and generates an output PCAP containing only the packets that satisfy user-provided conditions. It also displays the following packet statistics in the standard output:
- Total bytes & packets processed
- Total bytes & packets dropped
- Total bytes & packets written
- Total DNS packets modified

## Build instruction

To build this project, navigate to the project root folder (`pcap-convert`) and run the following commands in your terminal:

```
cmake -S . -B build
cmake --build build
```

## Command to run the project

```
./build/pcap-convert --vlan 5 -ip-version 4 --ttl 2 --dns-addr 10.0.0.1 --dns-port 5353 -i data/captures/x11-sample.pcap -o data/captures/x11-sample-filtered.pcap
```

The x11-sample-filtered.pcap will be generated in data/captures folder.
