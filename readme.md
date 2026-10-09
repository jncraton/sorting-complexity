# Sorting Through Complexity

An introductory exploration of complexity theory through open science and open pedagogy.

![Bubble Sort](https://upload.wikimedia.org/wikipedia/commons/3/37/Bubble_sort_animation.gif)

## Learning Outcomes

After completing this project, students will be able to:

1. Compare the [computational complexity](https://en.wikipedia.org/wiki/Computational_complexity) of sorting algorithms and list operations
2. Collaborate on software projects using [version control systems](https://en.wikipedia.org/wiki/Version_control)
3. Follow [open science](https://en.wikipedia.org/wiki/Open_science) practices

![Open Science pillars](https://thumb.wikimedia.org/wikipedia/commons/thumb/d/d8/UNESCO-Open_science-pillars-en.png/500px-UNESCO-Open_science-pillars-en.png)


## Task

Each student or group implements sorting algorithms as methods within C++ container classes (`list`, `forward_list`, and `vector`). These containers are used in a test harness that measures wall time and the number of comparisons performed for various input sizes. A shared web dashboard is updated to allow comparison and exploration of the included algorithms and data structures. The dashboard compares the programs in terms of both wall time and the number of operations used.

[Example Dashboard](https://jncraton.github.io/sorting-complexity/)

Students can contribute and review one another's work using pull requests. When this project is hosted on GitHub, GitHub Actions will automatically build the dashboard and push it to GitHub Pages for review.

## Building

Running the included `makefile` will build all files, run analysis and generate the dashboard (`index.html`). To build the dashboard locally, you'll need Python 3.12, uv, make, and gcc 14.2 or higher. Simply run:

```sh
make
```

## Analysis

The following automated analysis is performed and displayed for each container and operation:

1. The containers are compiled using `g++ -std=c++23`.
2. The `bench` program measures the time taken for various operations (e.g., `push_back`, `insert`, `sort_quick`) across different input sizes.
3. A `TrackedInt` class is used to count the number of comparisons performed during sorting.
4. The results are saved to `bench.csv`.
5. `analyze.py` processes the CSV to generate an interactive Plotly dashboard (`index.html`) comparing performance across containers and algorithms.

## OCTOPUS and PALSave

This open resource is part of the [OCTOPUS project](https://qubeshub.org/community/groups/octopus/about) and supported by a [PALSave Open Pedagogy grant](https://palni.org/palsave/open-pedagogy-grants).

## Resources

- [The Basic Reproducible Workflow Template](http://www.practicereproducibleresearch.org/core-chapters/3-basic.html)
