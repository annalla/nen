#pragma once
#include"dirent.h"
#include"File.h"

void compressionFolder(string folderPath, ofstream &outFile, string folderName);

void readFolder(string folderPath, vector<string>& listFileName, vector<string>& listFoder);


