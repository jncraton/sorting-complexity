all: bench

%.o: %.cc
	g++ -std=c++23 -O3 -fno-tree-dce -fno-lto -c $< -o $@

bench: list.o bench.o
	g++ -std=c++23 -fno-tree-dce -fno-lto -O3 $^ -o $@
	./bench

format:
	clang-format -i *.cc *.hh

clean:
	rm -rf *.o *.csv test bench
