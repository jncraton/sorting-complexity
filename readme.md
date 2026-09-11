# Sorting Complexity

![Bubble Sort](https://upload.wikimedia.org/wikipedia/commons/3/37/Bubble_sort_animation.gif)

## Learning Outcomes

After completing this project, students will be able:

1. Compare the [computational complexity](https://en.wikipedia.org/wiki/Computational_complexity) of various sorting algorithms
2. Collaborate on software projects using [version control systems](https://en.wikipedia.org/wiki/Version_control)
3. Follow [open science](https://en.wikipedia.org/wiki/Open_science) practices

![Open Science pillars](https://thumb.wikimedia.org/wikipedia/commons/thumb/d/d8/UNESCO-Open_science-pillars-en.png/500px-UNESCO-Open_science-pillars-en.png)

## Task

Each student merges their own sorting algorithms as C++ programs. This project then builds a web dashboard allowing comparison and exploration of the included algorithms. The dashboard compares the time complexity of the programs both in terms of raw execution time and the number of comparison operations used.

Programs live in the `algorithms` directory. Each program reads from standard input until EOF is reached. The program should output the list correctly sorted following by a count of comparisons used along with the amount of time in seconds. An example bubble sort (bubble.cc) program is provided.

When this project is hosted on Github, Github Actions will automatically build the dashboards and push them to Github Pages for review. Students can contribute and review one another's work using pull requests.

## Building

Running the included `makefile` will build all files, run analysis and generate the dashboard (<index.html>). To build the dashboard locally, you'll need Python 3.12, uv, make, and gcc 14.2 or higher. Simply run:

```sh
make
```

## Analysis

The following automated analysis is performed and displayed for each discovered C++ program in the algorithms directory:

1. The program is compiled using `g++ -std=c++23`.
2. The program is tested against random unsigned integer lists of the following sizes while storing the provided runtime and comparison count for each run:
  - 1, 2, 4, 10, 100, 1000, 10000, 100000, 1000000
3. The test is re-run using presorted lists for separate comparison.
4. The test is re-run using reverse-sorted lists for separate comparison.

A dashboard is generated to compare algorithm complexity for random, presorted, and reverse-sorted list. Separate graphs are provided for time and comparisons, for 6 total graphs.

## OCTOPUS

This open resource is part of the [OCTOPUS project](https://qubeshub.org/community/groups/octopus/about):

> The OCTOPUS Project: Open Collaboration for Transformative Open Pedagogy to support Undergraduate Open Science Education
>
> OCTOPUS is fundamentally about improving undergraduate science education through the broad integration of the practices and possibilities of Open Science into the STEM curriculum, using Open Pedagogy as a primary lever. This open collaboration began with a group of 12 educators who created resources in alignment with our goals. We are excited to invite you to join our community - everyone interested is welcome! This can mean just exploring our resources, participating in discussions and events, or actively contributing your own open science and open pedagogy teaching resources to our collection. Becoming a member is free, and does not obligate you to anything, but you will receive monthly updates on what is happening in the OCTOPUS community.
>
> Although most scientists agree that transparency and openness in science would strengthen and further scientific knowledge, open science is still not the standard for how science is practiced today, especially in the US. Long-time arguments for making scientific practice more open are usually pitched to established research scientists. Transitioning to open science then has required untraining a large group of people indoctrinated and successful in the current competitive scientific world, which likely explains why Open Science has had little traction. Science education often mirrors scientific practice's competitive focus, where students who are not "good enough" get "weeded out". We make the case that improving science education and achieving a cultural shift towards universal open, equitable, and socially just scientific practice requires substantial transformation in our undergraduate science education systems.
>
> Our resources contextualize Open Science into a broader understanding of the open ecosystem and the connections between its various components, including open data, open access, open educational resources, open source, open infrastructure, citizen science, crowdfunding, open notebook, open labs, open evaluation and more.
>
> Our resources incorporate the basics of how and why to do open science, but are also designed to provide students with opportunities to deeply and critically examine the pitfalls and inequities that many open scientists may face, and to consider how to address those inequities.
>
> Our resources integrate other important structural aspects of improving undergraduate science education such as alternative grading approaches and innovative pedagogical strategies, especially Open Pedagogy.
>
> Our resources are openly licensed and can be easily downloaded and modified for use in a variety of contexts. As members of an open community, we highly encourage users to upload their new versions of remixed OCTOPUS materials so that others may also make use of these revised versions.

## PALSave Open Pedagogy

This work is supported by a [PALSave Open Pedagogy grant](https://palni.org/palsave/open-pedagogy-grants). This grant offers support and recognition for creating or redesigning a course assignment that embraces open pedagogy-an approach that empowers students and makes learning more impactful. Your work will not only benefit your current students but also provide a valuable resource for future educators and learners.
