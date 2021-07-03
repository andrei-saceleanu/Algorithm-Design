#include<bits/stdc++.h>
typedef unsigned long long int ulli;

using namespace std;
ifstream fin("ridge.in");
ofstream fout("ridge.out");
int *h, *c;


int main() {
	ulli n;
	fin >> n;
	h = new int[n];
	c = new int[n];
	for(int i = 0; i < n; i++) {
		fin >> h[i] >> c[i];
	}
	ulli ** dp = new ulli*[n];
	for(int i = 0; i < n; i++) {
		dp[i] = new ulli[3];
	}
	// caz de baza pentru primul element
	dp[0][0] = 0;  // 0 excavari nu costa nimic
	dp[0][1] = (h[0] > 0 ? c[0] : 0);  // 1 excavare costa c[0] sau 0
	dp[0][2] = (h[0] > 1 ? 2*c[0] : 0);  // 2 excavari costa 2*c[0] sau 0

	for(int i = 1; i < n; i++) {
		for(int j = 0; j < 3; j++) {
			ulli mn = ULLONG_MAX;
			if(h[i]-j >= 0) {  // daca pot face j excavari
				// gasesc minimul din costurile admisibile anterioare
				// admisibil = adiacentii raman diferiti
				if(h[i]-j != h[i-1]) {
					mn = fmin(mn, dp[i-1][0]);
				}
				if((h[i-1]-1 >= 0) && (h[i]-j != h[i-1]-1)) {
					mn = fmin(mn, dp[i-1][1]);
				}
				if((h[i-1]-2 >= 0) && (h[i]-j != h[i-1]-2)) {
					mn = fmin(mn, dp[i-1][2]);
				}
				dp[i][j] = j*c[i] + mn;  // la sol. se adauga costul a j excv.
			} else {
				// daca nu se pot face j excavari,solutia subproblemei
				// este Inf (ULLONG_MAX)
				dp[i][j] = ULLONG_MAX;
			}
		}
	}
	ulli res = ULLONG_MAX;
	for(int i = 0; i < 3; i++) {
		res = fmin(res, dp[n-1][i]);
	}
	fout << res;
	return 0;
}
