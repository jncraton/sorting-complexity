# Sorting Complexity

![Bubble Sort](https://upload.wikimedia.org/wikipedia/commons/3/37/Bubble_sort_animation.gif)

## Learning Outcomes

After completing this project, students will be able:

1. Compare the [computational complexity](https://en.wikipedia.org/wiki/Computational_complexity) of sorting algorithms
2. Collaborate on software projects using [version control systems](https://en.wikipedia.org/wiki/Version_control)
3. Follow [open science](https://en.wikipedia.org/wiki/Open_science) practices

![Open Science pillars](https://thumb.wikimedia.org/wikipedia/commons/thumb/d/d8/UNESCO-Open_science-pillars-en.png/500px-UNESCO-Open_science-pillars-en.png)

## Task

Each student creates and merges their own sorting algorithm as a C++ program. A shared web dashboard is updated allowing comparison and exploration of the included algorithms. The dashboard compares the time complexity of the programs both in terms of wall time and the number of comparison operations used.

Each sorting algorithm lives in the `algorithms` directory. Each program reads line-separated numbers from standard input until EOF is reached. The program should output the list correctly sorted followed by a count of comparisons used along with the amount of time in seconds. An example bubble sort (bubble.cc) program is provided.

When this project is hosted on Github, Github Actions will automatically build the dashboards and push them to Github Pages for review. Students can contribute and review one another's work using pull requests.

## Building

Running the included `makefile` will build all files, run analysis and generate the dashboard (<index.html>). To build the dashboard locally, you'll need Python 3.12, uv, make, and gcc 14.2 or higher. Simply run:

```sh
make
```

## Analysis

The following automated analysis is performed and displayed for each discovered C++ program in the algorithms directory:

1. The program is compiled using `g++ -std=c++23`.
2. The program is tested against random unsigned integer lists while storing the provided runtime and comparison count for each run.
3. The test is re-run using presorted lists for separate comparison.
4. The test is re-run using reverse-sorted lists for separate comparison.

A dashboard is generated to compare algorithm complexity for random, presorted, and reverse-sorted list. Separate graphs are provided for time and comparisons, for 6 total graphs.

## OCTOPUS and PALSave

This open resource is part of the [OCTOPUS project](https://qubeshub.org/community/groups/octopus/about) and support by a [PALSave Open Pedagogy grant](https://palni.org/palsave/open-pedagogy-grants).
