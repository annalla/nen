#include"Huffman.h"


HuffmanNode* creatNode(char c, long freq)
{
	HuffmanNode* Node = new HuffmanNode;
	Node->c = c;
	Node->frequence = freq;
	Node->pLeft = NULL;
	Node->pRight = NULL;

	return Node;

}
HuffmanTree* creatMinHeap(unsigned size)
{
	HuffmanTree* tree = new HuffmanTree;
	tree->size = size;
	tree->array = new HuffmanNode * [size];
	for (int i = 0; i < size; i++)
		tree->array[i] = new HuffmanNode;

	return tree;
}

HuffmanTree* creatAndBuildMinHeap(char arr[], long frequence[], unsigned size)
{

	HuffmanTree* tree = creatMinHeap(size);

	for (int i = 0; i < size; i++)
	{
		tree->array[i] = creatNode(arr[i], frequence[i]);
	}

	buildMinHeap(tree);
	return tree;
}
void swapNode(HuffmanNode*& a, HuffmanNode*& b)
{
	HuffmanNode* tmp = a;
	a = b;
	b = tmp;
}
void heapify(HuffmanTree* tree, int i)
{
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	long minIndex = i;

	if (l < tree->size && tree->array[l]->frequence < tree->array[minIndex]->frequence)
		minIndex = l;
	if (r < tree->size && tree->array[r]->frequence < tree->array[minIndex]->frequence)
		minIndex = r;

	if (minIndex != i)
	{
		swapNode(tree->array[minIndex], tree->array[i]);
		heapify(tree, minIndex);
	}

}
void buildMinHeap(HuffmanTree* tree)
{
	int n = tree->size - 1;
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		heapify(tree, i);
	}
}
bool isSizeOne(HuffmanTree* tree)
{
	return tree->size == 1;
}
HuffmanNode* getMinNode(HuffmanTree* tree)
{
	HuffmanNode* tmp = tree->array[0];


	tree->array[0] = tree->array[tree->size - 1];
	--tree->size;
	heapify(tree, 0);
	return tmp;
}
void insertNodeIntoTree(HuffmanTree* tree, HuffmanNode* Node)
{
	++tree->size;
	int i = tree->size - 1;

	while (i && Node->frequence < tree->array[(i - 1) / 2]->frequence)
	{
		tree->array[i] = tree->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	tree->array[i] = Node;

}
HuffmanTree* buildHuffmanTree(char arr[], long frequence[], unsigned size)
{
	HuffmanTree* tree = creatAndBuildMinHeap(arr, frequence, size);
	HuffmanNode* pLeft, * pRight, * top;

	while (isSizeOne(tree) != 1)
	{
		pLeft = getMinNode(tree);
		pRight = getMinNode(tree);
		top = creatNode('$', pLeft->frequence + pRight->frequence);
		top->pLeft = pLeft;
		top->pRight = pRight;

		insertNodeIntoTree(tree, top);

	}
	return tree;

}

vector<Code> findCodeTable(char arr[], long frequence[], unsigned size)
{
	HuffmanTree* tree = buildHuffmanTree(arr, frequence, size);
	string code = "";
	vector<Code>arrCode;

	findCode(tree->array[0], arrCode, code, 0);

	return arrCode;
}

void findCode(HuffmanNode* tree, vector<Code>& table, string code, int top)
{
	if (tree->pLeft)
	{
		code += '0';
		code[top] = '0';
		findCode(tree->pLeft, table, code, top + 1);
	}
	if (tree->pRight)
	{
		code += '1';
		code[top] = '1';
		findCode(tree->pRight, table, code, top + 1);
	}
	if (tree->pLeft == NULL && tree->pRight == NULL)
	{
		Code x;
		x.c = tree->c;
		x.frequence = tree->frequence;
		code = code.substr(0, top);
		x.code = code;
		table.push_back(x);
	}
}

void convert(string arrCode[], vector<Code>table)
{
	for (int i = 0; i < table.size(); i++)
	{
		arrCode[unsigned char(table[i].c)] = table[i].code;
	}
}

string convertDecimalToBinary(int Deci)
{
	string kq = "";
	if (Deci < 0)
		Deci += 256;
	int i = 8;
	for (int j = 7; j >= 0; j--)
	{
		kq += (((Deci >> j) & 1) + 48);
	}
	--i;

	return kq;
}

