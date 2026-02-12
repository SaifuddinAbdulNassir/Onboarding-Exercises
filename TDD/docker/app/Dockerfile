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

# Add the work directory to Cmake prefix path
ENV CMAKE_PREFIX_PATH=/usr/local

# Build/install PcapPlusPlus
ARG PCPPP_REF=v24.09
RUN git clone --depth 1 --branch "${PCPPP_REF}" https://github.com/seladb/PcapPlusPlus.git /tmp/PcapPlusPlus && \
    cmake -S /tmp/PcapPlusPlus -B /tmp/PcapPlusPlus/build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build /tmp/PcapPlusPlus/build -j && \
    cmake --install /tmp/PcapPlusPlus/build && \
    rm -rf /tmp/PcapPlusPlus

# Build/install GoogleTest
ARG GTEST_REF=v1.15.2
RUN git clone --depth 1 --branch "${GTEST_REF}" https://github.com/google/googletest.git /tmp/googletest && \
    cmake -S /tmp/googletest -B /tmp/googletest/build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      -DBUILD_GMOCK=ON \
      -DINSTALL_GTEST=ON && \
    cmake --build /tmp/googletest/build -j && \
    cmake --install /tmp/googletest/build && \
    rm -rf /tmp/googletest

# Build/install TBB
ARG TBB_REF=v2021.12.0
RUN git clone --depth 1 --branch "${TBB_REF}" https://github.com/oneapi-src/oneTBB.git /tmp/oneTBB && \
    cmake -S /tmp/oneTBB -B /tmp/oneTBB/build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      -DTBB_TEST=OFF && \
    cmake --build /tmp/oneTBB/build -j && \
    cmake --install /tmp/oneTBB/build && \
    rm -rf /tmp/oneTBB

WORKDIR /workspace/app

CMD ["sh", "-lc", "sleep infinity"]