#include<bits/stdc++.h>
#define MOD 1000000007

using namespace std;
ifstream fin("trigigel.in");
ofstream fout("trigigel.out");


int main() {
	unsigned long long int n;
	fin >> n;
	unsigned long long int count[3] = {1, 0, 0};
	int prev = 0;
	int current = 1;
	for(int i = 1; i < n; i++) {
		count[current] = (count[current] + count[prev] + 1) % MOD;
		prev = current;
		current = (i+1) % 3;
	}
	int res = (count[0] + count[1] + count[2]) % MOD;
	fout << res;
	return 0;
}
