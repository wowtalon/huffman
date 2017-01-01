#include "huff.h"
#include <time.h>

int main(int argc, char *argv[]) {
	time_t start = clock();
	huff_in(argv[1], argv[2]);
	ifstream file(argv[1]);
	file.seekg(0, ios::end);
	streampos ps = file.tellg();
	cout << "ѹ��ǰ��СΪ��" << ps << "bytes" << endl;
	file.close();
	file.open(argv[2]);
	file.seekg(0, ios::end);
	ps = file.tellg();
	cout << "ѹ�����СΪ��" << ps << "bytes" << endl;
	file.close();
	time_t end = clock();
	cout << "��������" << double(end - start)/CLOCKS_PER_SEC << "S" << endl;
	return 0;
}

