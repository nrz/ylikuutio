FROM debian:stable
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get -qq update -y
RUN apt-get -qq install -y \
    cmake \
    build-essential \
    libx11-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libsdl2-dev \
    libxcursor-dev \
    libxrandr-dev \
    libxext-dev \
    libxi-dev \
    libxinerama-dev \
    git

WORKDIR /work/build
CMD cmake .. && time make -j $(nproc)
