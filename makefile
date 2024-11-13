CXX=g++
CXXFLAGS=-std=c++17 -Wall -g -MMD -I/opt/homebrew/include $(shell find . -name '*.h' -exec dirname {} \; | sort -u | sed 's/^/-I/')
LDFLAGS=-L/opt/homebrew/lib -lX11 -lboost_system
EXEC=chess

# Specify output directories
BUILD_DIR=build
CCFILES=$(shell find . -name '*.cc')
OBJECTS=$(patsubst %.cc,$(BUILD_DIR)/%.o,$(CCFILES))
DEPENDS=$(patsubst %.cc,$(BUILD_DIR)/%.d,$(CCFILES))

# Default target
all: ${EXEC}

# Link the executable
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

# Ensure only necessary subdirectories are created under `build`
$(BUILD_DIR)/%.o: %.cc | $(BUILD_DIR)/dirs
	${CXX} ${CXXFLAGS} -c $< -o $@

# Create subdirectories for .o files, excluding `build` itself
$(BUILD_DIR)/dirs:
	mkdir -p $(BUILD_DIR)
	find . -path ./build -prune -o -type d -exec mkdir -p $(BUILD_DIR)/{} \;

# Include dependency files
-include ${DEPENDS}

.PHONY: all clean
clean:
	rm -rf ${BUILD_DIR} ${EXEC}