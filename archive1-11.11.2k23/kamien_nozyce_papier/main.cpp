#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    std::map<str, str> map = {
        {"PAPIER PAPIER", "REMIS"},
        {"NOZYCE NOZYCE", "REMIS"},
        {"KAMIEN KAMIEN", "REMIS"},
        {"PAPIER KAMIEN", "BITOLINA"},
        {"KAMIEN NOZYCE", "BITOLINA"},
        {"NOZYCE PAPIER", "BITOLINA"},
        {"KAMIEN PAPIER", "BITEK"},
        {"NOZYCE KAMIEN", "BITEK"},
        {"PAPIER NOZYCE", "BITEK"}
    };

    str bitolina, bitek;
    std::cin>>bitolina>>bitek;
    std::cout<<map[bitolina+" "+bitek];


    std::cout.flush();
}
