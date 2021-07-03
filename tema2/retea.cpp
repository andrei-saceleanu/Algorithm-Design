#include<bits/stdc++.h>

using namespace std;

ifstream fin("retea.in");
ofstream fout("retea.out");

int n, m, x, y, k;
vector<int> *adj;
int *visited;

// parcurgere in adancime ,considerand deconectat nodul "ignore"
void dfs(int curr, int ignore) {
	visited[curr] = ignore;
	k++;
	if(curr == ignore)
		return;
	for(int i = 0; i < adj[curr].size(); i++) {
		if(adj[curr][i] != ignore && visited[adj[curr][i]] == ignore - 1)
			dfs(adj[curr][i], ignore);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	fin.tie(0);
	fout.tie(0);
	// citire si constructie graf al retelei
	fin >> n >> m;
	adj = new vector<int>[n + 1];
	for(int i = 0; i < m; i++) {
		fin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	visited = (int *)calloc(n + 1, sizeof(int));
	int cnt;
	// pentru fiecare nod,se simuleaza deconectarea lui
	// si se realizeaza cate o parcurgere in adancime completa
	// pentru fiecare componenta conexa,se identifica dimensiunea
	// si se scade patratul acesteia din n*n(vezi README pentru detalii)
	// la fiecare nod i,o valoare in visited de i-1 inseamna ca
	// nodul nu a fost vizitat la pasul curent(a fost vizitat doar pana
	// la simularea anterioara)
	for(int i = 1; i <= n; i++) {
		cnt = n * n;
		for(int j = 1; j <= n; j++) {
			if(visited[j] == i - 1) {
				k = 0;
				dfs(j, i);
				cnt -= k * k;
			}
		}
		fout << cnt << "\n";
	}
	return 0;
}
