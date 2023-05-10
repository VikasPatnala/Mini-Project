#include <bits/stdc++.h>

using namespace std;

int main()
{
    fstream file;
    file.open("input.csv");
    file << 100 << "\n";
    for(int i = 0; i < 100; ++i)
    {
        file << rand() % 100 << ", " << rand() % 100 << "\n";
    }
}