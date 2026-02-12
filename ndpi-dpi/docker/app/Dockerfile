FROM alpine:3.20

RUN apk add --no-cache \
    autoconf \
    automake \
    build-base \
    cmake \
    ninja \
    pkgconf \
    git \
    ca-certificates \
    libtool \
    linux-headers \
    libpcap-dev \
    openssl-dev

# Add the work directory to Cmake prefix path
ENV CMAKE_PREFIX_PATH=/usr/local

# Build/install PcapPlusPlus
ARG PCPPP_REF=v24.09
RUN git clone --depth 1 --branch "${PCPPP_REF}" https://github.com/seladb/PcapPlusPlus.git /tmp/PcapPlusPlus && \
    cmake -S /tmp/PcapPlusPlus -B /tmp/PcapPlusPlus/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build /tmp/PcapPlusPlus/build -j && \
    cmake --install /tmp/PcapPlusPlus/build && \
    rm -rf /tmp/PcapPlusPlus
       
# Build/install cxxopts
ARG CXXOPTS_REF=v3.2.0
RUN git clone --depth 1 --branch "${CXXOPTS_REF}" https://github.com/jarro2783/cxxopts.git /tmp/cxxopts && \
    cmake -S /tmp/cxxopts -B /tmp/cxxopts/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build /tmp/cxxopts/build -j && \
    cmake --install /tmp/cxxopts/build && \
    mkdir -p /usr/local/include/cxxopts && \
    install -m 0644 /tmp/cxxopts/include/cxxopts.hpp /usr/local/include/cxxopts/cxxopts.hpp && \
    rm -rf /tmp/cxxopts

# Build/install libfort
ARG LIBFORT_REF=v0.4.2
RUN git clone --depth 1 --branch "${LIBFORT_REF}" https://github.com/seleznevae/libfort.git /tmp/libfort && \
    cmake -S /tmp/libfort -B /tmp/libfort/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build /tmp/libfort/build -j && \
    cmake --install /tmp/libfort/build && \
    mkdir -p /usr/local/include/libfort && \
    for f in fort.hpp fort.h; do for d in include lib; do src="/tmp/libfort/$d/$f"; [ -f "$src" ] && install -m 0644 "$src" "/usr/local/include/libfort/$f" && break; done; done && \
    rm -rf /tmp/libfort

# Build/install nDPI
ARG NDPI_REF=4.12
RUN git clone --depth 1 --branch "${NDPI_REF}" https://github.com/ntop/nDPI.git /tmp/ndpi && \
    cd /tmp/ndpi && \
    ./autogen.sh && \
    ./configure --prefix=/usr/local && \
    make -j"$(nproc)" && \
    make install && \
    rm -rf /tmp/ndpi

WORKDIR /workspace/app

CMD ["sh", "-lc", "sleep infinity"]
