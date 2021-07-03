#include<bits/stdc++.h>


using namespace std;
ifstream fin("crypto.in");
ofstream fout("crypto.out");
unsigned long long int n, b, p, u;

typedef struct {
	int p, u;
} computer;

computer *v1;

// sortare crescatoare dupa "puterea" calculatorului
int cmp_computer(computer a, computer b) {
	return a.p < b.p;
}


// se verifica daca toate calculatoarele pot fi aduse la
// minim cnt folosind o suma pana in bugetul alocat
int ok(computer *v1, int cnt, int budget) {
	unsigned long long int need = 0;
	for(int i = 0; i < n; i++) {
		if(v1[i].p >= cnt)
			break;
		need = need + (cnt-v1[i].p)*v1[i].u;
		if(need > budget)
			return 0;
	}
	return need <= budget;
}



int main() {
	ios_base::sync_with_stdio(false);
	fin >> n >> b;
	computer *v1 = (computer *)malloc(n*sizeof(computer));
	for(int i = 0; i < n; i++) {
		fin >> v1[i].p >> v1[i].u;
	}
	sort(v1, v1+n, cmp_computer);
	unsigned long long int l = 0;
	unsigned long long int r = 1000000000;
	unsigned long long int res = -1;
	unsigned long long int m = -1;
	while(l <= r) {  // cautare binara in spatiul rezultatelor posibile
		m = l + (r - l)/2;
		if(ok(v1, m, b)) {  // daca se pot aduce toate la minim m
			res = m;  // retin rezultatul si incerc sa gasesc unul mai mare
			l = m + 1;
		} else {
			r = m - 1;
		}
	}
	fout << res;

	return 0;
}
