
GCC := g++

OUTPUT := opgave2a
SOURCES := $(wildcard *.cpp)
CCFLAGS := -std=c++20 -pthread

all: $(OUTPUT)
	
$(OUTPUT):$(SOURCES)
	$(GCC) -o build/$(OUTPUT) $(CCFLAGS) $(SOURCES)
	
clean:
	rm $(OUTPUT)
	
.PHONY: all
