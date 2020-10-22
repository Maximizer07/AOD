#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cmath>
#include<string>
#include <fstream>
#include<vector>
using namespace std;
struct car_owner {
	int number;
	string brand;
	string info;
	bool stolen;
};
vector<car_owner> car;
void print_info(car_owner a) {
	cout << "Номер машины : " << a.number << " Марка машины : " << a.brand << " Сведения о владельце : " << a.info << " Сведения об угоне : " << a.stolen << endl;
}
void read_from_file() {
	car_owner tmp;
	ifstream in("first.txt");
	while (!in.eof()) {
		in >> tmp.number >> tmp.brand >> tmp.info >> tmp.stolen;
		car.push_back(tmp);
	}
}
void read_from_binary_file() {
	ifstream fin("second.txt", istream::binary);
	car_owner tmp;
	for (unsigned int i = 0; i < car.size(); i++) {
		fin.read((char*)&car.at(i), sizeof(car_owner));
	}
	fin.close();
}

void write_data_to_binary()
{
	car_owner temp;
	ofstream fout("output.txt", ostream::binary);
	for (unsigned int i = 0; i < car.size(); ++i)
	{
		fout.write((char*)&car.at(i), sizeof(car_owner));
	}
	fout.close();
}
void change_stolen() {
	int num;
	cout << "Введите номер автомобиля, у которого нужно установить факт угона\n";
	cin >> num;
	read_from_binary_file();
	for (unsigned int i = 0; i < car.size(); i++) {
		if (car[i].number == num) {
			car[i].stolen = true;
		}
	}
	write_data_to_binary();
}

void print_all_stolen_cars() {
	for (unsigned int i = 0; i < car.size(); i++) {
		if (car[i].stolen == true) print_info(car[i]);
	}
}
int main() {
	setlocale(0,"Rus");
	read_from_file();
	write_data_to_binary();
	read_from_binary_file();
	print_all_stolen_cars();
	change_stolen();
	print_all_stolen_cars();
}