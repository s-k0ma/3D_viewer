FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    gcc \
    g++ \
    make \
    pkg-config \
    qt6-base-dev \
    qt6-base-dev-tools \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    libqt6widgets6 \
    libqt6printsupport6 \
    libqt6openglwidgets6 \
    libqt6gui6 \
    libgl1-mesa-dev \
    libopengl-dev \
    mesa-common-dev \
    libglu1-mesa-dev \
    libxkbcommon-x11-0 \
    libgtest-dev \
    lcov \
    valgrind \
    clang-format \
    doxygen \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir -p build && \
    cd build && \
    cmake ../view && \
    make -j$(nproc)

CMD ["./build/viewer_front"]