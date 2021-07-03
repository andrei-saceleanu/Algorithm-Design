#include<bits/stdc++.h>

using namespace std;
ifstream fin("stocks.in");
ofstream fout("stocks.out");
int mat[100][3];  // fiecare rand de 3 elemente reprezinta o actiune
int ***dp;

int main() {
	int n, B, L;
	fin >> n >> B >> L;
	for(int i = 0; i < n; i++) {
		fin >> mat[i][0] >> mat[i][1] >> mat[i][2];
	}
	dp = new int**[n+1];
	for(int i = 0; i <= n; i++) {
		dp[i] = new int*[B+1];
		for(int j = 0; j <= B; j++) {
			dp[i][j] = new int[L+1];
		}
	}
	int loss = -1;
	int profit = -1;
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= B; j++) {
			for(int k = 0; k <= L; k++) {
				if(i == 0 || j == 0 || k == 0) {
					dp[i][j][k] = 0;
				} else {
					if(mat[i-1][0] > j) {  // currentValue > buget j,nu includ
						dp[i][j][k] = dp[i-1][j][k];
					} else {
						loss = mat[i-1][0] - mat[i-1][1];
						profit = mat[i-1][2] - mat[i-1][0];
						if(loss > k)  // loss curent > l. admisibil k,nu includ
							dp[i][j][k] = dp[i-1][j][k];
						else
						// solutia subproblemei este maximul din 2 situatii
						// nu includ i-1 / includ si adun profitul
							dp[i][j][k] = fmax(dp[i-1][j][k], profit+dp[i-1][j-mat[i-1][0]][k-loss]);
					}
				}
			}
		}
	}
	fout << dp[n][B][L];
	return 0;
}
