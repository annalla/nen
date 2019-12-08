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

	for (int i = 0; i <MAX_CHAR; i++)
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

string encodedHuffmanData(string name, vector<Code>codeTable)//tạo chuỗi nén dữ liệu
{
	string enCodedStr = "";
	ifstream infile;
	infile.open(name, ios::binary);
	//infile.open(name, ios::in);
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
				enCodedStr +=  codeTable[i].code;
				//enCodedStr.append(codeTable[i].code);
				/////////////////Chi tim duoc 1 ky tu c trong bang codeTable
				break;
			}
		}
	}
	infile.close();
	return enCodedStr;
}
void compressionData(string inName, string outName)//nén dữ liệu từ file inName thành file outName
{
	char data[MAX_CHAR];//lưu kí tự char data[MAX_CHAR]
	long freq[MAX_CHAR];//lưu tần số tương ứng long freq[MAX_CHAR]
	unsigned size;
	vector<Code>arrCode;//lưu mảng các mã bit của mỗi kí tự
	//đọc dữ liệu từ file và tìm tần số xuất hiên các kí tự
	if (!DataAndFReq(inName, data, size, freq))
	{
		cout << "Couldn't open file";
		exit(1);
	}
	arrCode = findCodeTable(data, freq, size);//tìm mã code của các kí tự tương ứng
	ofstream outfile;
	outfile.open(outName, ios::binary);
	//outfile.open(outName, ios::out);
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

	outfile << '\n';//6 1 a4 b3 »1 ¿1 ï1 
	//6 1 a4 b3 »1 ¿1 ï1
	//	ýàÊ€

	string enCodedStr = "";
	ifstream infile;
	infile.open(inName, ios::binary);
	//infile.open(inName, ios::in);
	if (!infile)
	{
		cout << "couldn't open file";
		exit(1);
	}

	char c;
	char d = 0;
	while (infile)
	{
		infile.get(c);
		if (infile.eof())
			break;
		for (int i = 0; i < arrCode.size(); i++)//tìm chuỗi mã hóa
		{
			if (c == arrCode[i].c)
			{
				arrCode[i].code[arrCode[i].size] = '\0';
				enCodedStr += arrCode[i].code;
				//enCodedStr.append(codeTable[i].code);
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
				break;
			}
		}
	}
	while (enCodedStr.size())//đảm bảo đầy đủ số bit cho mỗi kí tự
	{
		if (enCodedStr.length() % 8 == 0)
			break;
		enCodedStr += '0';
	}
	for (int i = 0;enCodedStr.size() && i < 8; i++)//tách 8 bit -> kí tự lưu vào file nén
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
	infile.close();
	outfile.close();
	
}
void decodedFile(string inName, string outName)//giải nén dữ liệu từ file inName ra file outName
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

void decodedData(ifstream&infile, string outName)
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
	int j = 0;

	//đọc bảng tần số, data và build encodeData
	infile >> size;
	unsigned tmp = size;
	string encodedStr = "";
	HuffmanTree* tree = NULL;
	HuffmanNode* treeTmp = NULL;
	vector<Code>arr;
	unsigned length = 0;//số lượng bit trong encodedData
	int i = 0;
	int k = 0;

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
		else if (j > tmp)
		{
			i = 0;
			encodedStr += convertDecimalToBinary(c);
			while (i < encodedStr.size())
			//while (k < length && i < encodedStr.size())
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
		else
		{
			tree = buildHuffmanTree(data, freq, size);
			treeTmp = tree->array[0];
			arr = findCodeTable(data, freq, size);
			for (int i = 0; i < arr.size(); i++)
			{
				length += arr[i].size*arr[i].frequence;
			}
		}
		j++;
	}
	//HuffmanTree*tree= buildHuffmanTree(data, freq, size);
	//HuffmanNode* treeTmp = tree->array[0];
	//vector<Code>arr;
	//arr = findCodeTable(data, freq, size);
	//unsigned length = 0;//số lượng bit trong encodedData
	//for (int i = 0; i < arr.size(); i++)
	//{
	//	length += arr[i].size*arr[i].frequence;
	//}
	////decodeData 
	//for (int i = 0; i <length; i++)
	//{
	//
	//	if (encodedStr[i] == '0')
	//	{
	//		treeTmp = treeTmp->pLeft;
	//	}
	//	else
	//		treeTmp = treeTmp->pRight;
	//	if (!treeTmp->pLeft && !treeTmp->pRight)
	//	{
	//		outfile << treeTmp->c;
	//		treeTmp = tree->array[0];
	//	}

	//}

	
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