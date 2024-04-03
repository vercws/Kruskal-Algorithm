Kruskal's Algorithm Implementation
This repository contains C++ code implementing Kruskal's algorithm for finding the Minimum Spanning Tree (MST) of a graph. 
It includes two versions of the algorithm, each utilizing different approaches for optimizing performance.

Table of Contents
Introduction
Features
Files
Usage

Introduction
Kruskal's algorithm is a greedy algorithm used to find the minimum spanning tree of a connected, undirected graph. 
It does this by selecting edges in increasing order of their weights, without forming any cycles, until all vertices are connected.

This implementation of Kruskal's algorithm offers two versions for comparison:
Version 1: Uses a straightforward approach without any optimizations.
Version 2: Incorporates path compression and union by rank techniques to enhance performance.

Features
Generic Implementation: Utilizes templates to handle any type of data, allowing flexibility in usage.
Dynamic Array: Implements a dynamic array to manage the graph's nodes and edges efficiently.
Union-Find Data Structure: Employs the Union-Find data structure to track connectivity between nodes and optimize the algorithm.
Sorting: Utilizes Merge Sort for sorting edges based on their weights.

Files
main.cpp: Contains the main program where Kruskal's algorithm is applied to sample graphs.
Header.h: Header file containing class and function declarations.
README.md: The file you're currently reading, providing an overview of the repository.

Usage
To use this implementation, follow these steps:
1. Clone the repository to your local machine.
2. Compile the main.cpp file using a C++ compiler.
3. Execute the compiled program.
4. View the output, which includes the MST's details, sorting time, main loop time, and the number of find operations performed.
