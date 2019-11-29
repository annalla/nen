#pragma once
#include"dirent.h"
#include"File.h"
#define Max 100
#include"string.h"
#include<direct.h>
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h> 
using namespace std;

void compressionFolder(string folderPath, ofstream &outFile, string folderName);

void depressionFolder(string folderpath, ifstream &infile);
void readFolder(string folderPath, vector<string>& listFileName, vector<string>& listFoder);


