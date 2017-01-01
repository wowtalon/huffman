#include "huff.h"

#define TEST_ORIGIN "E:\\Desktop\\test1.txt"
#define TEST_ZIPPED "E:\\Desktop\\test_out.haff"
#define TEST_UNZIPPED "E:\\Desktop\\test_out.txt"

void test_read();
void test_make_dict();
void test_make_huff();
void test_code();
void test_write();
void test_decode();
void test();

int main() {
	test();
	return 0;
}

// test OK
void test_read() {
	string file;
	cin >> file;
	cout << readFile(file);
}

// test OK
void test_make_dict() {
	string file;
	cout << "选择测试文件：" << endl;
	cin >> file;
	file = readFile(file);
	vector<Pair> dic = make_dict(file);
	print(dic);
}

void test_make_huff() {
	string file;
	cout << "选择测试文件：" << endl;
	cin >> file;
	file = readFile(file);
	vector<Pair> dic = make_dict(file);
	Node *root = make_huff(dic);
	map<CHAR, string> map = make_map(root);
	print(map);
}

void test_code() {
	string file;
	cout << "选择测试文件：" << endl;
	cin >> file;
	file = readFile(file);
	cout << code(file) << endl;
}

void test_write() {
	string file;
	cout << "选择压缩测试文件：" << endl;
	file = TEST_ORIGIN;
	file = readFile(file);
	string content = code(file);
	cout << "选择保存路径：" << endl;
	file = TEST_ZIPPED;
	writeFile(file, content);
//	fstream outf;
//	outf.open(file.c_str(), ios::binary|ios::out);
//	outf.write(content.c_str(), sizeof(content));
//	outf.close();
}

void test_decode() {
	string file;
	cout << "选择解压测试文件：" << endl;
	// cin >> file;
	file = TEST_ZIPPED;
	file = readFile(file);
	Node *root;
	vector<Pair> v;
	string source;
	int size;
	cout << "source : " << file << endl;
	parse(file, source, size, v);
	string content = "";
	for(int i = 0; i < source.size(); i++) {
		content.append(ascToBin(source[i]));
	}
	cout << content << endl;
	print(v);
	root = make_huff(v);
	map<CHAR, string> haffmap = make_map(root);
	print(haffmap);
	cout << "请输入保存路径:" << endl;
	// cin >> file;
	file = TEST_UNZIPPED;
	writeFile(file, decode(content, root, size));
	cout << decode(content, root, size) << endl;
}

void test() {
	test_write();
	test_decode();
}

