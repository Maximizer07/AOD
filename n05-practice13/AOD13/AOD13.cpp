#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

vector <vector<int>> arr;
struct Node {
	int num;
	vector <pair<Node*, int>> sv;
	Node(int num);
};
Node::Node(int num) {
	this->num = num;
}
vector <Node*> gr;
void graph() {
	gr.resize(arr.size());
	for (int i = 0; i < arr.size(); i++) gr[i] = new Node(i + 1);
}

void create() {
	bool* b = new bool[arr.size()];
	for (int i = 1; i < arr.size(); i++) b[i] = false;
	b[0] = true;
	int min, num_par, num_ch;
	for (int k = 0; k < gr.size() - 1; k++) {
		min = 10000000000;
		for (int i = 0; i < arr.size(); i++) {
			if (b[i] == true) {
				for (int j = 0; j < arr[i].size(); j++) {
					if (!b[j] and arr[i][j] != 0 and arr[i][j] < min) {
						num_par = i;
						num_ch = j;
						min = arr[i][j];
					}
				}
			}
		}
		gr[num_par]->sv.push_back(make_pair(gr[num_ch], min));
		gr[num_ch]->sv.push_back(make_pair(gr[num_par], min));
		b[num_ch] = true;
	}
}

void input() {
	int nodes, k, number, length;
	cout << "Введите количество вершин графа: ";
	cin >> nodes;
	arr.resize(nodes);
	for (int i = 0; i < arr.size(); i++) {
		arr[i].resize(nodes);
		for (int j = 0; j < arr[i].size(); j++) arr[i][j] = 0;
	}
	for (int i = 0; i < arr.size() - 1; ++i) {
		cout << "Количество связей у вершины " << i + 1 << " (без повторений): ";
		cin >> k;
		for (int j = 0; j < k; j++) {
			cout << j + 1 << " ребро:" << endl;
			cout << "   Номер вершины, к которой идёт связь: ";
			cin >> number;
			cout << "   Длина связи: ";
			cin >> length;
			arr[i][number - 1] = length;
			arr[number - 1][i] = length;
		}
	}
}

void print() {
	vector <vector<int>> ost_tree;
	ost_tree.resize(arr.size());
	for (int i = 0; i < ost_tree.size(); i++) {
		ost_tree[i].resize(ost_tree.size());
		for (int j = 0; j < ost_tree[i].size(); j++) ost_tree[i][j] = 0;
	}
	for (int i = 0; i < gr.size(); i++) {
		for (int j = 0; j < gr[i]->sv.size(); j++) {
			ost_tree[gr[i]->num - 1][gr[i]->sv[j].first->num - 1] = gr[i]->sv[j].second;
			ost_tree[gr[i]->sv[j].first->num - 1][gr[i]->num - 1] = gr[i]->sv[j].second;
		}
	}
	cout << endl;
	cout <<"№  ";
	for (int i = 0; i < ost_tree.size(); i++) cout << i + 1 << " ";
	cout << endl << endl;
	for (int i = 0; i < ost_tree.size(); i++) {
		cout << i + 1 << "  ";
		for (int j = 0; j < ost_tree[i].size(); j++) {
			cout << ost_tree[i][j] << "|";
		}
		cout << endl;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//№ 14.1.1
	/*arr = {
		{0,1,2,0,10},
		{1,0,0,3,6},
	    {2,0,0,4,7},
		{0,3,4,0,11},
		{10,6,7,11,0} 
	};*/
	input();
	graph();
	create();
	print();
}