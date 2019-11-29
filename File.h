#pragma once
#include"Huffman.h"


bool readFile(string name, long data[]);//đọc file lấy dữ liệu
bool DataAndFReq(string name, char data[], unsigned& size, long freq[]);//đọc file thống kê tần số mỗi kí tự


void compressionData(string inName, string outName);// nén dữ liệu vào file khác
string encodedHuffmanData(string name, vector<Code>codeTable);//tạo chuỗi nén dữ liệu


void decodedData(ifstream &inFile,string outName);//giải nén
void decodedFile(string inName, string outName);

//các hàm dưới dùng để test chương trình
void printDataAndFreq(char data[],unsigned size, long freq[]);