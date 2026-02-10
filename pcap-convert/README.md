# Onboarding Exercises

## Project

* pcap-convert

This exercise takes a PCAP file as input and generates an output PCAP containing only the packets that satisfy user-provided conditions. It also displays the following packet statistics in the standard output:
- Total bytes & packets processed
- Total bytes & packets dropped
- Total bytes & packets written
- Total DNS packets modified

## Docker (recommended)

This repository includes a Docker-based dev environment so you can build and run the project **without installing any dependencies on the host** (other than Docker / Docker Compose).

### Prerequisites
- Docker Engine
- Docker Compose v2 (`docker compose`)

### Quick start

From the repository root (`pcap-convert`):

1) Build and start the dev container:
```bash
docker compose --env-file docker/.env -f docker/docker-compose.yml up -d --build
```

2) Open a shell inside the container:
```bash
docker compose --env-file docker/.env -f docker/docker-compose.yml exec dev sh
```

3) Build the project inside the container:
```bash
cmake -S . -B build
cmake --build build
```

4) Run the project inside the container:
```bash
./build/app/pcap-convert --vlan 5 --ip-version 4 --ttl 2 --dns-addr 10.0.0.1 --dns-port 5353 -i data/captures/x11-sample.pcap -o data/captures/x11-sample-filtered.pcap
```

The `x11-sample-filtered.pcap` will be generated in `data/captures/`.

### Stop / cleanup
From the repository root:
```bash
docker compose --env-file docker/.env -f docker/docker-compose.yml down
```

## Build instruction (native)

To build this project natively, navigate to the project root folder (`pcap-convert`) and run the following commands in your terminal:

```bash
cmake -S . -B build
cmake --build build
```

## Command to run the project

```bash
./build/app/pcap-convert --vlan 5 --ip-version 4 --ttl 2 --dns-addr 10.0.0.1 --dns-port 5353 -i data/captures/x11-sample.pcap -o data/captures/x11-sample-filtered.pcap
```

The x11-sample-filtered.pcap will be generated in data/captures folder.
