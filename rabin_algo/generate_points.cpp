#include <bits/stdc++.h>

using namespace std;

int main()
{
    fstream file;
    file.open("input.csv");
    set<pair<int, int>> s;
    vector<pair<int, int>> v;
    srand(time(NULL));
    for(int i = 0; i < 100; ++i)
    {
        int x = rand() % 1000;
        int y = rand() % 1000;
        if (s.find({x, y}) == s.end()) {
            s.insert({x, y});
            v.push_back({x, y});
        }
    }
    file << v.size() << "\n";

    for(int i = 0; i < v.size(); ++i) {
        file << v[i].first << ", " << v[i].second << "\n";
    }

//     for(int i = 0; i < v.size(); ++i) {
//         file << v[i].first << ", ";
//     }
//     file << "\n";
//     for(int i = 0; i < v.size(); ++i) {
//         file << v[i].second << ", ";
//     }
}