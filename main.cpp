#include"File.h"
#include"Folder.h"
#include<string>

int main()
{
	ifstream infile;
	ofstream outfile;
	///*infile.open("corpus-title.txt", ios::binary);
	//compressionData("Text.txt", "kq.txt");
	//decodedFile("kq.txt", "giainen.txt");*/
	//outfile.open("Text.txt", ios::binary);

	//compressionFolder("Nhung", outfile);
	//outfile.close();

	//infile.open("Text.txt", ios::binary);
	//depressionFolder("Test", infile);

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
		cin.ignore();
		switch (h)
		{
		case 1:
		{
			system("cls");
			cout << "1.Compression File!\n";
			string in, out;
			cout << "Input Link to File needed to be compressed:";
			getline(cin, in);
			//cin >> in;
			cout << "Input Link to File after compression:";
			getline(cin, out);
			compressionData(in, out);
			break;
		}
		case 2:
		{
			system("cls");
			cout << "2.Depression File!\n";
			string in, out;
			cout << "Input Link to File needed to be decoded:";
			getline(cin, in);
			//cin.ignore();
			//cin >> in;
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
			getline(cin, folderpath1);
			//cin.ignore();
			cout << "Input Link to Folder after compression:";
			getline(cin,ddoutfile);

			string nameFolder = "";
			int i = folderpath1.size() - 1;
			while (i >= 0 && folderpath1[i] != '\\')
			{
				nameFolder += folderpath1[i];
				--i;
			}
			ofstream outfile1;
			outfile1.open(ddoutfile, ios::binary);
			compressionFolder(folderpath1, outfile1);
			outfile1.close();
			break;
		}
		case 4:
		{
			system("cls");
			cout << "4.Depression Folder!\n";
			string ddoutfile;
			cout << "Input Link to Folder needed to be decoded:";
			getline(cin,ddoutfile);
			//cin.ignore();
			string folderpath;
			cout << "Input Link to Folder after decoding:";
			getline(cin,folderpath);
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

	system("pause");
	return 0;
}

