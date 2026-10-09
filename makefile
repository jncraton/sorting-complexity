CXXFLAGS = -std=c++23 -O3 -fno-tree-dce -fno-lto
OBJECTS = algorithms/list.o algorithms/forward_list.o algorithms/vector.o

all: test index.html

algorithms/%.o: algorithms/%.cc
	g++ $(CXXFLAGS) -c $< -o $@

bench: $(OBJECTS) algorithms/bench.o
	g++ $(CXXFLAGS) $^ -o $@

test: $(OBJECTS) algorithms/test.o
	g++ $(CXXFLAGS) $^ -o $@
	./test

bench.csv: bench
	./bench

index.html: bench.csv analyze.py
	uv run python3 analyze.py

format:
	clang-format -i algorithms/*.cc algorithms/*.hh

clean:
	rm -rf bin index.html uv.lock venv .venv algorithms/*.o *.csv test bench
