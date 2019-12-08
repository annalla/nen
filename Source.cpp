#include"File.h"
#include"Folder.h"

int main()
{
	
	string in = "c:\\users\\asus\\Downloads\\corpus-title\\corpus-title.txt";//link file muon giai nen
	string out = "c:\\users\\asus\\Downloads\\kq.txt";//link file kq
	string c = "c:\\users\\asus\\Downloads\\test.txt";// link file test
	compressionData(in, out);
	decodedFile(out, c);
	system("pause");


	//string ddoutfile = "c:\\users\\asus\\documents\\folder.txt";//link file sau khi nen
	//string foldername = "test";// Ten folder
	//string folderpath1 = "c:\\users\\asus\\documents\\test";// link folder muon nen
	//ofstream outfile1;
	//outfile1.open(ddoutfile, ios::binary);
	//compressionFolder(folderpath1, outfile1, foldername);
	//outfile1.close();

	//string folderpath = "c:\\users\\asus\\downloads";// dia chi folder moi
	//ifstream infile;
	//infile.open(ddoutfile, ios::binary);
	//depressionFolder(folderpath, infile);
	//infile.close();

	system("pause");
	return 0;
}

