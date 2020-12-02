#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> multiply;
vector<vector<int>> brackets;
vector<int> matrixes;
string answer;
void get_expression(int i, int j, int flag) {
	if (i == j) answer += "A";
	else {
		if (flag != 0) answer += "(";
		get_expression(i, brackets[i][j], 1);
		answer += "*";
		get_expression(brackets[i][j] + 1, j, 1);
		if (flag != 0) answer += ")";
	}
}
void calc() {
	int n = matrixes.size() - 1;
	for (int i = 0; i < n; i++) {
		multiply.push_back(vector <int>());
		brackets.push_back(vector <int>());
		for (int a = 0; a < n; a++) {
			multiply[i].push_back(0);
			brackets[i].push_back(0);
			}
	}
	int j;
	for (int l = 1; l < n; l++) {
		for (int i = 0; i < n - l; i++) {
			j = i + l;
			multiply[i][j] = INT_MAX;
			for (int k = i; k < j; k++) {
				int q = multiply[i][k] + multiply[k + 1][j] + matrixes[i] * matrixes[k + 1] * matrixes[j + 1];
				if (q < multiply[i][j]) {
					multiply[i][j] = q;
					brackets[i][j] = k;
				}
			}
		}
	}
	get_expression(0, n - 1, 0);
	cout << "\nОптимальный порядок: " << answer << "\n";
}

int main() {
	setlocale(LC_ALL, "Russian");
	matrixes = { 5, 10, 3, 12, 5, 50, 6 };
	calc();
}