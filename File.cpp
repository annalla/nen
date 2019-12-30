#include"File.h"


bool readFile(string name, long data[])
{
	ifstream inFile;

	char c;
	inFile.open(name, ios::binary);
	//inFile.open(name, ios::in);
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
		data[(unsigned char)(c)]++;
	}
	inFile.close();
	return 1;
}

bool DataAndFReq(string name, char data[], unsigned& size, long freq[])//đọc file thống kê tần số mỗi kí tự
{
	long ch[MAX_CHAR]{ 0 };
	size = 0;
	if (!readFile(name, ch))
		return 0;

	for (int i = 0; i < MAX_CHAR; i++)
	{
		if (ch[i] != 0)
		{
			data[size] = i;
			freq[size] = ch[i];
			size++;
		}
	}
	return 1;
}

void compressionData(string inName, string outName)//nén dữ liệu từ file inName thành file outName
{
	char data[MAX_CHAR];//lưu kí tự char data[MAX_CHAR]
	long freq[MAX_CHAR];//lưu tần số tương ứng long freq[MAX_CHAR]
	unsigned size;
	unsigned length = 0;
	vector<Code>table;//lưu mảng các mã bit của mỗi kí tự
	string arrCode[MAX_CHAR];
	ofstream outfile;
	outfile.open(outName, ios::binary);
	ifstream infile;
	infile.open(inName, ios::binary);
	//đọc dữ liệu từ file và tìm tần số xuất hiên các kí tự
	if (!DataAndFReq(inName, data, size, freq))
	{
		cout << "Couldn't open file";
		exit(1);
	}
	if (!outfile)
	{
		cout << "Couldn't open file";
		exit(1);
	}
	if (size == 0)
	{
		outfile << 0;
	}
	else if (size == 1)
	{
		outfile << size;
		outfile << data[0];
		outfile << freq[0];
	}
	else
	{
		table = findCodeTable(data, freq, size);//tìm mã code của các kí tự tương ứng
		convert(arrCode, table);
		for (int i = 0; i < table.size(); i++)
		{
			length += table[i].code.size() * table[i].frequence;
		}
		outfile << size;
		outfile << ' ';
		outfile << length;
		for (int i = 0; i < size; i++)
		{
			outfile << data[i];
			outfile << freq[i];
			outfile << ' ';
		}
		outfile << '\n';

		string enCodedStr = "";
		if (!infile)
		{
			cout << "couldn't open file";
			exit(1);
		}

		char d = 0;
		char c;
		while (infile)
		{
			infile.get(c);
			if (infile.eof())
				break;
			enCodedStr += arrCode[unsigned char(c)];
			while (enCodedStr.size() >= 8)
			{
				for (int i = 0; i < 8; i++)//tách 8 bit -> kí tự lưu vào file nén
				{
					if (enCodedStr[i] == '1')
						d |= (1 << (7 - (i % 8)));
					if (i == 7)
					{
						outfile << d;
						d = 0;
						break;
					}
				}
				enCodedStr.erase(0, 8);
			}
		}
		while (enCodedStr.size())//đảm bảo đầy đủ số bit cho mỗi kí tự
		{
			if (enCodedStr.length() % 8 == 0)
				break;
			enCodedStr += '0';
		}
		for (int i = 0; enCodedStr.size() && i < 8; i++)//tách 8 bit -> kí tự lưu vào file nén của phần chuỗi còn lại nếu còn
		{
			if (enCodedStr[i] == '1')
				d |= (1 << (7 - (i % 8)));
			if (i == 7)
			{
				outfile << d;
				d = 0;
				break;
			}
		}
	}

	infile.close();
	outfile.close();

}

void decodedData(ifstream& infile, string outName)//giải nén dữ liệu từ file inName ra file outName
{

	ofstream outfile;
	outfile.open(outName, ios::binary);
	if (!infile)
	{
		cout << "Couldn't open file";
		exit(1);
	}

	char c;
	unsigned ts;//tan so
	char data[MAX_CHAR];
	long freq[MAX_CHAR];
	unsigned size = 0;
	unsigned length = 0;//số lượng bit trong encodedData
	int j = 0;

	//đọc bảng tần số, data và build encodeData
	infile >> size;
	///
	if(size==0)
		return;
	if (size == 1)
	{
		while (infile)
		{
			infile.get(c);
			if (infile.eof())
				break;
			infile >> ts;
		}
		for (int i = 0; i < ts; i++)
			outfile << c;
	}
	else
	{
		infile.get(c);
		infile >> length;
		unsigned tmp = size;
		string encodedStr = "";
		HuffmanTree* tree = NULL;
		HuffmanNode* treeTmp = NULL;
		int i = 0;
		int k = 0;
		while (infile)
		{
			infile.get(c);
			if (infile.eof())
				break;
			if (j == tmp)
			{
				tree = buildHuffmanTree(data, freq, size);
				treeTmp = tree->array[0];

			}
			if (j < tmp)
			{
				data[j] = c;
				infile >> ts;
				freq[j] = ts;
				infile.get(c);

			}
			else if (j > tmp)//j!=tmp
			{
				i = 0;
				encodedStr += convertDecimalToBinary(c);
				while (k < length && i < encodedStr.size())
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
					i++;
					k++;
				}
				if (k >= length)
					break;
				encodedStr.clear();
			}
			j++;

		}
	}

	outfile.close();
}
void decodedFile(string inName, string outName)
{
	ifstream infile;
	infile.open(inName, ios::binary);
	if (!infile)
	{
		cout << "Couldn't open file";
		exit(1);
	}
	decodedData(infile, outName);
	infile.close();
}

