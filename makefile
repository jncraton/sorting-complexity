all: index.html

index.html: analyze.py
	uv run python3 analyze.py

format:
	clang-format -i algorithms/*

clean:
	rm -rf bin index.html uv.lock venv .venv
