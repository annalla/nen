#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include"Huffman.h"




bool readFile(string name, long data[]);//đọc file lấy dữ liệu
bool DataAndFReq(string name, char data[], unsigned& size, long freq[]);//đọc file thống kê tần số mỗi kí tự
void compressionData(string inName, string outName);// nén dữ liệu vào file khác
//void decodedData(string inName, string outName);//giải nén
void decodedFile(string inName, string outName);
void decodedData(ifstream& infile, string outName);//giải nén
