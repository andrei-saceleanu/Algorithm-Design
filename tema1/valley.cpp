#include<bits/stdc++.h>

using namespace std;

ifstream fin("valley.in");
ofstream fout("valley.out");
int *v, n;

int main() {
	fin >> n;
	v = new int[n];
	int mn = INT_MAX;
	int index = -1;
	// flag-uri de verificare monotonie a intregului sir
	int is_increasing = 1;
	int is_decreasing = 1;
	for(int i = 0; i < n; i++) {
		fin >> v[i];
		if(i >= 1) {
			// actualizare flag-uri daca nu se respecta monotonia
			if(v[i] < v[i-1])
				is_increasing = 0;
			if(v[i] > v[i-1])
				is_decreasing = 0;
		}

		if(v[i] < mn) {
			mn = v[i];
			index = i;
		}
	}
	if(is_increasing) {
		fout << (v[1] - v[0]);
	} else if (is_decreasing) {
		fout << (v[n-2] - v[n-1]);
	} else {
		unsigned long long int cost = 0;
		int diff = 0;
		for(int i = 1; i <= index; i++) {
			// "excavare" element astfel incat sa fie identic cu cel precedent
			if(v[i] > v[i-1]) {
				diff = v[i] - v[i-1];
				cost += diff;
				v[i] -= diff;
			}
		}
		for(int i = n - 2; i >=index; i--) {
			// "excavare" element astfel incat sa fie identic cu succesorul
			if(v[i] > v[i+1]) {
				diff = v[i] - v[i+1];
				cost += diff;
				v[i] -= diff;
			}
		}
		fout << cost;
	}

	return 0;
}
