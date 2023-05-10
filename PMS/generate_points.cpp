#include <bits/stdc++.h>

using namespace std;

int main()
{
    fstream file;
    file.open("input.csv");
    srand(time(NULL));
    set<pair<int, int>> above;
    set<pair<int, int>> below;
    // abovey y = 8
    // mid line y = 4
    // below y = 0
    // x is inbetween [0, 50)
    for (int i = 0; i < 50; ++i) {
        int x = rand() % 50;
        int y = rand() % 4;
        if(below.find({x, y}) == below.end()) {
            below.insert({x, y});
        };
    }
    for (int i = 0; i < 50; ++i) {
        int x = rand() % 50;
        int y = rand() % 4;
        if(above.find({x, y + 5}) == above.end()) {
            above.insert({x, y + 5});
        };
    }
    file << above.size() << "\n";
    for (auto i : above) {
        file << i.first << ", " << i.second << "\n";
    }
    file << below.size() << "\n";
    for (auto i : below) {
        file << i.first << ", " << i.second << "\n";
    }
    // file << "\n\n\n";
    // for (auto i : above) {
    //     file << i.first << ", ";
    // }
    // file << "\n\n\n";
    // for (auto i : above) {
    //     file << i.second << ", ";
    // }
    // file << "\n\n\n";
    // for (auto i : below) {
    //     file << i.first << ", ";
    // }
    // file << "\n\n\n";
    // for (auto i : below) {
    //     file << i.second << ", ";
    // }
}