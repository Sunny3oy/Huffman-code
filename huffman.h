#pragma once
#ifndef HUFFMAN_H_
#define HUFFMAN_H_

// ---------------------------------------------------------------------------------------------
// Huffman code related
// ---------------------------------------------------------------------------------------------

// The Huffman node struct
struct HuffmanNode {
	char character;
	int frequency;
	bool isLeaf;
	HuffmanNode *left;
	HuffmanNode *right;

	// Constructor for leaf nodes
	HuffmanNode(char, int);

	// Constructor for internal nodes
	HuffmanNode(int, HuffmanNode *, HuffmanNode *);

	// Overloaded comparison operators
	inline bool operator<(HuffmanNode &rhsNode) {
		return frequency < rhsNode.frequency;
	}

	inline bool operator>(HuffmanNode &rhsNode) {
		return rhsNode < *this;
	}
};

// Huffman code functions
HuffmanNode **genHuffmanNodes(char *, int *, int);

HuffmanNode *genHuffmanTree(HuffmanNode **, int);

// ---------------------------------------------------------------------------------------------
// Min heap related
// ---------------------------------------------------------------------------------------------

// The MinHeap struct
struct MinHeap {
	int heapSize;
	HuffmanNode **heapNodes;

	// Constructor
	MinHeap(HuffmanNode **, int);

	// Min heap methods
	void exchange(int, int);

	void minHeapify(int);

	void buildMinHeap();

	// Min priority queue methods
	HuffmanNode *extractMin();

	void insert(HuffmanNode *);
};

#endif /* HUFFMAN_H_ */
