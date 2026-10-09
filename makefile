CXXFLAGS = -std=c++23 -O3 -fno-tree-dce -fno-lto
OBJECTS = src/list.o src/forward_list.o src/vector.o

all: test index.html

src/%.o: src/%.cc
	g++ $(CXXFLAGS) -c $< -o $@

bench: $(OBJECTS) src/bench.o
	g++ $(CXXFLAGS) $^ -o $@

test: $(OBJECTS) src/test.o
	g++ $(CXXFLAGS) $^ -o $@
	./test

bench.csv: bench
	./bench

index.html: bench.csv analyze.py
	uv run python3 analyze.py

format:
	clang-format -i src/*.cc src/*.hh

clean:
	rm -rf bin index.html uv.lock venv .venv src/*.o *.csv test bench
