# Onboarding Exercises

## Project

* nDPI

This exercise captures live network traffic and extracts data such as **Connection ID**, **Protocol**, **Category**, and **Domain** using the nDPI engine.

## Build instruction

To build and this project. Navigate to the project root folder ('ndpi-dpi') and run the following commands in your terminal:

```
cmake -S . -B build
cmake --build build
```

## Command to run the project.

```
 sudo ./build/ndpi_dpi -i eth0 --N 30
```
 
 -i eth0: Specifies the network interfcae (e.g., eth0) provinding the live traffic.
 --N 30: Sets the maximum number of packets to process inside the DPI engine.
