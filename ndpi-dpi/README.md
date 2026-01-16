# Onboarding Exercises

## Project

* nDPI

This exercise captures the live traffic and gives Connection Id, Protocol, Category and domain.

## Build instruction

To build and this project.
Go inside the project folder (ie; ndpi-dpi)
Then follow the commands in the terminal from that folder location

```
cmake -S . -B build
cmake --build build
cd build
```
## Command to run the project.

```
 sudo ./ndpi_dpi -i eth0 --N 30
```
 
 eth0 is the Network interface which provides live traffic N max number of packets to send inside DPI engine


