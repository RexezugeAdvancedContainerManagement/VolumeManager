# Use an official Ubuntu image as the base
FROM ubuntu:22.04 AS builder

# Set environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install required dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    make \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Install Conan using pip
RUN pip3 install conan

RUN conan profile detect

# Set the working directory inside the container
WORKDIR /app

# Copy the entire project into the container
COPY . .

# Create and set the build directory
RUN mkdir -p build-release

# Run the release build script
RUN chmod +x scripts/release_and_run.sh && \
    ./scripts/release_and_run.sh

FROM ubuntu:22.04 AS runtime

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install only the essential runtime dependencies
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy the compiled binary from the builder stage
COPY --from=builder /app/build-release/VolumeManager .

# Set the entrypoint to run the compiled program
CMD ["./VolumeManager"]
