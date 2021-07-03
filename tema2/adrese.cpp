#include<bits/stdc++.h>

using namespace std;

ifstream fin("adrese.in");
ofstream fout("adrese.out");
int n, k;
vector<int> *adj;
int *visited;
// numele persoanelor
vector<string> names;
// mapare intre index din vectorul de nume si setul de adrese
// maparea se realizeaza dupa index deoarece pot exista
// 2 persoane cu acelasi nume
unordered_map<int, set<string>> emails;

// verifica daca persoanele de index a si b au o adresa de mail comuna
bool common_mail(int a, int b) {
	set<string> x = emails[a];
	set<string> y = emails[b];
	set<string>::iterator it1 = x.begin();
	set<string>::iterator it2 = y.begin();
	while(it1 != x.end()&&it2 != y.end()) {
		if(*it1 < *it2) {
			++it1;
		} else if (*it2 < *it1) {
			++it2;
		} else {
			return true;
		}
	}
	return false;
}

// parcurgere in adancime a grafului construit
// pentru o parcurgere a unei componente conexe
// s va retine numele unei persoane, minim lexicografic
// iar email_set reuniunea adreselor tuturor persoanelor
// din componenta
void dfs(int curr, string& s, set<string>& email_set) {
	visited[curr] = 1;
	if(names[curr] < s) {
		s = names[curr];
	}
	set<string> x = emails[curr];
	email_set.insert(x.begin(), x.end());
	for(int i = 0; i < adj[curr].size(); i++) {
		if(!visited[adj[curr][i]]) {
			dfs(adj[curr][i], s, email_set);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	fin.tie(0);
	fout.tie(0);
	fin >> n;
	fin.get();
	for(int i = 0; i < n; i++) {
		string s;
		fin >> s >> k;
		fin.get();
		names.push_back(s);
		for(int j = 0; j < k; j++) {
			string mail;
			getline(fin, mail);
			emails[i].insert(mail);
		}
	}
	adj = new vector<int>[n];
	// construire graf
	// 2 persoane sunt unite de muchie daca au cel putin
	// o adresa comuna
	for(int i = 0; i < n-1; i++) {
		for(int j = i+1; j < n; j++) {
			if(common_mail(i, j)) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}
	visited = (int *)calloc(n, sizeof(int));
	int cnt = 0;
	// res retine rezultatul pentru fiecare componenta conexa/persoana finala
	// un element din res este de forma
	// {dimensiune set de adrese,{nume persoana,set de adrese}}
	// aceasta forma a fost aleasa pentru a facilita afisarea in ordinea
	// ceruta(dupa numar de adrese,apoi lexicografic dupa nume)
	vector<pair<int, pair<string, set<string>>>> res;
	for(int i = 0; i < n; i++) {
		if(!visited[i]) {
			cnt++;
			string s = names[i];
			set<string> email_set;
			dfs(i, s, email_set);
			res.push_back({email_set.size(), {s, email_set}});
		}
	}
	fout << cnt << "\n";
	sort(res.begin(), res.end());
	set<string>::iterator it;
	for(int i = 0; i < res.size(); i++) {
		fout << res[i].second.first << " " << res[i].first << "\n";
		it = res[i].second.second.begin();
		for(; it !=res[i].second.second.end(); it++) {
			fout << *it << "\n";
		}
	}
	return 0;
}
