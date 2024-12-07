CXX = clang++
LIBS = -lre2 # $(shell pkg-config absl_strings --libs) # $(shell pkg-config absl_flat_hash_set --libs)
FLAGS = -pedantic -Wall -O3 -g -std=c++20 -fsanitize=address

UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
	FLAGS += -I/opt/homebrew/include -L/opt/homebrew/lib
endif

build/%: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^
