#pragma once
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>


class Data
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Data* data)
	{
		os << data->value << "\n";
		os << data->character << "\n";
		return os;
	}
	Data(int& v, char& c)
	{
		value = v;
		character = c;
	};
	int value;
	char character;
};




template <typename T>
class DynamicArray
{
public:
	DynamicArray()
	{
		current_size = 0;
	}
	T*& operator[](int index)
	{
		return *&dane[index];
	};
	int current_size;
	T** dane = nullptr;
	void addTail(T*& data);
	template <typename Comparator>
	void Merge(Comparator comp, int left, int middle, int right);
	template <typename Comparator>
	void MergeSortHelper(Comparator comp, int left, int right);
	template <typename Comparator>
	void MergeSort(Comparator comp);
	T* returnData(int index);
	void changeData(T*& data, int index);
	void deleteAll();
	void displayAllElements();

};

struct Node
{
	float x = 0;
	float y = 0;
	Node() {};
	Node(float NewX, float NewY)
	{
		x = NewX;
		y = NewY;
	}
};

struct Edge
{
	int IndexOne = 0;
	int IndexTwo = 0;
	double weight = 0;
	Edge(int newIndexOne, int newIndexTwo, double newWeight)
	{
		IndexOne = newIndexOne;
		IndexTwo = newIndexTwo;
		weight = newWeight;
	}
};

class EdgeCompare // if the first bigger returns true 
{
public:
	bool operator()(const Edge e1, const Edge e2) const
	{
		if (e1.weight > e2.weight) return true;
		else return false;

	}
};

struct Graph
{
	DynamicArray<Node> Nodes;
	DynamicArray<Edge> Edges;
	int size = Nodes.current_size;

	Graph() {};


};

struct UnionFind
{
	int* ParentIndex; // = nullptr;
	int* Rank; // = nullptr;
	int NumberOfNodes = 0;
	int FindOpCounter = 0;

	UnionFind(int n)
	{
		NumberOfNodes = n;
		ParentIndex = new int[n];
		Rank = new int[n];
		for (int i = 0; i < n; i++)
		{
			ParentIndex[i] = i;
			Rank[i] = 0;
		}
	}

	void CombineTwoSets(int iNode, int jNode);
	int FindRepresentative(int NodeIndex);
	int PathCompression(int NodeIndex);
	void UnionByRank(int iNode, int jNode);

};