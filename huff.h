#ifndef H_HUFF_INC
#define H_HUFF_INC

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <map>
#include <sstream>

#define ASC_BIT 7

using namespace std;

typedef char CHAR;
typedef pair<CHAR, int> Pair;

struct Node {
	int value;
	bool encode;
	char ch;
	Node *left;
	Node *right;
	Node(int v = 0, bool en = false, char c = '+', Node *l = NULL, Node *r = NULL):value(v), encode(en), ch(c), left(l), right(r) {}
};

void huff_in();
void huff_out();

vector<Pair> make_dict(string);
Node *make_huff(vector<Pair>&);
map<CHAR, string> make_map(Node*);

string code(string);
string decode(string, Node*, int);
void toHuff(map<CHAR, string>&, Node*, string);
string readFile(string);
void parse(string, string&, int&, vector<Pair>&t);
void writeFile(string, string);

string ascToBin(unsigned char);
string binToAsc(string);
string otob(int);
int btoo(string);
void print(const vector<Pair>&);
void print(const map<CHAR, string>&);

bool com(const Pair&, const Pair&);
bool comNode(Node*, Node*);

#endif 

