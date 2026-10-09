all: test index.html

algorithms/%.o: algorithms/%.cc
	g++ -std=c++23 -O3 -fno-tree-dce -fno-lto -c $< -o $@

bench: algorithms/list.o algorithms/forward_list.o algorithms/vector.o algorithms/bench.o
	g++ -std=c++23 -fno-tree-dce -fno-lto -O3 $^ -o $@

bench.csv: bench
	./bench

test: algorithms/list.o algorithms/forward_list.o algorithms/vector.o algorithms/test.o
	g++ -std=c++23 -fno-tree-dce -fno-lto -O3 $^ -o $@
	./test

index.html: bench.csv analyze.py
	uv run python3 analyze.py

format:
	clang-format -i algorithms/*.cc algorithms/*.hh

clean:
	rm -rf bin index.html uv.lock venv .venv algorithms/*.o *.csv test bench
