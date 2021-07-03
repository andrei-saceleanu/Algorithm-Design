#include<bits/stdc++.h>

using namespace std;

ifstream fin("poduri.in");
ofstream fout("poduri.out");
// dimensiuni,coordonate start,curente si viitoare
int n, m, x, y, cx, cy, nx, ny;

// verifica daca pozitia (a,b) se afla intre limitele matricei
int inside(int a, int b) {
	return (a >= 0) && (a < n) && (b >= 0) && (b < m);
}



int main() {
	fin >> n >> m;
	fin >> x >> y;
	vector<string> mat;
	fin.get();
	for(int i = 0; i < n; i++) {
		string s;
		getline(fin, s);
		mat.push_back(s);
	}
	queue<pair<int, int>> q;
	int **visited = new int*[n];
	int **dist = new int*[n];
	for(int i = 0; i < n; i++) {
		visited[i] = new int[m];
		dist[i] = new int[m];
		for(int j = 0; j < m; j++) {
			visited[i][j] = 0;
			dist[i][j] = INT_MAX;
		}
	}
	int sx = x-1, sy = y-1;  // valorile citite sunt 1-indexate(se prefera 0)
	int dx[] = {-1, 0, 1, 0};
	int dy[] = {0, 1, 0, -1};
	dist[sx][sy] = 0;
	visited[sx][sy] = 1;
	q.push({sx, sy});  // se viziteaza si se pune in coada startul
	int res = INT_MAX;
	while(!q.empty()) {
		pair<int, int> curr = q.front();
		q.pop();
		cx = curr.first;
		cy = curr.second;

		if(mat[cx][cy] == 'V') {
			if(cx == 0 || cx == n-1) {
				// o celula cu pod vertical este adiacenta cu exteriorul
				// daca se afla pe prima sau ultima linie
				res = fmin(res, 1 + dist[cx][cy]);
			}
			// se proceseaza vecinii pe verticala,valizi si nevizitati
			if(inside(cx-1, cy) && !visited[cx-1][cy]) {
				q.push({cx-1, cy});
				dist[cx-1][cy] = dist[cx][cy]+1;
				visited[cx-1][cy] = 1;
			}
			if(inside(cx+1, cy) && !visited[cx+1][cy]) {
				q.push({cx+1, cy});
				dist[cx+1][cy] = dist[cx][cy]+1;
				visited[cx+1][cy] = 1;
			}
		} else if (mat[cx][cy] == 'O') {
			if(cy == 0 || cy == m-1) {
				// o celula cu pod orizontal este adiacenta cu exteriorul
				// daca se afla pe prima sau ultima coloana
				res = fmin(res, 1 + dist[cx][cy]);
			}
			// se proceseaza vecinii pe orizontala,valizi si nevizitati
			if(inside(cx, cy-1) && !visited[cx][cy-1]) {
				q.push({cx, cy-1});
				dist[cx][cy-1] = dist[cx][cy]+1;
				visited[cx][cy-1] = 1;
			}
			if(inside(cx, cy+1) && !visited[cx][cy+1]) {
				q.push({cx, cy+1});
				dist[cx][cy+1] = dist[cx][cy]+1;
				visited[cx][cy+1] = 1;
			}
		} else if (mat[cx][cy] == 'D') {
			// o celula cu pod dublu este adiacenta cu exteriorul
			// daca se afla pe "bordura"
			if(cx == 0 || cx == n-1 || cy == 0 || cy == m-1) {
				res = fmin(res, 1 + dist[cx][cy]);
			}
			// se proceseaza vecinii ortogonali,valizi si nevizitati
			for(int k = 0; k < 4; k++) {
				nx = cx + dx[k];
				ny = cy + dy[k];
				if(inside(nx, ny) && !visited[nx][ny]) {
					q.push({nx, ny});
					dist[nx][ny] = dist[cx][cy]+1;
					visited[nx][ny] = 1;
				}
			}
		}
	}
	// res ramane INT_MAX doar daca nu se poate iesi din matrice
	// in cazul acesta,se afiseaza -1
	if(res == INT_MAX) {
		fout << -1;
	} else {
		fout << res;
	}
	return 0;
}
