#pragma once
#include"Huffman.h"


bool readFile(char* name, long data[]);//đọc file lấy dữ liệu
bool DataAndFReq(char* name, char data[], unsigned& size, long freq[]);//đọc file thống kê tần số mỗi kí tự


void compressionData(char* inName, char* outName);// nén dữ liệu vào file khác
string encodedHuffmanData(char* name, vector<Code>codeTable);//tạo chuỗi nén dữ liệu


void decodedData(char* inName,char*outName);//giải nén


//các hàm dưới dùng để test chương trình
void printDataAndFreq(char data[],unsigned size, long freq[]);