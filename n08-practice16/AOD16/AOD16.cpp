#include <iostream>
#include <algorithm>
#include <queue>
#include <windows.h>
using namespace std;

struct Item {
	float weight;
	int value;
};

struct Node {
	int level, profit, bound;
	float weight;
};

bool compare(Item a, Item b) {
	double r1 = (double)a.value / a.weight;
	double r2 = (double)b.value / b.weight;
	return r1 > r2;
}

int bound(Node u, int n, int knapsackWeight, Item arr[]) {
	if (u.weight >= knapsackWeight)
		return 0;
	int profit_bound = u.profit;
	int j = u.level + 1;
	int totalWeight = u.weight;
	while ((j < n) && (totalWeight + arr[j].weight <= knapsackWeight)) {
		totalWeight += arr[j].weight;
		profit_bound += arr[j].value;
		j++;
	}
	if (j < n)
		profit_bound += (knapsackWeight - totalWeight) * arr[j].value /
		arr[j].weight;
	return profit_bound;
}

int knapsack(int W, Item arr[], int n) {
	sort(arr, arr + n, compare);
	queue <Node> Q;
	Node u, v;
	u.level = -1;
	u.profit = u.weight = 0;
	Q.push(u);

	int maxProfit = 0;
	while (!Q.empty()) {
		u = Q.front();
		Q.pop();

		if (u.level == -1)
			v.level = 0;

		if (u.level == n - 1)
			continue;

		v.level = u.level + 1;
		v.weight = u.weight + arr[v.level].weight;
		v.profit = u.profit + arr[v.level].value;
		if (v.weight <= W && v.profit > maxProfit)
			maxProfit = v.profit;
		v.bound = bound(v, n, W, arr);

		if (v.bound > maxProfit)
			Q.push(v);

		v.weight = u.weight;
		v.profit = u.profit;
		v.bound = bound(v, n, W, arr);
		if (v.bound > maxProfit)
			Q.push(v);
	}

	return maxProfit;
}

int main() {
	setlocale(0, " ");
	SetConsoleCP(1251);           
    SetConsoleOutputCP(1251);
	int W = 10;
	Item arr[] = { {1,2},{2,23},{2,95},{2,79},{3,10} };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "Маскимальная возможная стоимость: " << knapsack(W, arr, n);
	return 0;
}