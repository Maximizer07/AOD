#include <iostream>
#include <Windows.h>
#include <queue>
using namespace std;

void inputarr(int* arr, int n) {
	cout << "Введите элементы массива: ";
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}

void outputarr(int* arr, int n) {
	cout << "Сортированный массив: ";
	for (int i = 0; i < n; i++)
		if (i != n - 1) 
			cout << arr[i] << ' ';
		else 
			cout << arr[i];
}
int maxarr(int* arr, int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) max = arr[i];
	}
	return max;
}
int discharge(int a) {
	int i = 0;
	while (a > 0) {
		i++;
		a/=10;
	}
	return i;
}
int digit(int x, int position) {
	int num=0;
	for(int i=0;i<position;i++) {
		num = x % 10;
		x=x/10;
	}
	return num;
}
void RadixSort(int* arr, int n) {
	queue <int> que[10];
	int max = discharge(maxarr(arr, n));
	for (int i=0;i<max;i++) {
		for (int j = 0; j < n; j++) {
			que[digit(arr[j],i+1)].push(arr[j]);
		}
		int index = 0;
		for (int j = 0; j < 10; j++) {
			while (!que[j].empty()) {
				arr[index] = que[j].front();
				que[j].pop();
				index++;				}	
		}
	}
}
void start(int* arr,int n) {
	inputarr(arr, n);
	RadixSort(arr, n);
	outputarr(arr, n);
}
int main()
{
	setlocale(LC_ALL, " ");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите размер массива целых чисел: ";
	int n;
	cin >> n;
	int* arr = new int[n];
	start(arr, n);
}