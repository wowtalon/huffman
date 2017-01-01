#include "huff.h"

#define TEST_ORIGIN "E:\\Desktop\\test1.txt"
#define TEST_ZIPPED "E:\\Desktop\\test_out.haff"
#define TEST_UNZIPPED "E:\\Desktop\\test_out.txt"

void test_write();
void test_read();
void test1();
void test();

//int main() {
//	huff_in();
//	huff_out();
//	return 0;
//}

void test_write() {
	fstream file;
	string s = ""; 
	string tmp = "";
	file.open(TEST_ORIGIN, ios::in);
//	while(!file.eof()) {
//		char ch;
//		file.read((char*)&ch, sizeof(char));
//		s.push_back(ch);
//	}
	while(getline(file, tmp)) {
		s = s + tmp + '\n';
		// cout << tmp << endl;
	}
	s.erase(s.size() - 1);
	// cout << s << endl;
	file.close();
	vector<Pair> v = make_dict(s);
	int size = v.size();
	long len = s.size();
	s = code(s);
	//file.open(TEST_ZIPPED, ios::binary|ios::out);
	//writeFile(TEST_ZIPPED, size, len, s, v);
}

void test_read() {
	fstream file;
	vector<Pair> v;
	string s = ""; 
	int size;
	long len;
	char ch;
	int count;
	//string s;
	file.open(TEST_ZIPPED, ios::binary|ios::in);
	file.read((char*)&size, sizeof(int));
	file.read((char*)&len, sizeof(long));
	cout << size << " " << len << endl;
	for(int i = 0; i < size; i++) {
		file.read((char*)&ch, sizeof(char));
		file.read((char*)&count, sizeof(int));
		v.push_back(make_pair<char, int>(ch, count));
	}
	while(!file.eof()) {
		file.read((char*)&ch, sizeof(char));
		// cout << ch;
		s.push_back(ch);
	}
	string source = "";
	for(int i = 0; i < s.size(); i++) {
		source += ascToBin(s[i]);
	}
	source = decode(source, v, len);
	cout << "Are You OK?" << endl;
	cout << source << endl;
	file.close();
	file.open(TEST_UNZIPPED, ios::out);
	for(int i = 0; i < source.size(); i++) {
		file.write((char*)&source[i], sizeof(char));
	}
	file.close();
}

void test1() {
	//writeFile(TEST_ZIPPED, 5, 11, "hello,world");
	fstream file;
	file.open(TEST_ZIPPED, ios::binary|ios::in);
	int size;
	long len;
	char ch;
	file.read((char*)&size, sizeof(int));
	file.read((char*)&len, sizeof(long));
	cout << size << " " << len << endl;
	while(len--) {
		file.read((char*)&ch, sizeof(char));
		cout << ch;
	} 
	file.close();
}

void test() {
	// test_write();
	//test_decode();
}

