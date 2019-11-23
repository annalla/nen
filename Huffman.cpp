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

	//swapNode(tree->array[0], tree->array[tree->size - 1]);
	tree->array[0] = tree->array[tree->size - 1];
	--tree->size;
	heapify(tree, 0);
	return tmp;
}
void insertNodeIntoTree(HuffmanTree* tree, HuffmanNode* Node)
{
	++tree->size;
	int i = tree->size-1;

	while (i && Node->frequence < tree->array[(i - 1) / 2]->frequence)
	{
		tree->array[i] = tree->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	tree->array[i] = Node;

}
HuffmanTree* buildHuffmanTree(char arr[], long frequence[], unsigned size)
{
	HuffmanTree* tree = creatAndBuildMinHeap(arr, frequence,size);
	HuffmanNode* pLeft, * pRight, * top;

	while (isSizeOne(tree)!=1)
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
	char code[MAX_CODE];
	vector<Code>arrCode;

	findCode(tree->array[0], arrCode, code,0);

	return arrCode;
}

void findCode(HuffmanNode* tree, vector<Code> &table, char code[], int top)
{
	if (tree->pLeft)
	{
		code[top] = '0';
		findCode(tree->pLeft, table, code, top + 1);
	}
	if (tree->pRight)
	{
		code[top] = '1';
		findCode(tree->pRight, table, code, top + 1);
	}
	if (tree->pLeft == NULL && tree->pRight == NULL)
	{
		Code x;
		x.c = tree->c;
		x.size = top;
		x.frequence = tree->frequence;
		for (int i = 0; i < top; i++)
			x.code[i] = code[i];
		//printCode(code,top);
		table.push_back(x);
	}
}

char convertBinarytoDeci(char binary[], unsigned size)
{
	char deci = 0;
	for (int i = 0; i < size; i++)
	{
		deci = deci + pow(2, size - 1 - i) * (binary[i] - 48);
	}
	return deci;
}

string convertDecimalToBinary(int Deci)
{
	string kq = "";
	if (Deci < 0)
		Deci += 256;
	while (Deci)
	{
		if (Deci % 2)
			kq += '1';
		else
			kq += '0';
		Deci = Deci / 2;
		
	}
	while (kq.length() != 8)
	{
		kq = kq + '0';
	}
	reverse(kq.begin(), kq.end());

	return kq;
}


//test
void printCode(char code[], unsigned size)
{
	for (int i = 0; i < size; i++)
		cout <<  code[i];
	cout << "\n";
}

void printTree(HuffmanTree* tree)
{
	for (int i = 0; i < tree->size; i++)
		cout << tree->array[i]->frequence << " ";
}

void printMinHeap(HuffmanTree* tree)
{
	for (int i = 0; i < tree->size; i++)
		cout << tree->array[i]->frequence << " ";
}
void printArrCode(vector<Code>arrCode)
{
	for (int i = 0; i < arrCode.size(); i++)
	{
		cout << arrCode[i].c << "-";
		printCode(arrCode[i].code,arrCode[i].size);
	}
}