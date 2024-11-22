# Compiler and Flags
CXX=g++
CXX_STANDARD=-std=c++17
CXX_WARNINGS=-Wall -g
CXX_DEPFLAGS=-MMD
CXX_INCLUDE_DIRS=$(shell find . -name '*.h' -exec dirname {} \; | sort -u | sed 's/^/-I/') -I/opt/homebrew/include
CXXFLAGS=$(CXX_STANDARD) $(CXX_WARNINGS) $(CXX_DEPFLAGS) $(CXX_INCLUDE_DIRS)

# Linker and Libraries
BOOST_LIB_DIR=/opt/homebrew/lib
BOOST_LIBS=-lboost_system
LDFLAGS=-L$(BOOST_LIB_DIR) $(BOOST_LIBS)

# Build Directories and Executable
BUILD_DIR=build
EXEC=chess

# Source Files and Build Artifacts
CCFILES=$(shell find . -name '*.cc')
OBJECTS=$(patsubst %.cc,$(BUILD_DIR)/%.o,$(CCFILES))
DEPENDS=$(patsubst %.cc,$(BUILD_DIR)/%.d,$(CCFILES))

# Default Target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Compile source files
$(BUILD_DIR)/%.o: %.cc | $(BUILD_DIR)/dirs
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure build directories exist
$(BUILD_DIR)/dirs:
	mkdir -p $(BUILD_DIR)
	find . -path ./build -prune -o -type d -exec mkdir -p $(BUILD_DIR)/{} \;

# Include dependency files
-include $(DEPENDS)

# Clean up build artifacts
.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR) $(EXEC)