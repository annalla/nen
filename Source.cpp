#include"File.h"
#include"Folder.h"

int main()
{
	int h;
	do
	{
		system("cls");
		cout << "0.End Program!\n";
		cout << "1.Compression File!\n";
		cout << "2.Depression File!\n";
		cout << "3.Compression Folder!\n";
		cout << "4.Depression Folder!\n";
		cout << "Choose:";
		cin >> h;
		switch (h)
		{
		case 1:
		{
			system("cls");
			cout << "1.Compression File!\n";
			string in, out;
			cout << "Input Link to File needed to be compressed:";
			cin >> in;
			cout << "Input Link to File after compression:";
			cin >> out;
			compressionData(in, out);
			break;
		}
		case 2:
		{
			system("cls");
			cout << "2.Depression File!\n";
			string in, out;
			cout << "Input Link to File needed to be decoded:";
			cin >> in;
			cout << "Input Link to File after decoding:";
			cin >> out;
			decodedFile(in, out);
			break;
		}
		case 3:
		{
			string ddoutfile;
			string folderpath1;
	
			system("cls");
			cout << "3.Compression Folder!\n";
		
			cout << "Input Link to Folder needed to be compressed:";
			cin >> folderpath1;
			cout << "Input Link to Folder after compression:";
			cin >> ddoutfile;

			string nameFolder = "";
			int i = folderpath1.size() - 1;
			while (i >= 0 && folderpath1[i] != '\\')
			{
				nameFolder += folderpath1[i];
				--i;
			}
			ofstream outfile1;
			outfile1.open(ddoutfile, ios::binary);
			compressionFolder(folderpath1, outfile1,nameFolder);
			outfile1.close();
			break;
		}
		case 4:
		{
			system("cls");
			cout << "4.Depression Folder!\n";
			string ddoutfile;
			cout << "Input Link to Folder needed to be decoded:";
			cin >> ddoutfile;
			string folderpath;
			cout << "Input Link to Folder after decoding:";
			cin >> folderpath;
			ifstream infile;
			infile.open(ddoutfile, ios::binary);
			depressionFolder(folderpath, infile);
			infile.close();
			break;
		}
		default:
		{
			cout << "No suitable Selection\n";
			break;
		}
		}
	} while (h != 0);

	//string in = "c:\\users\\asus\\Downloads\\corpus-title\\tt.txt";//link file muon giai nen
	//string out = "c:\\users\\asus\\Downloads\\kq.txt";//link file kq
	//string c = "c:\\users\\asus\\Downloads\\test.txt";// link file test
	//
	
	system("pause");


	//string ddoutfile = "c:\\users\\asus\\documents\\folder.txt";//link file sau khi nen
	//string foldername = "test";// Ten folder
	//string folderpath1 = "c:\\users\\asus\\documents\\test";// link folder muon nen
	//

	//string folderpath = "c:\\users\\asus\\downloads";// dia chi folder moi
	//ifstream infile;
	//infile.open(ddoutfile, ios::binary);
	//depressionFolder(folderpath, infile);
	//infile.close();

	system("pause");
	return 0;
}

