#include <bits/stdc++.h>

using namespace std;

int main()
{
    fstream file;
    file.open("input1.csv");
    file << 20 << "\n";
    
    set<int> s1, s2;
    
    for(int i = 0; i < 20; ++i)
    {
        int a = rand() % 100;
        int b = rand() % 100;
        if(s1.find(a) == s1.end() && s2.find(b) == s2.end()) {
            file << a << ", " << b << "\n";
            s1.insert(a);
            s2.insert(b);
        }
        else {
            i--;
        }
    }
}