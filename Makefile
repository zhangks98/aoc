CXX = clang++
LIBS = -lre2
FLAGS = -pedantic -Wall -O3 -g -std=c++17 -fsanitize=address

%: %.cc
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^
