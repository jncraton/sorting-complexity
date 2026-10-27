CXXFLAGS = -std=c++23 -O3 -fno-tree-dce -fno-lto -Wno-terminate
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

readme.pdf: readme.md
	sed '/\.gif/d' $< > readme-no-anim.md
	pandoc -f markdown -t pdf readme-no-anim.md -o $@
	rm -f readme-no-anim.md

sorting-complexity.zip:
	zip $@ * src/*

handout:
	python3 handout.py src/vector.cc src/vector.cc
	python3 handout.py src/forward_list.cc src/forward_list.cc
	python3 handout.py src/list.cc src/list.cc

format:
	clang-format -i src/*.cc src/*.hh
	uv run black *.py

clean:
	rm -rf bin index.html uv.lock venv .venv src/*.o *.csv test bench *.pdf *.zip
