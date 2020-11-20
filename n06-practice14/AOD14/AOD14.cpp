#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <clocale>
#include <Windows.h>
using namespace std;

struct Letter { 
	char ch;
	int count;
	double frequency;
	Letter* left;
	Letter* right;
	string code;
	Letter(char ch, int count) {
		this->ch = ch;
		this->count = count;
	}
	Letter(Letter* left, Letter* right) {
		ch = 0;
		this->left = left;
		this->right = right;
		this->frequency = left->frequency + right->frequency;
		this->count = left->count + right->count;
	}
};

string str;
vector<Letter*> alphabet;
vector<Letter*> tree;
int length;

void input() {
	getline(cin, str);
	bool flag;
	for (unsigned int i = 0; i < str.size(); ++i) {
		flag = false;
		for (unsigned int j = 0; j < alphabet.size(); ++j) {
			if (alphabet[j]->ch == str[i]) {
				++alphabet[j]->count;
				flag = true;
			}
		}
		if (!flag) alphabet.push_back(new Letter(str[i], 1));
	}
	for (unsigned int i = 0; i < alphabet.size(); ++i) alphabet[i]->frequency = (double)alphabet[i]->count / str.size();

}

void set_code(Letter* let) {
	if (let->ch == 0) {
		let->left->code = let->code + '0';
		let->right->code = let->code + '1';
		set_code(let->left);
		set_code(let->right);
	}
	else return;
}

void make_tree() {
	double min = 0;
	int i_left, i_right;
	tree.resize(alphabet.size());
	for (unsigned int i = 0; i < tree.size(); ++i) tree[i] = alphabet[i];
	while (tree.size() != 1) {
		min = 2;
		for (int i = tree.size() - 1; i >= 0; --i) {
			for (int j = i - 1; j >= 0; --j) {
				if (tree[i]->frequency + tree[j]->frequency < min) {
					min = tree[i]->frequency + tree[j]->frequency;
					i_left = j;
					i_right = i;
				}
			}
		}
		tree.push_back(new Letter(tree[i_left], tree[i_right]));
		tree.erase(tree.begin() + i_right);
		tree.erase(tree.begin() + i_left);
	}
	set_code(tree[0]);
}

void output() {
	length = 0;
	for (unsigned int i = 0; i < str.size(); ++i) {
		for (unsigned int j = 0; j < alphabet.size(); ++j) {
			if (str[i] == alphabet[j]->ch) {
				cout << alphabet[j]->code << ' ';
				length += alphabet[j]->code.size();
			}
		}
	}
}

void output_code(Letter* let) {
	for (unsigned int i = 0; i < alphabet.size(); i++)
		cout << alphabet[i]->ch << " " << alphabet[i]->code << endl;
}

void task() {
	cout << "\nКоэффициент сжатия относительно кодировки ascii - " << (double)8 * str.size() / (length);
	int count = 0;
	for (unsigned int pow = 1; pow < alphabet.size(); pow *= 2) ++count;
	cout << "\nКоэффициент сжатия относительно равномерного кода - " << (long double)(count * str.size()) / length;
	cout << "\nСредняя длина кода = " << (double)length / str.size();
	double disp = 0;
	for (unsigned int i = 0; i < str.size(); ++i) {
		for (unsigned int j = 0; j < alphabet.size(); ++j) {
			if (str[i] == alphabet[j]->ch)
				disp += (alphabet[j]->code.size() - (double)length / str.size()) * (alphabet[j]->code.size() - (double)length / str.size());
		}
	}
	disp /= str.size();
	cout << "\nДисперсия = " << disp;
}

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите строку для кодирования:\n";
	input();
	make_tree();
	output_code(tree[0]);
	output();
	task();
}