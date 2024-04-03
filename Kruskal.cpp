#include "Header.h"


template <typename T>
void DynamicArray<T>::addTail(T*& data)
{

	T** tempArr = new T * [current_size + 1];
	for (int i = 0; i < current_size; i++)
	{
		tempArr[i] = dane[i];
	}

	delete[] dane;
	dane = tempArr;

	current_size++;
	dane[current_size - 1] = data;

}


template <typename T>
void DynamicArray<T>::deleteAll()
{
	for (int i = 0; i < current_size; i++)
	{
		delete dane[i];
		dane[i] = nullptr;
	}
	delete[] dane;
	dane = nullptr;
	current_size = 0;
}

template <typename T>
void DynamicArray<T>::displayAllElements()
{
	for (int i = 0; i < current_size; i++)
	{
		std::cout << "Data at index " << i << ":" << std::endl;
		std::cout << dane[i] << "\n\n";
	}

}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::Merge(Comparator comp, int left, int middle, int right)
{
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	T** leftArray = new T * [n1];
	T** rightArray = new T * [n2];

	for (i = 0; i < n1; i++)
		leftArray[i] = dane[left + i];
	for (j = 0; j < n2; j++)
		rightArray[j] = dane[middle + 1 + j];

	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (!comp(*leftArray[i], *rightArray[j])) {
			dane[k] = leftArray[i];
			i++;
		}
		else {
			dane[k] = rightArray[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		dane[k] = leftArray[i];
		i++;
		k++;
	}
	while (j < n2) {
		dane[k] = rightArray[j];
		j++;
		k++;
	}

	delete[] leftArray;
	delete[] rightArray;
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::MergeSortHelper(Comparator comp, int left, int right)
{
	if (left < right) {
		int middle = left + (right - left) / 2;

		MergeSortHelper(comp, left, middle);
		MergeSortHelper(comp, middle + 1, right);

		Merge(comp, left, middle, right);
	}
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::MergeSort(Comparator comp)
{
	MergeSortHelper(comp, 0, current_size - 1);
}

template <typename T>
void DynamicArray<T>::changeData(T*& data, int index)
{
	if (index < 0 || index > current_size - 1)
	{
		std::cout << "Index out of range" << std::endl;
		return;
	}
	else
	{
		delete dane[index];
		dane[index] = data;
		std::cout << "Data under the current index has been changed" << std::endl;
	}

}

template <typename T>
T* DynamicArray<T>::returnData(int index)
{
	if (index < 0 || index > current_size - 1)
	{
		std::cout << "Index out of range" << std::endl;
		return nullptr;
	}
	else
	{
		return dane[index];
	}
}

int RandomNumber(int from, int to)
{
	std::random_device rd;
	std::default_random_engine e{ rd() };
	std::uniform_int_distribution <unsigned> u(from, to);
	return u(e);
}

int UnionFind::FindRepresentative(int NodeIndex)
{
	FindOpCounter++;
	if (ParentIndex[NodeIndex] == NodeIndex)
	{
		return NodeIndex;
	}
	else
		return FindRepresentative(ParentIndex[NodeIndex]);
}

int UnionFind::PathCompression(int NodeIndex)
{
	FindOpCounter++;
	if (ParentIndex[NodeIndex] != NodeIndex)
	{
		ParentIndex[NodeIndex] = PathCompression(ParentIndex[NodeIndex]);

	}
	return ParentIndex[NodeIndex];
}

void UnionFind::CombineTwoSets(int iNode, int jNode)
{
	int iRep = FindRepresentative(iNode);
	int jRep = FindRepresentative(jNode);
	
	if (iRep != jRep)
	{
		ParentIndex[iRep] = jRep;
	}
}

void UnionFind::UnionByRank(int iNode, int jNode)
{
	if (Rank[iNode] > Rank[jNode])
	{
		ParentIndex[jNode] = iNode;
	}
	else if (Rank[iNode] < Rank[jNode]) 
	{
		ParentIndex[iNode] = jNode;
	}
	else
	{
		ParentIndex[jNode] = iNode;
		Rank[iNode]++;
	}
}


template <typename Comparator>
DynamicArray<Edge> KruskalAlgorithmVer1(Graph graph, Comparator comp)
{
	UnionFind unia = UnionFind(graph.size);
	
	clock_t s1 = clock();
	graph.Edges.MergeSort(comp);
	clock_t e1 = clock();
	double time1 = (e1 - s1) / (double)CLOCKS_PER_SEC;

	DynamicArray<Edge> MST;
	clock_t s2 = clock();
	for (int i = 0; i < graph.Edges.current_size; i++)
	{
		int rep1 = unia.FindRepresentative(graph.Edges[i]->IndexOne);
		int rep2 = unia.FindRepresentative(graph.Edges[i]->IndexTwo);
		if (rep1 != rep2)
		{
			MST.addTail(graph.Edges[i]);
			unia.CombineTwoSets(graph.Edges[i]->IndexOne, graph.Edges[i]->IndexTwo);
		}
		
	}
	clock_t e2 = clock();
	double time2 = (e2 - s2) / (double)CLOCKS_PER_SEC;
	
	double suma = 0;
	for (int i = 0; i < MST.current_size; i++)
	{
		suma += MST.dane[i]->weight;
	}

	std::cout << "Number of edges: " << MST.current_size << '\n';
	std::cout << "Total weight: " << suma << '\n';
	std::cout << "Sorting time: " << time1 << "\n";
	std::cout << "Main loop time: " << time2 << "\n";
	std::cout << "Number of find operations: " << unia.FindOpCounter << std::endl;

	return MST;
}

template <typename Comparator>
DynamicArray<Edge> KruskalAlgorithmVer2(Graph graph, Comparator comp)
{
	UnionFind unia = UnionFind(graph.size);

	clock_t s1 = clock();
	graph.Edges.MergeSort(comp);
	clock_t e1 = clock();
	double time1 = (e1 - s1) / (double)CLOCKS_PER_SEC;

	DynamicArray<Edge> MST;
	clock_t s2 = clock();
	for (int i = 0; i < graph.Edges.current_size; i++)
	{
		int rep1 = unia.PathCompression(graph.Edges[i]->IndexOne);
		int rep2 = unia.PathCompression(graph.Edges[i]->IndexTwo);
		if (rep1 != rep2)
		{
			MST.addTail(graph.Edges[i]);
			unia.UnionByRank(rep1, rep2);
		}
	}
	clock_t e2 = clock();
	double time2 = (e2 - s2) / (double)CLOCKS_PER_SEC;

	double suma = 0.0;
	for (int i = 0; i < MST.current_size; i++)
	{
		suma = suma + MST.dane[i]->weight;
	}

	std::cout << "Number of edges: " << MST.current_size << '\n';
	std::cout << "Total weight: " << suma << '\n';
	std::cout << "Sorting time: " << time1 << "\n";
	std::cout << "Main loop time: " << time2 << "\n";
	std::cout << "Number of find operations: " << unia.FindOpCounter++ << std::endl;

	return MST;
}


int main()
{
//---------------------------FIRST FILE--------------------------
	std::fstream example1;
	example1.open("g1.txt");

	Graph graph1;
	std::string line;
	std::getline(example1, line);

	graph1.size = std::stoi(line);
	for (int i = 0; i < graph1.size; i++)
	{
		std::string line2;
		std::getline(example1, line2);

		std::stringstream input_stringstream(line2);
		std::string words[2];
		int j = 0;

		while ((j < 2) && (input_stringstream >> words[j]))
		{
			j++;
		}

		if (j == 2)
		{
			std::string x = words[0];
			float X = std::stof(x);  

			std::string y = words[1];
			float Y = std::stof(y);
			Node* newNode = new Node(X, Y);

			graph1.Nodes.addTail(newNode);

		}

	}
	std::string line3;
	std::getline(example1, line3);
	int EdgesNumber = std::stoi(line3);


	for (int i = 0; i < EdgesNumber; i++)
	{
		std::string line3;
		std::getline(example1, line3);
		std::stringstream input_stringstream(line3);
		std::string words[3];
		int j = 0;

		while ((j < 3) && (input_stringstream >> words[j]))
		{
			j++;
		}

		if (j == 3)
		{
			std::string index1 = words[0];
			int Indexone = std::stoi(index1);

			std::string index2 = words[1];
			int Indextwo = std::stoi(index2);

			std::string weigh = words[2];
			double weighN = std::stod(weigh);

			Edge* newEdge = new Edge(Indexone, Indextwo, weighN);
			graph1.Edges.addTail(newEdge);

		}

	}

	EdgeCompare comp;

	DynamicArray<Edge> MST1 = KruskalAlgorithmVer1(graph1, comp);

	DynamicArray<Edge> MST2 = KruskalAlgorithmVer2(graph1, comp);
	
	example1.close();

	// ---------------------NEXT FILE-------------------------
	std::fstream example2;
	example2.open("g2.txt");

	Graph graph2;
	std::string lineN;
	std::getline(example2, lineN);

	graph2.size = std::stoi(lineN);
	for (int i = 0; i < graph2.size; i++)
	{
		std::string lineN2;
		std::getline(example2, lineN2);

		std::stringstream input_stringstream(lineN2);
		std::string words[2];
		int j = 0;

		while ((j < 2) && (input_stringstream >> words[j]))
		{
			j++;
		}

		if (j == 2)
		{
			std::string x = words[0];
			float X = std::stof(x);

			std::string y = words[1];
			float Y = std::stof(y);
			Node* newNode = new Node(X, Y);

			graph2.Nodes.addTail(newNode);

		}

	}
	std::string lineN3;
	std::getline(example2, lineN3);
	int EdgesNumber2 = std::stoi(lineN3);


	for (int i = 0; i < EdgesNumber2; i++)
	{
		std::string lineN3;
		std::getline(example2, lineN3);
		std::stringstream input_stringstream(lineN3);
		std::string words[3];
		int j = 0;

		while ((j < 3) && (input_stringstream >> words[j]))
		{
			j++;
		}

		if (j == 3)
		{
			std::string index1 = words[0];
			int Indexone = std::stoi(index1);

			std::string index2 = words[1];
			int Indextwo = std::stoi(index2);

			std::string weigh = words[2];
			double weighN = std::stod(weigh);

			Edge* newEdge = new Edge(Indexone, Indextwo, weighN);
			graph2.Edges.addTail(newEdge);

		}

	}

	EdgeCompare comp2;

	DynamicArray<Edge> MSTN1 = KruskalAlgorithmVer1(graph2, comp2);
	DynamicArray<Edge> MSTN2 = KruskalAlgorithmVer2(graph2, comp2);

	example2.close();

	return 0;
}