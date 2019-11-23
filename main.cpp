#include"Huffman.h"
#include"File.h"


int main()
{
	char in[] = "Text.txt";
	char out[] = "kq.txt";
	char c[] = "test.txt";
	

	compressionData(in,out);
	decodedData(out,c);
	
	


	return 0;
}