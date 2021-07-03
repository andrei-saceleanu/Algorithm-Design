#include<bits/stdc++.h>
#define MOD 1000000007


using namespace std;

typedef unsigned long long int ulli;
ifstream fin("trigigel.in");
ofstream fout("trigigel.out");

// matricile de tranzitie intre stari
// vezi README pentru justificare
ulli a[4][4] = {
	{1, 0, 1, 1},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
};
ulli b[4][4] = {
	{1, 0, 0, 0},
	{1, 1, 0, 1},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
};
ulli c[4][4] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 1},
	{0, 0, 0, 1}
};
ulli g[4][4] = {
	{2, 1, 1, 3},
	{1, 1, 0, 1},
	{1, 1, 1, 2},
	{0, 0, 0, 1}
};


// inmultire matrice 4x4 modulo MOD
// res = a*b
void mul_mat(ulli res[4][4], ulli a[4][4], ulli b[4][4]) {
	ulli c[4][4];
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			c[i][j] = 0;
			for(int k = 0; k < 4; k++) {
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
			}
		}
	}
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			res[i][j] = c[i][j];
		}
	}
}


// exponentiere logaritmica matrice 4x4
// a = a ^ n
void exp_mat(ulli a[4][4], ulli n) {
	ulli temp[4][4] = {0};
	temp[0][0] = 1;
	temp[1][1] = 1;
	temp[2][2] = 1;
	temp[3][3] = 1;
	while(n) {
		if(n % 2) {
			mul_mat(temp, temp, a);
		}
		n = n >> 1;
		mul_mat(a, a, a);
	}
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			a[i][j] = temp[i][j];
		}
	}
}

int main() {
	ulli n;
	fin >> n;
	if(n == 1) {
		fout << 1;
	} else {
		ulli cat = (n - 1) / 3;
		ulli r = (n - 1) % 3;
		exp_mat(g, cat);
		// completare matrice finala de tranzitie de la starea initiala
		// la cea dorita
		if(r == 1)
			mul_mat(g, b, g);
		if(r == 2) {
			mul_mat(g, b, g);
			mul_mat(g, c, g);
		}
		// vezi README pentru alegerea valorilor din matricea finala g
		unsigned long long int res1 = (g[0][0] + g[0][3]) % MOD;
		unsigned long long int res2 = (g[1][0] + g[1][3]) % MOD;
		unsigned long long int res3 = (g[2][0] + g[2][3]) % MOD;
		unsigned long long int res = (res1 + res2 + res3) % MOD;
		fout << res;
	}
	return 0;
}
