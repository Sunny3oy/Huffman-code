//Sunny Mei 0599
#include <cstddef>
#include "huffman.h"



// ---------------------------------------------------------------------------------------------
// Huffman code related
// ---------------------------------------------------------------------------------------------

// The HuffmanNode constructor for leaf nodes
HuffmanNode::HuffmanNode(char character, int frequency) {
	// TODO
	this->character = character;
	this->frequency = frequency;
	this->isLeaf = 1;
	this->left = NULL;
	this->right = NULL;
}

// The HuffmanNode constructor for internal nodes
HuffmanNode::HuffmanNode(int frequency, HuffmanNode *left, HuffmanNode *right) {
	// TODO
	this->frequency = frequency;
	this->left = left;
	this->right = right;
	this->isLeaf = 0;
}

/*
Creates an array of HuffmanNodes (more specifically, pointers to HuffmanNodes)
based on the given character-frequency pairs.

characters: an array of char
frequencies: an array of int
length: the length of characters and frequencies arrays

returns: an array of HuffmanNode*

Note: For 0 <= i < length, the frequency of the character characters[i]
is found at frequencies[i].
*/
HuffmanNode **genHuffmanNodes(char *characters, int *frequencies, int length) {

	HuffmanNode **array = new HuffmanNode *[length];
	for (int i = 0; i < length; i++)
	{
		HuffmanNode *index = new HuffmanNode(characters[i], frequencies[i]);
		array[i] = index;
	}

	return array;

}

/*
Creates the Huffman tree reusing the given HuffmanNodes.

nodes: an array of HuffmanNode*
length: the length of nodes array

returns: the pointer to the root of the huffman tree
*/
HuffmanNode *genHuffmanTree(HuffmanNode **nodes, int length) {

	MinHeap min = MinHeap(nodes, length);//create the array with minHeap constructor

	while (min.heapSize > 1)//it will run until the array has size one
	{
		HuffmanNode *L, *R;//we make the nodes for left and right
		L = min.extractMin();//we extract the min from the heap and assign it to left
		R = min.extractMin();//we do the same for the right
		HuffmanNode *internal = new HuffmanNode(L->frequency + R->frequency, L, R);//we create an internal node with the sum of the frequency left and right.
																				   //we also assign left and right to be child of internal
		min.insert(internal);//we insert the internal node back into the heap
	}

	return min.extractMin();//we extract the min but since we only got one element left in the array, this should be the root.
}

// ---------------------------------------------------------------------------------------------
// Min heap related
// ---------------------------------------------------------------------------------------------

// Helper functions for heap
int left(int index) {
	return (index + 1) * 2 - 1;
}

int right(int index) {
	return (index + 1) * 2;
}

int parent(int index) {
	return (index + 1) / 2 - 1;
}

// MinHeap constructor
MinHeap::MinHeap(HuffmanNode **nodes, int length) {
	heapSize = length;
	this->heapNodes = new HuffmanNode *[length];
	for (int i = 0; i < length; i++)
		this->heapNodes[i] = nodes[i];
	buildMinHeap();
}

// Exchanges the HuffmanNode pointers at the given indices of heapNodes array
void MinHeap::exchange(int firstIndex, int secondIndex) {
	// TODO
	HuffmanNode * temp;
	temp = heapNodes[firstIndex];
	heapNodes[firstIndex] = heapNodes[secondIndex];
	heapNodes[secondIndex] = temp;
}

// Applies the minHeapify algorithm starting from the given index
void MinHeap::minHeapify(int index) {
	// TODO
	int smallest = index;
	int size = heapSize;
	if (left(index) < size && heapNodes[left(index)]->frequency < heapNodes[smallest]->frequency)
	{
		smallest = left(index);
	}
	if (right(index) < size && heapNodes[right(index)]->frequency < heapNodes[smallest]->frequency)
	{
		smallest = right(index);
	}
	if (smallest != index)
	{
		exchange(smallest, index);
		minHeapify(smallest);
	}
}

// Converts the heapNodes array into a heap
void MinHeap::buildMinHeap() {
	for (int i = heapSize / 2 - 1; i >= 0; i--)
		minHeapify(i);
}

// Removes the minimum element from the heap and returns it
HuffmanNode *MinHeap::extractMin() {
	// TODO
	if (heapSize < 1)
	{
		return NULL;
	}
	HuffmanNode *temp;
	temp = heapNodes[0];
	heapNodes[0] = heapNodes[heapSize - 1];
	heapSize--;
	minHeapify(0);
	return temp;
}

// Inserts a new HuffmanNode to the heap
void MinHeap::insert(HuffmanNode *node) {
	heapSize++;
	int i = heapSize - 1;
	heapNodes[i] = node;
	while (i > 0 && *heapNodes[parent(i)] > *heapNodes[i]) {
		exchange(i, parent(i));
		i = parent(i);
	}
}
