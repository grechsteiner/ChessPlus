CXX=g++
CXXFLAGS=-std=c++17 -Wall -g -MMD -I/opt/homebrew/include $(shell find . -name '*.h' -exec dirname {} \; | sort -u | sed 's/^/-I/')
LDFLAGS=-L/opt/homebrew/lib -lX11
EXEC=chess
CCFILES=$(shell find . -name '*.cc')
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}