#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
typedef pair<ll,ll> llp;
template <typename T> using vec = vector<T>;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// #define NWD std::gcd;
	const int LIM = 1e3;
	int liczby[LIM];

	int max_c = 0; // dlugosc maksymalnego podciagu gdzie NWD > 1
	int max_c_ind = -1; // indeks poczatku tego ciagu
	int max_c_nwd = -1; // nwd tego ciagu

	for(int i = 0; i < LIM; i++) {
		// ustalamy poczatkowe nwd ciagu
		int nwd = liczby[i];
		int jmem = 0; // maksymalny j dla ktorego nwd bylo > 1
		for(int j = i; j < LIM; j++) {
			nwd = gcd(nwd, liczby[i]); // obliczamy nwd spojnego pocviagu [i, j]
			if(nwd == 1) break; // jesli nwd spadnie do 1 konczymy petle poniewaz to nwd juz do konca bedzie rowne 1
			jmem = j; // aktualizujemy najwieksze j dla ktorego nwd > 1
		}
		
		// sprawdzamy czy najdluzszy podciag zaczynajacy sie w i spelniajacy warunek NWD > 1 
		// jest dluzszy od obecnie najdluzszego
		if(jmem - i > max_c) {
			max_c = jmem - i;
			max_c_ind = i;
			max_c_nwd = nwd;
		}
	}

	// wypisujemy dane
	cout<<"count: "<<max_c<<"\n";
	cout<<"nwd: "<<max_c_nwd<<"\n";
	cout<<"ind: "<<max_c_ind<<"\n";
	cout<<"nums: ";
	for(int i = max_c_ind; i < max_c_ind + max_c; i++) cout<<liczby[i]<<" ";
	
	
	cout.flush();
	return 0;
}