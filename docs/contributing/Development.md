# Development Guide

## Prerequisites
Before running the build scripts, ensure you have the following installed:

- **CMake** (>=3.15)
- **Conan** (>=2.0)
- **A C++ compiler** (GCC, Clang, or MSVC)
- **Make** or an equivalent build system

You can install Conan via:
```sh
pip install conan
```

Ensure Conan is configured correctly:
```sh
conan profile detect
```

## Project Structure
```
VolumeManager/
├── scripts/
│   ├── build_and_test.sh      # Build Debug mode & run tests
│   ├── release_and_run.sh     # Build Release mode & run
│   ├── release_only.sh        # Build Release mode (no run)
│   ├── clean.sh               # Remove build directories
├── CMakeLists.txt             # CMake configuration
├── conanfile.txt              # Conan dependencies
├── src/                       # Source code
├── include/                   # Header files
├── test/                      # Test files and cases
├── build-debug/ (ignored)      # Debug build output
├── build-release/ (ignored)    # Release build output
```

## Using the Build Scripts
All scripts should be executed from the project root.

### **1. Build and Test (Debug Mode)**
```sh
./scripts/build_and_test.sh
```
- Installs dependencies
- Configures CMake in **Debug mode**
- Builds the project
- Runs **tests**

### **2. Build and Run (Release Mode)**
```sh
./scripts/release_and_run.sh
```
- Installs dependencies
- Configures CMake in **Release mode**
- Builds the project
- Runs the compiled executable

### **3. Only Build (Release Mode)**
```sh
./scripts/release_only.sh
```
- Installs dependencies
- Configures CMake in **Release mode**
- Builds the project
- Does **not** run the executable

### **4. Clean Build Directories**
```sh
./scripts/clean.sh
```
- Deletes `build-debug/` and `build-release/`
- Useful for a fresh build

## Troubleshooting
### **1. Permission Denied When Running Scripts**
If you see a permission error, make scripts executable:
```sh
chmod +x scripts/*.sh
```

### **2. Conan Dependency Issues**
Try running:
```sh
conan profile detect
conan install . --build=missing
```

### **3. CMake Not Finding Dependencies**
Ensure Conan is setting up the toolchain correctly:
```sh
conan install . --build=missing --output-folder=.
cmake . -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
```

## Contributing
If you modify the build process, update this guide and test scripts before pushing changes:
```sh
./scripts/build_and_test.sh
./scripts/release_and_run.sh
```

Happy coding! 🚀

