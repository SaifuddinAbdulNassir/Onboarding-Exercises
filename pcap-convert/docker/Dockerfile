FROM alpine:3.20

RUN apk add --no-cache \
    bash \
    build-base \
    cmake \
    ninja \
    pkgconf \
    git \
    ca-certificates \
    linux-headers \
    libpcap-dev \
    openssl-dev

# Make it easier for CMake to find things installed in /usr/local
ENV CMAKE_PREFIX_PATH=/usr/local

# PcapPlusPlus
ARG PCPPP_REF=v24.09
RUN git clone --depth 1 --branch "${PCPPP_REF}" https://github.com/seladb/PcapPlusPlus.git /tmp/PcapPlusPlus && \
    cmake -S /tmp/PcapPlusPlus -B /tmp/PcapPlusPlus/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build /tmp/PcapPlusPlus/build -j && \
    cmake --install /tmp/PcapPlusPlus/build && \
    rm -rf /tmp/PcapPlusPlus
       
# cxxopts (header-only; install headers into /usr/local/include) ----
ARG CXXOPTS_REF=v3.2.0
RUN git clone --depth 1 --branch "${CXXOPTS_REF}" https://github.com/jarro2783/cxxopts.git /tmp/cxxopts && \
    cmake -S /tmp/cxxopts -B /tmp/cxxopts/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build /tmp/cxxopts/build -j && \
    cmake --install /tmp/cxxopts/build && \
    mkdir -p /usr/local/include/cxxopts && \
    install -m 0644 /tmp/cxxopts/include/cxxopts.hpp /usr/local/include/cxxopts/cxxopts.hpp && \
    rm -rf /tmp/cxxopts

# libfort (header-only; install headers into /usr/local/include) ----
ARG LIBFORT_REF=v0.4.2
RUN git clone --depth 1 --branch "${LIBFORT_REF}" https://github.com/seleznevae/libfort.git /tmp/libfort && \
    cmake -S /tmp/libfort -B /tmp/libfort/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build /tmp/libfort/build -j && \
    cmake --install /tmp/libfort/build && \
    mkdir -p /usr/local/include/libfort && \
    for f in fort.hpp fort.h; do for d in include lib; do src="/tmp/libfort/$d/$f"; [ -f "$src" ] && install -m 0644 "$src" "/usr/local/include/libfort/$f" && break; done; done && \
    rm -rf /tmp/libfort

WORKDIR /workspace/app

CMD ["sh", "-lc", "sleep infinity"]
