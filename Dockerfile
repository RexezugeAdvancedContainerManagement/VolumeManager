# Stage 1: Install system dependencies and Conan
FROM ubuntu:22.04 AS conan

WORKDIR /build

# Install system dependencies
RUN apt-get update && apt-get install -y \
    software-properties-common \
    build-essential \
    cmake \
    gcc-12 g++-12 \
    python3 python3-pip python3-venv \
    git && \
    rm -rf /var/lib/apt/lists/*

# Set GCC 12 as the default compiler
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100

# Install Conan (latest version)
RUN pip3 install --upgrade conan

# Verify installation
RUN conan --version && g++ --version && cmake --version

# Copy Conan and CMake configuration files
COPY conanfile.txt CMakeLists.txt CMakeUserPresets.json ./
COPY include/ include/

# Configure Conan and install dependencies
RUN conan profile detect || conan profile list && \
    conan install . --output-folder=build --build=missing

# Stage 2: Build the application
FROM ubuntu:22.04 AS builder

WORKDIR /app

# Install required build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gcc-12 g++-12 \
    && rm -rf /var/lib/apt/lists/*

# Set GCC 12 as the default compiler
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100

# Copy dependencies from Conan stage
COPY --from=conan /build /app

# Copy source files separately to avoid unnecessary recompilation
COPY src/ src/
COPY test/ test/
COPY scripts/ scripts/
COPY include/ include/
COPY CMakeLists.txt ./

# Build the project using CMake
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --parallel $(nproc)

# Stage 3: Create a minimal runtime container
FROM ubuntu:22.04 AS runtime

WORKDIR /app

# Install only runtime dependencies (if needed)
RUN apt-get update && apt-get install -y \
    libstdc++6 && \
    rm -rf /var/lib/apt/lists/*

# Copy the compiled binary from the builder stage
COPY --from=builder /app/build/VolumeManager .

# Set entry point to execute the application
CMD ["./VolumeManager"]
