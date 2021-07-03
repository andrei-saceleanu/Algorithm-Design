#include<bits/stdc++.h>

using namespace std;

ifstream fin("adrese.in");
ofstream fout("adrese.out");
int n,k;
int *parent;

vector<string> names;
unordered_map<int,set<string>> emails;

int find(int i){
	if(parent[i]!=i)
		parent[i] =find(parent[i]);
	return parent[i];
}

void uni(int i,int j){
	int x = find(i);
	int y = find(j);
	if(names[x]<names[y]){
		parent[y] = x;
		emails[x].insert(emails[y].begin(),emails[y].end());
	}else{
		parent[x] = y;
		emails[y].insert(emails[x].begin(),emails[x].end());
	}
}

bool common_mail(int a,int b){
	set<string> x = emails[a];
	set<string> y = emails[b];
	set<string>::iterator it;
	for(it=x.begin();it!=x.end();it++){
		if(y.find(*it)!=y.end())
			return true;
	}
	return false;
}

int main(){
	fin>>n;
	fin.get();
	parent = new int[n];
	for(int i=0;i<n;i++){
		parent[i] = i;
		string s;
		fin>>s>>k;
		fin.get();
		names.push_back(s);
		for(int j=0;j<k;j++){
			string mail;
			getline(fin,mail);
			emails[i].insert(mail);
		}
	}
	
	for(int i=0;i<n;i++){
		for(int j = i+1;j<n;j++){
			if(common_mail(i,j)){
				uni(i,j);
			}
		}
	}
	int cnt = 0;
	for(int i=0;i<n;i++){
		if(parent[i]==i){
			cnt++;
		}
	}
	fout<<cnt<<"\n";
	set<string>::iterator it;
	vector<pair<int,pair<string,int>>> v;
	for(int i=0;i<n;i++){
		if(parent[i]==i){
			v.push_back({emails[i].size(),{names[i],i}});
		}
	}
	sort(v.begin(),v.end());
	int ind = -1;
	for(int i=0;i<v.size();i++){
		ind = v[i].second.second;
		fout<<v[i].second.first<<" "<<v[i].first<<"\n";
		for(it=emails[ind].begin();it!=emails[ind].end();it++){
			fout<<*it<<"\n";
		} 
	}

	return 0;
}