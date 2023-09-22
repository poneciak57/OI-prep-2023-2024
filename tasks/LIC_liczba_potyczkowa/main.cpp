#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


bool is_fighting_number(vec<int> &n, ll full) {
    vec<bool> already_checked = vec<bool>(10, false);
    
    for(int t: n) {
        if((already_checked[t] || (t == 1))) {
            already_checked[t] = true;
        } else if (t == 2 && n[0]%2 == 0) {
            already_checked[2] = true;
        } else if (t == 5 && n[0] == 5) {
            already_checked[5] = true;
        } else if (full % t == 0) {
            already_checked[t] = true;
        } else {
            return false;
        }
    }

    return true;
}

vec<int> from_number(ll num) {
    vec<int> liczba;
    
    while(num > 0) {
        liczba.push_back(num%10);
        num /= 10;
    }
    return liczba;
}

int increment(vec<int> &num) {
    int i = 0;
    int inc = 1;
    int mult = 1;
    while(++num[i] == 10) {
        num[i] = 1;
        i++;
        inc+=mult;
        mult*=10;
        if(i == num.size()) {
            num.push_back(0);
        }
    }
    return inc;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll from, to;
    std::cin>>from>>to;

    vec<int> liczba = from_number(from);
    ll full = from;
    ll count = 0;

    while(full < to) {
        count += is_fighting_number(liczba, full);
        full += increment(liczba);
    }
    
    std::cout<<count;
    std::cout.flush();
}