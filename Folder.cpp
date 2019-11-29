#include"Folder.h"
#include<string>
#pragma warning(disable : 4996)

void readFolder(string folderPath, vector<string>& listFileName, vector<string>& listFoder)
{
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir(folderPath.c_str())) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			ifstream f((folderPath + "\\" + ent->d_name), ios::in);
			if (f.is_open())
			{
				listFileName.push_back(ent->d_name);
				f.close();
			}
			else
			{
				string tmp(ent->d_name);
				if (tmp.compare(".") != 0 && tmp.compare("..") != 0)
				{
					listFoder.push_back(folderPath + "\\" + ent->d_name);
				}
			}
		}
		closedir(dir);
	}
}

void compressionFolder(string folderPath, ofstream &outFile,string folderName )
{
	vector<string>folderList;
	vector<string>fileList;
	
	readFolder(folderPath, fileList, folderList);
	//Lưu thư mục 
	string nameFolder="";
	int i = folderPath.size() - 1;
	while (i >= 0 && folderPath[i] != '\\' )
	{
		nameFolder += folderPath[i];
		--i;
	}
	reverse(nameFolder.begin(), nameFolder.end());
	outFile << nameFolder << endl;
	outFile << fileList.size() << endl;
	outFile << folderList.size() << endl;
	for (int i = 0; i < fileList.size(); i++)//lưu tệp trong thư mục
	{
		outFile << fileList[i] << endl;
 		compressionData(folderPath+"\\"+fileList[i],fileList[i]);
		ifstream inFile;
		inFile.open(fileList[i]);
		char c;
		while (inFile)
		{
			inFile.get(c);
			if (inFile.eof())
				break;
			outFile << c;	
		}
		outFile << endl;//đánh dấu xong 1 tệp
		inFile.close();
	}

	for (int i = 0; i < folderList.size(); i++)
	{
		cout << folderList[i] << endl;
		compressionFolder(folderList[i], outFile, folderName);
	}
	
}

