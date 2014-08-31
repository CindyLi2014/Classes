//Cindy Li
#include <cstring>
#include <fstream>
#include <iomanip>
#include "BinaryHeap.h"
#include "BinaryTree.h"

using namespace std;

class HuffmanChar
{
public:
	HuffmanChar() : c('\0'), f(0){}
	HuffmanChar(int feq) : c('\0'), f(feq){}
	HuffmanChar(char ch, int feq) : c(ch), f(feq){}

	bool operator < (const HuffmanChar& a) const {return f < a.f;}
	friend ostream& operator<<(ostream& out, const HuffmanChar& hc)
	{
		out << hc.c << std::right << std::setw(4) << hc.f;
		return out; 
	}

	char c;
	int f;//frequency
};

typedef BinaryTree<HuffmanChar> BNode;

void ReadFile(char *filename, BinaryHeap <BNode>& heap)
{
	const int NUM = 128;
	int asciitable[NUM];
	memset(asciitable, 0, sizeof(asciitable));

	ifstream inf(filename);
	char c;
	HuffmanChar hc;

	while(inf >> std::noskipws >> c)
		asciitable[(int)(c)]++;

	for(int i=0; i<NUM; i++)
		if (asciitable[i]>0)
				heap.insert(BNode(HuffmanChar((char)(i), asciitable[i]), NULL, NULL));
}

BNode* BuildHuffmanTree(BinaryHeap <BNode>& heap)
{
	while (!heap.isEmpty())
	{
		//extract two nodes
		BNode nd1 = heap.findMin();
		BNode* pLeft = new BNode(nd1);
		heap.deleteMin();
		if(heap.isEmpty())
			return pLeft;
		
		BNode nd2 = heap.findMin();
		BNode* pRight = new BNode(nd2);
		heap.deleteMin();

		HuffmanChar hc(nd1.getObject().f + nd2.getObject().f);
		heap.insert(BNode(hc, pLeft, pRight));
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Please use this format: command filename\n"; 
		return 0;
	}
	//1. read file, and sort char by frequency w/ binaryheap
	//2. use this bheap as input to huffman, extract min from heap one by one to get tree, each time push a new tree node back to bheap
	//3. finally, print it out
	BinaryHeap <BNode> heap(1000001);
	ReadFile(argv[1], heap);
	BNode* root = BuildHuffmanTree(heap);
	if(root)
	{
		char c[128];
		root->printTree(c, 0);
	}

	return 0;
}