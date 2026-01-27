# Onboarding Exercises

## Project

* pcap-convert

This exercise take a pcap file as input and gives the output pcap file which contains the packets satisfies the condition provided by the user. It also display the following packet stats in the standard output:
- Total bytes & packets processed
- Total bytes & packets dropped
- Total bytes & packets written
- Total DNS packets modified

## Build instruction

To build and this project.
Go inside the project folder (ie; pcap-convert)
Then follow the commands in the terminal from that folder location

```
cmake -S . -B build
cmake --build build
cd build
```

After executing these commands and before running the project take one pcap file from the folder Pcapfiles, rename it to input.pcap (if name is not input.pcap) and copy it to the build folder.

## Command to run the project

```
./build/pcap-convert --vlan 5 -ip-version 4 --ttl 2 --dns-addr 10.0.0.1 --dns-port 5353 -i Pcapfiles/input.pcap -o Pcapfiles/output.pcap
```

The output.pcap will be generated in build folder.
