#include<bits/stdc++.h>

using namespace std;

ifstream fin("lego.in");
ofstream fout("lego.out");
int k, n, t, s;
// vector folosit la generarea solutiei
// in solutie se doreste sa nu existe duplicate
int *used;
// solutie partiala,coeficienti de inmultire,solutie finala
vector<int> sol, coeffs, res;
// multimea variantelor de coeficienti
vector<vector<int>> c;
int max_len;

// conditie pentru solutie partiala
// se va abandona forma curenta a solutiei daca nu este strict crescatoare
int increasing(int p) {
	if(p >= 1) {
		return sol[p] > sol[p-1];
	}
	return 1;
}

// generare moduri de combinare ale pieselor
// se obtin vectori de n coeficienti,a caror suma
// este nenula(trebuie folosita macar o piesa) si mai mica decat t
// (se pot folosi maxim t piese,inclusiv)
void bkt_coeffs() {
	for(int i = 0; i <= t; i++) {
		coeffs.push_back(i);
		s += i;
		if(s <= t && coeffs.size() <= n) {
			if(s <= t && s > 0 && coeffs.size() == n) {
				c.push_back(coeffs);
			} else {
				bkt_coeffs();
			}
		}
		s -= i;
		coeffs.pop_back();
	}
}

// pentru un set de dimensiuni al pieselor,se genereaza
// un vector binar (nums[i] = 0 daca i nu poate fi obtinut
// din setul curent si folosind oricare din vectorii de coeficienti
// si 1 ,in caz contrar)
// pe acest vector,se face o traversare liniara si se retine lungimea
// celei mai lungi subsecvente de 1
// rezultatul final se actualizeaza daca lungimea maxima gasita
// este mai mare decat maximul global identificat pana in acel moment
void check() {
	int x;
	int *nums = (int *)calloc(t * k + 1, sizeof(int));
	for(int i = 0; i < c.size(); i++) {
		x = 0;
		for(int j = 0; j < n; j++) {
			x += sol[j] * c[i][j];
		}
		nums[x] = 1;
	}
	int mx_len = 0, len;
	int i = 1;
	while(i <= t * k) {
		if(nums[i] == 0) {
			i++;
		} else {
			len = 0;
			while(i <= t * k && nums[i] == 1) {
				len++;
				i++;
			}
			mx_len = fmax(mx_len, len);
		}
	}
	if(mx_len > max_len) {
		max_len = mx_len;
		res = sol;
	}
}


// generare set de dimensiuni pentru piese
// se pleaca de la 2 deoarece 1 este deja inclus
// pentru a limita solutiile generate,se pun
// conditiile de unicitate ale elementelor
// (cu ajutorul vectorului used) si de monotonie
// (nu are sens sa se analizeze atat 1 4 5,cat si 1 5 4,de exemplu)
void bkt(int p) {
	for(int i = 2; i <= k; i++) {
		if(!used[i]) {
			sol.push_back(i);
			used[i] = 1;
			if(increasing(p)) {
				if(p == n-1) {
					check();
				} else {
					bkt(p + 1);
				}
			}
			used[i] = 0;
			sol.pop_back();
		}
	}
}

int main() {
	fin >> k >> n >> t;
	sol.push_back(1);  // includere obligatorie a lui 1 in solutie
	used = (int *)calloc(k + 1, sizeof(int));
	used[1] = 1;
	bkt_coeffs();
	bkt(1);
	fout << max_len << "\n";
	for(int i = 0; i < res.size(); i++) {
		fout << res[i] << " ";
	}
	return 0;
}
