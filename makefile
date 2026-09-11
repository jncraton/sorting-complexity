all: index.html

index.html: analyze.py
	uv run python3 analyze.py

clean:
	rm -rf bin index.html uv.lock venv .venv
