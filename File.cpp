#include"File.h"


bool readFile(string name, long data[])
{
	ifstream inFile;
	char c;
	inFile.open(name, ios::in|ios::binary);
	if (inFile.fail())
	{
		cout << "Couldn't open file\n";
		return 0;
	}
	while (inFile)
	{
		inFile.get(c);
		if (inFile.eof())
			break;
		data[c]++;
	}

	inFile.close();
	return 1;

}

bool DataAndFReq(string name, char data[], unsigned& size, long freq[])
{
	long ch[MAX_CHAR]{ 0 };
	size = 0;
	if (!readFile(name, ch))
		return 0;

	for (int i = 0; i < MAX_CHAR; i++)
	{
		if (ch[i] != 0)
		{
			data[size] = char(i);
			freq[size] = ch[i];
			size++;
		}

	}
	//printDataAndFreq(data, size, freq);
	return 1;
}

string encodedHuffmanData(string name, vector<Code>codeTable)
{
	string enCodedStr = "";
	ifstream infile;
	infile.open(name, ios::in|ios::binary);
	if (!infile)
	{
		cout << "couldn't open file";
		exit(1);
	}
	
	char c;
	if (infile.fail())
		return 0;
	while (infile)
	{
		infile.get(c);
		if (infile.eof())
			break;
		for (int i = 0; i < codeTable.size(); i++)//tìm chuỗi mã hóa
		{
			if (c == codeTable[i].c)
			{
				codeTable[i].code[codeTable[i].size] = '\0';
				enCodedStr += codeTable[i].code;
				break;
			
			}
		}
	}
	infile.close();
	return enCodedStr;
}
void compressionData(string inName, string outName)//nén dữ liệu từ file inName thành file outName
{
	//long text[MAX_CHAR]{ 0 };
	char data[MAX_CHAR];//lưu kí tựu
	long freq[MAX_CHAR];//lưu tần số tương ứng
	unsigned size;
	vector<Code>arrCode;//lưu mảng các mã bit của mỗi kí tự
	//đọc dữ liệu từ file và tìm tần số xuất hiên các kí tự
	if (!DataAndFReq(inName, data, size, freq))
	{
		cout << "Couldn't open file";
		exit(1);
	}
	arrCode = findCodeTable(data, freq, size);//tìm mã code của các kí tự tương ứng
	string str = encodedHuffmanData(inName, arrCode);//chuỗi sau khi mã hóa
	
	ofstream outfile;
	outfile.open(outName, ios::out|ios::binary);
	if (!outfile)
	{
		cout << "Couldn't open file";
		exit(1);
	}
	//lưu bản tần số của dữ liệu vào file nén
	outfile << size;
	for (int i = 0; i < size;i++)
	{
		outfile << data[i];
		outfile << freq[i];
		outfile << ' ';
	}
	outfile << '\n';

	char d = 0;

	while (1)//đảm bảo đầy đủ số bit cho mỗi kí tự
	{
		if (str.length() % 8 == 0)
			break;
		str = str + '0';
	}
	for (int i = 0; i < str.length(); i++)//tách 8 bit -> kí tự lưu vào file nén
	{
		if (str[i] == '1')
			d |= (1 << (7 - (i % 8)));
		if ((i - 7) % 8 == 0)
		{
			outfile << d;
			d = 0;
		}
	}
	outfile.close();
}
void decodedFile(string inName, string outName)
{
	ifstream infile;
	infile.open(inName, ios::in | ios::binary);
	if (!infile)
	{
		cout << "Couldn't open file";
		exit(1);
	}
	decodedData(infile, outName);
	infile.close();
}
void decodedData(ifstream& infile, string outName)//giải nén dữ liệu từ file inName ra file outName
{
	
	ofstream outfile;
	outfile.open(outName, ios::out | ios::binary);
	char c;
	unsigned ts;//tan so
	char data[MAX_CHAR];
	long freq[MAX_CHAR];
	unsigned size = 0;
	int j = 0;
	int count = 0,test=0;
	//đọc bảng tần số, data và build encodeData
	infile >> size;
	unsigned tmp = size;

	vector<Code>arr;
	unsigned length = 0;//số lượng bit trong encodedData
	string encodedStr = "";
	while (infile)
	{
		infile.get(c);
		if (infile.eof())
			break;
		if (j < tmp)
		{
			data[j] = c;
			infile >> ts;
			freq[j] = ts;
			infile.get(c);
			
		}
		else if (j == tmp)
		{
			arr = findCodeTable(data, freq, size);
			for (int i = 0; i < arr.size(); i++)
			{
				length += arr[i].size*arr[i].frequence;

			}
		}
		else if (j != tmp)
		{
			//cout << count << endl;
			//cout << c;
			encodedStr += convertDecimalToBinary(c);
			if (encodedStr.size()>=length)
			{

				//cout << length << endl;
				break;
			}
		}
		j++;
	}
	HuffmanTree*tree= buildHuffmanTree(data, freq, size);
	HuffmanNode* treeTmp= tree->array[0];
	//decodeData 
	for (int i = 0; i <length; i++)
	{
	
		if (encodedStr[i] == '0')
		{
			treeTmp = treeTmp->pLeft;
		}
		else
			treeTmp = treeTmp->pRight;
		if (!treeTmp->pLeft && !treeTmp->pRight)
		{
			outfile << treeTmp->c;
			treeTmp = tree->array[0];
		}

	}

	
	outfile.close();
	
}




//dùng để test
void printDataAndFreq(char data[], unsigned size, long freq[])
{
	for (int i = 0; i < size; i++)
	{
		cout << data[i] << "-" << freq[i] << endl;
	}
}
