CXXFLAGS+= -I include

UNAME := $(shell uname)

CXX = g++
default: all
all: read_region

LIB_SRC = $(wildcard src/*.cpp)
LIB_OBJ = $(patsubst %.cpp, %.o, $(LIB_SRC))

-include $(pathsubst %.o, $(LIB_OBJ))

$(OBJS): %.o : %.cpp
	$(CXX) -o $@ $(CXXFLAGS) -c $< 

read_region: $(LIB_OBJ)
	$(CXX) -o $@ $(CXXFLAGS) -Itests $(LDFLAGS) $^ $(LIBS)

clean:
	rm -f $(LIB_OBJ) read_region

.phony: clean default
