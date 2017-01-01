#include "huff.h"

void huff_in() {
	cout << "请选择您要压缩的文件：" << endl;
	string file;
	cin >> file;
	string source = readFile(file);
	cout << source << endl;
	cout << "请选择您要保存的路径：" << endl;
	cin >> file;
	cout << code(source) << endl;
	// writeFile(file, code(source));
}

void huff_out() {
	cout << "请选择您要解压的文件：" << endl;
	string file;
	cin >> file;
	string source;
	int size = 0;
	vector<Pair> dict;
	// readFile(file, source, size, dict);
	Node *root = make_huff(dict);
	map<CHAR, string> map = make_map(root);
	
	cout << "请选择您要保存的路径：" << endl;
	cin >> file;
	// writeFile(file, decode(source, root, size));
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
	cout << "==========================coding...========================" << endl;
	// cout << "source: " << source << endl;
	string r;
	vector<Pair> dict = make_dict(source);
	Node *root = make_huff(dict);
	map<CHAR, string> map = make_map(root);
	
	print(dict);
	
	char buffer[255];
	itoa(dict.size(), buffer, 10);
	r.append(buffer);
	r += " ";
	itoa(source.size(), buffer, 10);
	r.append(buffer);
	r += " ";
	
	for(vector<Pair>::iterator i = dict.begin(); i != dict.end(); i++) {
		r += "[";
		r.push_back((*i).first);
		// r.push_back(',');
		itoa((*i).second, buffer, 10);
		r.append(buffer);
		r += "]";
	}
	
	string content = "";
	for(int i = 0; i < source.size(); i++) {
		content += map[source[i]];
	}
	while(content.size() % ASC_BIT != 0) {
		content.push_back('0');
	}
	// r += content;
	cout << content << endl;
	content = binToAsc(content);
	// cout << content << endl;
	r.append(content);
	cout << "============================================================" << endl;
	return r;
}

string decode(string source, Node *root, int size) {
	// cout << "===========================source===========================" << endl;
	// cout << source << endl;
	string r = "";
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

void writeFile(string file, int size, long len, string content) {
	fstream out;
	out.open(file.c_str(), ios::binary|ios::out);
	out.write((char*)&size, sizeof(int));
	out.write((char*)&len, sizeof(long));
	for(int i = 0; i < content.size(); i++) {
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
	cout << r << endl;
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

