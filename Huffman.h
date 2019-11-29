﻿#pragma once
#include<iostream>
#define MAX_CHAR 256
#define MAX_CODE 256
#include<fstream>
#include<vector>
#include<string>
using namespace std;

struct HuffmanNode
{
	char c;
	long frequence;
	HuffmanNode* pLeft, * pRight;
};

struct HuffmanTree
{
	unsigned size;
	HuffmanNode** array;
};

struct Code
{
	char code[MAX_CODE];
	unsigned size;
	char c;
	long frequence;
};

HuffmanNode* creatNode(char c, long freq);//khởi tạo một node
void heapify(HuffmanTree* tree, int i);//hiệu chỉnh cây tại 1 node 
void swapNode(HuffmanNode*& a, HuffmanNode*& b);//hoán đổi 2 node
bool isSizeOne(HuffmanTree* tree);//kiểm tra cây có đúng còn 1 node hay không
HuffmanNode* getMinNode(HuffmanTree* tree);//lấy node có giá trị nhỏ nhất trong cây
void insertNodeIntoTree(HuffmanTree* tree, HuffmanNode* Node);//chèn một node vào cây huffman

HuffmanTree* creatMinHeap(unsigned size);//khởi tạo cây minheap
void buildMinHeap(HuffmanTree* tree);//dựng cây minheap
HuffmanTree* creatAndBuildMinHeap(char arr[], long frequence[], unsigned size);// tạo và dựng cây minheap

HuffmanTree* buildHuffmanTree(char arr[], long frequence[], unsigned size);//xây dựng cây huffman
vector<Code> findCodeTable(char arr[], long frequence[], unsigned size);

char convertBinarytoDeci(char binary[], unsigned size);
string convertDecimalToBinary(int Deci);


//tesst
void findCode(HuffmanNode* tree, vector<Code> &table, char code[], int top);
void printCode(char code[],unsigned size);
void printMinHeap(HuffmanTree* tree);
void printTree(HuffmanTree* tree);
void printArrCode(vector<Code>arrCode);
