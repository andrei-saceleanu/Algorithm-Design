#include<bits/stdc++.h>

using namespace std;

ifstream fin("adrese.in");
ofstream fout("adrese.out");
int n, k;
vector<int> *adj;
int *visited;


typedef struct{
	string name;
	int no_emails;
	string *emails;
} person;

person *p;
// verifica daca persoanele de index a si b au o adresa de mail comuna
bool common_mail(int a, int b) {
	int s1 = p[a].no_emails;
	int s2 = p[b].no_emails;
	for(int i=0;i<s1;i++){
		for(int j=0;j<s2;j++){
			if(p[a].emails[i]==p[b].emails[j])
				return true;
		}
	}
	return false;
}

bool cmp(person a,person b){
	if(a.no_emails!=b.no_emails){
		return a.no_emails<b.no_emails;
	}
	return a.name<b.name;
}

// parcurgere in adancime a grafului construit
// pentru o parcurgere a unei componente conexe
// s va retine numele unei persoane, minim lexicografic
// iar email_set reuniunea adreselor tuturor persoanelor
// din componenta
void dfs(int curr, string& s, set<string>& email_set) {
	visited[curr] = 1;
	if(p[curr].name < s) {
		s = p[curr].name;
	}
	int m = p[curr].no_emails;
	for(int i=0;i<m;i++){
		email_set.insert(p[curr].emails[i]);
	}
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
	p = new person[n];
	for(int i = 0; i < n; i++) {
		fin>>p[i].name>>p[i].no_emails;
		k = p[i].no_emails;
		p[i].emails = new string[k];
		for(int j = 0; j < k; j++) {
			fin>>p[i].emails[j];
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
	
	vector<person> res;
	for(int i = 0; i < n; i++) {
		if(!visited[i]) {
			cnt++;
			string s = p[i].name;
			set<string> email_set;
			dfs(i, s, email_set);
			person *new_pers = (person *)malloc(sizeof(person));
			char * name = new char[s.length()+1];
			strcpy(name,s.c_str());
			new_pers->name = name;
			new_pers->no_emails = email_set.size();
			new_pers->emails = new string[new_pers->no_emails];
			set<string>::iterator it;
			int j=0;
			for(it=email_set.begin();it!=email_set.end();it++){
				new_pers->emails[j] = *it;
				j++;
			}
			res.push_back(*new_pers);
		}
	}
	fout << cnt << "\n";
	sort(res.begin(), res.end(),cmp);
	for(int i = 0; i < res.size(); i++) {
		fout << res[i].name << " " << res[i].no_emails << "\n";
		for(int j=0;j<res[i].no_emails;j++){
			fout<<res[i].emails[j]<<"\n";
		}
	}
	return 0;
}