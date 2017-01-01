#include "huff.h"

void huff_in(char *in, char *out) {
	fstream file;
	// cout << "请选择您要压缩的文件：" << endl;
	// string f;
	// cin >> f;
	string s = ""; 
	file.open(in, ios::in);
	while(!file.eof()) {
		char ch;
		file.read((char*)&ch, sizeof(char));
		s.push_back(ch);
	}
	file.close();
	vector<Pair> v = make_dict(s);
	int size = v.size();
	long len = s.size();
	s = code(s);
	// cout << "请选择您要保存的路径：" << endl;
	// cin >> f;
	//file.open(TEST_ZIPPED, ios::binary|ios::out);
	writeFile(out, size, len, s, v);
}

void huff_out(char *in, char *out) {
	fstream file;
	vector<Pair> v;
	string s = ""; 
	int size;
	long len;
	char ch;
	int count;
	// cout << "请选择您要解压的文件：" << endl;
	// string f;
	// cin >> f;
	file.open(in, ios::binary|ios::in);
	file.read((char*)&size, sizeof(int));
	file.read((char*)&len, sizeof(long));
	// cout << size << " " << len << endl;
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
	// cout << "Are You OK?" << endl;
	// cout << source << endl;
	file.close();
	// cout << "请选择您要保存的路径：" << endl;
	// cin >> f;
	file.open(out, ios::out);
	for(int i = 0; i < source.size(); i++) {
		file.write((char*)&source[i], sizeof(char));
	}
	file.close();
}

vector<Pair> make_dict(string s) {
	vector<Pair> r;
	for(int i = 0; i < s.size(); i++) {
		int tmp = -1;
		for(int j = 0; j < r.size(); j++) {
			if(r[j].first == s[i]) {
				tmp = j;
				break;
			}
		}
		if(tmp >= 0) r[tmp].second++;
		else r.push_back(make_pair<CHAR, int>(s[i], 1));
	}
	return r;
}

Node *make_huff(vector<Pair> &v) {
	vector<Node*> t;
	Node *node;
	sort(v.begin(), v.end(), com);
	for(int i = 0; i < v.size(); i++) {
		node = new Node(v[i].second, true, v[i].first);
		t.push_back(node);
		
	}
	while(t.size() > 1) {
		sort(t.begin(), t.end(), comNode);
		int size = t.size();
		int value = t[size - 1]->value + t[size - 2]->value;
		t[size - 1]->value = 0;
		t[size - 2]->value = 1;
		node = new Node(value, false, '+', t[size - 1], t[size - 2]);
		t.pop_back();
		t.pop_back();
		t.push_back(node);
	}
	node = t[0];
	return node;
}

map<CHAR, string> make_map(Node *root) {
	map<CHAR, string> m;
	if(!root) return m;
	else {
		toHuff(m, root, "");
		return m;
	}
}

string code(string source) {
	cout << "coding..." << endl;
	// cout << "source: " << source << endl;
	string r;
	vector<Pair> dict = make_dict(source);
	Node *root = make_huff(dict);
	map<CHAR, string> map = make_map(root);
	
	// print(dict);
	string content = "";
	for(int i = 0; i < source.size(); i++) {
		content += map[source[i]];
	}
	while(content.size() % ASC_BIT != 0) {
		content.push_back('0');
	}
	// r += content;
	// cout << content << endl;
	content = binToAsc(content);
	// cout << content << endl;
	r.append(content);
	cout << "finished." << endl;
	return r;
}

string decode(string source, vector<Pair> &v, int size) {
	cout << "decoding..." << endl;
	// cout << source << endl;
	string r = "";
	Node *root = make_huff(v);
	Node *tmp = root;
	for(int i = 0; i < source.size() && size > 0; i++) {
		if(source[i] == '0') tmp = tmp->left;
		else tmp = tmp->right;
		if(tmp->encode) {
			// cout << ;
			// cout << tmp->ch;
			r.push_back(tmp->ch);
			size--;
			tmp = root;
		}
	}
	cout << "finished." << endl;
	return r;
}

void toHuff(map<CHAR, string> &m, Node *root, string s) {
	if(!root) return ;
	else {
		if(root->encode) {
			m[root->ch] = s;
		} else {
			toHuff(m, root->left, s + "0");
			toHuff(m, root->right, s + "1");
		}
	}
}

string readFile(string file) {
	cout << file << endl;
	ifstream in(file.c_str());
	string r = "";
	string s;
	while(getline(in, s)) {
		r += s;
		r.push_back('\n');
	}
	in.close();
	return r;
}

void parse(string source, string &content, int &size, vector<Pair> &dict) {
	content = "";
	size = 0;
	int sum = 0;
	int i = 0;
	for(i = 0; source[i] != ' ' && i < source.size(); i++) {
		sum *= 10;
		sum += source[i] - '0';
	}
	i++;
	for(; source[i] != ' ' && i < source.size(); i++) {
		size *= 10;
		size += source[i] - '0';
	}
	i++;
	while(sum--) {
		i++;
		CHAR ch = source[i];
		int count = 0;
		i ++;
		while(source[i] != ']') {
			count *= 10;
			count += source[i] - '0';
			i++;
		}
		dict.push_back(make_pair<CHAR, int>(ch, count));
		i++;
	}
	while(i < source.size()) {
		content.push_back(source[i]);
		i++;
	}
}

void writeFile(char *file, int size, long len, string content, vector<Pair> &v) {
	fstream out;
	out.open(file, ios::binary|ios::out);
	out.write((char*)&size, sizeof(int));
	out.write((char*)&len, sizeof(long));
	for(vector<Pair>::iterator i = v.begin(); i != v.end(); i++) {
		out.write((char*)&((*i).first), sizeof(char));
		out.write((char*)&((*i).second), sizeof(int));
	}
	for(int i = 0; i < content.size(); i++) {
		// cout << content[i];
		out.write((char*)&content[i], sizeof(char));
	}
	out.close();
}

string ascToBin(unsigned char ch) {
	int asc = ch;
	// cout << ch << " : " << asc << endl;
	string bin = "";
	while(asc > 0) {
		if(asc % 2 == 0) bin.push_back('0');
		else bin.push_back('1');
		asc /= 2;
	}
	while(bin.size() < 7) bin.push_back('0');
	reverse(bin.begin(), bin.end());
	return bin;
}

string binToAsc(string bin) {
	string r = "";
	int asc = 0;
	for(int i = 0; i < bin.size(); i++) {
		asc *= 2;
		asc += bin[i] - '0';
		if((i + 1) % ASC_BIT == 0) {
			r.push_back((CHAR)asc);
			// cout << (unsigned CHAR)asc << " : " << asc << endl;
			asc = 0;
		}
	}
	// cout << r << endl;
	return r;
}

// 十进制转二进制 
string otob(int arg) {
	string r;
	while(arg > 0) {
		if(arg % 2 == 0) r.push_back('0');
		else r.push_back('1');
		arg /= 2;
	}
	return r;
}

// 二进制转十进制 
int btoo(string arg) {
	int r = 0;
	for(int i = 0; i < arg.size(); i++) {
		r *= 2;
		r += arg[i] - '0';
	}
	return r;
}

void print(const vector<Pair> &v) {
	for(vector<Pair>::const_iterator i = v.begin(); i != v.end(); i++) {
		cout << (*i).first << " " << (*i).second << endl;
	}
}

void print(const map<CHAR, string> &m) {
	for(map<CHAR, string>::const_iterator i = m.begin(); i != m.end(); i++) {
		cout << (*i).first << " " << (*i).second << endl;
	}
}

bool com(const Pair &p1, const Pair &p2) {
	return p1.second > p2.second;
}

bool comNode(Node *n1, Node *n2) {
	return (*n1).value > (*n2).value;
}

