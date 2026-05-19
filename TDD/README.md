# Onboarding Exercises

## Projects

* TDD with googletest

This project demonstrates **Test-Driven Development (TDD)** using the [GoogleTest](https://github.com) framework to implement specific software requirements.

## Docker (recommended)

This repository includes a Docker-based dev environment so you can build and run the project **without installing any dependencies on the host** (other than Docker / Docker Compose).

### Prerequisites

- Docker Engine
- Docker Compose v2 (`docker compose`)

### Quick start

From the repository root (`TDD`):

1) Create a local env file (do not commit it):

```bash
cp docker/.env-example docker/.env
```

2) Build and start the dev container:

```bash
docker compose --env-file docker/.env -f docker/docker-compose.yml up -d --build
```

3) Open a shell inside the container:

```bash
docker compose --env-file docker/.env -f docker/docker-compose.yml exec dev sh
```

4) Build the project inside the container:

```bash
cmake -S . -B build
cmake --build build
```

5) Run the project inside the container:

```bash
./build/test/steering-tests
```

### Stop / cleanup

From the repository root:

```bash
docker compose --env-file docker/.env -f docker/docker-compose.yml down
```

## Build instruction (native)

To build this project natively. Navigate to the project root folder ('TDD') and run the following commands in your terminal:

```
cmake -S . -B build
cmake --build build
```

## Command to run the project 

* ./build/test/steering-tests
