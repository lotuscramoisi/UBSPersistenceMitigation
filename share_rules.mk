CC = gcc
CXX = g++

CXXFLAGS = -static-libgcc -static-libstdc++ -Wl,--subsystem,windows


ifneq ("$(wildcard exploit.c)","")
all: exploit
exploit: exploit.c
	$(CC) -o exploit exploit.c
endif

ifneq ("$(wildcard cleanup.c)","")
all: cleanup
TARGETS += cleanup
cleanup: cleanup.c
	$(CC) -o cleanup cleanup.c
endif

ifneq ("$(wildcard package.c)","")
all: package.dll
package.dll: package.c
	$(CXX) -shared -o package.dll package.c $(CXXFLAGS)
endif

ifneq ("$(wildcard servDLL.cpp)","")
all: servDLL.dll
servDLL.dll: servDLL.cpp
	$(CXX) -shared -o servDLL.dll servDLL.cpp $(CXXFLAGS)
endif

ifneq ("$(wildcard servDLLPort.cpp)","")
all: servDLLPort.dll
servDLLPort.dll: servDLLPort.cpp
	$(CXX) -shared -o servDLLPort.dll servDLLPort.cpp $(CXXFLAGS)
endif



clean:
	del /f /q exploit.exe cleanup.exe package.dll servDLL.dll servDLLPort.dll
