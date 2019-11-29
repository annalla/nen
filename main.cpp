#include"File.h"
#include"Folder.h"

int main()
{
	string in = "c:\\users\\asus\\documents\\A.txt";
	string out = "c:\\users\\asus\\Downloads\\kq.txt";
	string c = "c:\\users\\asus\\Downloads\\test.txt";
	compressionData(in, out);
	decodedFile(out, c);

	string ddoutfile= "c:\\users\\asus\\documents\\folder.txt";
	string foldername = "test";
	string folderpath1 = "c:\\users\\asus\\documents\\test";
	ofstream outfile1;
	outfile1.open(ddoutfile, ios::out);
	compressionFolder(folderpath1, outfile1, foldername);
	outfile1.close();

	string folderpath = "c:\\users\\asus\\Downloads";
	ifstream infile;
	infile.open(ddoutfile, ios::in);
	depressionFolder(folderpath, infile);
	infile.close();

	system("pause");
	return 0;
}

