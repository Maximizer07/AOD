#include <iostream>
#include <windows.h>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class Item {
public:
	string name;
	int number;

	Item(string name, int number) {
		this->name = name;
		this->number = number;
	}

	void output() {
		cout <<" "<<this->name << " " << this->number;
	}
};

template<typename T>
class HashTable {
	vector<list<T>> HT;
	int size = 10;
	int hash(const T& num) {
		return num.number % size;
	}

	int hash(int num) {
		return num % size;
	}

public:

	HashTable() {
		size = 10;
		HT.resize(size);
	}

	void add(const T& num) {
		HT[hash(num)].push_back(num);
		if (HT[hash(num)].size() > 3) rehash();
	}

	void rehash() {
		queue<T> qe;
		for (int i = 0; i < size; ++i) {
			for (T elem : HT[i]) {
				qe.push(elem);
			}
		}
		size = size * 2 + 1;
		HT.clear();
		HT.resize(size);
		while (!qe.empty()) {
			this->add(qe.front());
			qe.pop();
		}
	}
	void output() {
		for (int i = 0; i < size; ++i) {
			if (HT[i].size() == 0) continue;
			cout << i<<":";
			for (T elem : HT[i]) {
				elem.output();
			}
			cout << "\n";
		}
	}

	T find(int num) {
		for (T elem : HT[hash(num)]) {
			if (elem.number == num) return elem;
		}
		return T("Элемент не найден", 0);
	}

	void del(int num) {
		HT[hash(num)].erase(
			remove_if(HT[hash(num)].begin(), HT[hash(num)].end(), [num](const T t) 
				{
					return t.number == num;
				}
		), HT[hash(num)].end());
	}
};

int main() {
	SetConsoleCP(1251);              
    SetConsoleOutputCP(1251); 
	HashTable<Item> HT;
	HT.add(Item("МГУ", 90301));
	HT.add(Item("РТУ МИРЭА", 90301));
	HT.add(Item("НИУ ВШЭ", 90301));
	HT.add(Item("МЭИ", 90304));
	HT.add(Item("МАИ", 10302));
	HT.add(Item("МГТУ", 100501));
	HT.add(Item("МПГУ", 150306));
	HT.add(Item("РХТУ", 380303));
	cout << "Хэш-таблица до удаления\n\n";
	HT.output();
	HT.del(90304);
	cout << endl << "Производим поиск\n\n";
	cout << HT.find(380303).name << endl;
	cout << HT.find(150306).name << endl;
	cout << HT.find(100000).name << "\n";
	cout << endl << "Хэш-таблица после удаления\n\n";
	HT.output();
	cout << endl << "Введите номер для вывода списка\n\n";
	HT.output();
}