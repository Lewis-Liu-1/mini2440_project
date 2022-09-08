
BUILD=build
TARGETS=ex1 ex2 reverse
EXES=$(addprefix $(BUILD)/, $(TARGETS))

CXX_FLAGS=-std=c++17

all: $(BUILD) $(EXES)

build:
	@echo "Building:" $(EXES)
	mkdir -p build

$(BUILD)/reverse: string_reverse.c
	gcc -o $@ $<

$(BUILD)/ex1:
	g++ $(CXX_FLAGS) template1.cpp -o $@

$(BUILD)/ex2:
	g++ $(CXX_FLAGS) template2.cpp -o $@

clean:
	rm -rf $(BUILD)