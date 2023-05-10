#include <bits/stdc++.h>

using namespace std;

double rand_generator(double range_min, double range_max)
{
    const long max_rand = 1000000L;

    double random_double = range_min + (range_max - range_min) * (rand() % max_rand) / max_rand;

    return random_double;
}

int main()
{
    double range_min = 100;
    double range_max = 900;

    ofstream file;
    file.open("./tests/test4.txt");
    
    srand(time(NULL));
    set<double> values;
    file << 100 << "\n";
    for (int i = 0; i < 100; ++i) {
        double v1 = rand_generator(range_min, range_max);
        while(values.find(v1) != values.end()) {
            v1 = rand_generator(range_min, range_max);
        }
        values.insert(v1);
        double v2 = rand_generator(range_min, range_max);
        while(values.find(v2) != values.end()) {
            v2 = rand_generator(range_min, range_max);
        }
        values.insert(v2);
        double v3 = rand_generator(range_min, range_max);
        while(values.find(v3) != values.end()) {
            v3 = rand_generator(range_min, range_max);
        }
        values.insert(v3);
        double v4 = rand_generator(range_min, range_max);
        while(values.find(v4) != values.end()) {
            v4 = rand_generator(range_min, range_max);
        }
        values.insert(v4);
        file << v1 << " " << v2 << " " << v3 << " " << v4 << "\n";
    }
}