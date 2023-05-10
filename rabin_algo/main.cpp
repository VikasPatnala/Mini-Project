#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> pdd;

double dist(pdd a, pdd b)
{
    return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

ofstream fout;
double rabin_algo(vector<pdd> &pts) {
    // Select sqrt(n) random points from pts;
    int n = ceil(sqrt(pts.size()));

    random_device rd;
    mt19937 g(rd()); // random number generator

    shuffle(pts.begin(), pts.end(), g);

    vector<pdd> rand_pts(pts.begin(), pts.begin() + n);

    // rand_pts is sqrt(n) random points from the given array

    // Finding the closest pair in the rand_pts;

    double min_dist = 1000000;
    pdd p1, p2;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double distance = dist(rand_pts[i], rand_pts[j]);
            if (min_dist > distance) {
                min_dist = distance;
                p1 = rand_pts[i];
                p2 = rand_pts[j];
            }
        }
    }

    // cout << min_dist << "\n";
    // cout << p1.first << " " << p1.second << "\n";
    // cout << p2.first << " " << p2.second << "\n";

    map<pdd, vector<pdd>> hash_table;

    for (auto i : pts) {
        pdd pt;
        pt.first = floor(i.first / min_dist);
        pt.second = floor(i.second / min_dist);
        hash_table[pt].push_back(i);
    }

    // int count = 0;
    // cout << min_dist << "\n";
    // for (auto i : hash_table) {
    //     // count += i.second.size();
    //     cout << i.first.first << " " << i.first.second << "\n";
    // }

    double res = min_dist;
    for (auto i : hash_table) {
        vector<pdd> v = i.second;

        for (int j = 0; j < v.size(); ++j) {
            for (int k = j + 1; k < v.size(); ++k) {
                double distance = dist(v[j], v[k]);
                if (res > distance) {
                    res = distance;
                    p1 = v[j];
                    p2 = v[k];
                    // cout << "1\n";
                    // cout << p1.first << " " << p1.second << "\n";
                    // cout << p2.first << " " << p2.second << "\n";
                }
            }
        }

        pdd pt = i.first;
        pt.first--;

        if (hash_table.find(pt) != hash_table.end()) {
            vector<pdd> v1 = hash_table[pt];

            for (int j = 0; j < v1.size(); ++j) {
                for (int k = 0; k < v.size(); ++k) {
                    double distance = dist(v1[j], v[k]);
                    if (res > distance) {
                        res = distance;
                        p1 = v1[j];
                        p2 = v[k];
                        // cout << "2\n";
                        // cout << p1.first << " " << p1.second << "\n";
                        // cout << p2.first << " " << p2.second << "\n";
                    }
                }
            }
        }

        pt.first += 2;

        if (hash_table.find(pt) != hash_table.end()) {
            vector<pdd> v1 = hash_table[pt];

            for (int j = 0; j < v1.size(); ++j) {
                for (int k = 0; k < v.size(); ++k) {
                    double distance = dist(v1[j], v[k]);
                    if (res > distance) {
                        res = distance;
                        p1 = v1[j];
                        p2 = v[k];
                        // cout << "3\n";
                        // cout << p1.first << " " << p1.second << "\n";
                        // cout << p2.first << " " << p2.second << "\n";
                    }
                }
            }
        }

        pt.first--;
        pt.second--;

        if (hash_table.find(pt) != hash_table.end()) {
            vector<pdd> v1 = hash_table[pt];

            for (int j = 0; j < v1.size(); ++j) {
                for (int k = 0; k < v.size(); ++k) {
                    double distance = dist(v1[j], v[k]);
                    if (res > distance) {
                        res = distance;
                        p1 = v1[j];
                        p2 = v[k];
                        // cout << "4\n";
                        // cout << p1.first << " " << p1.second << "\n";
                        // cout << p2.first << " " << p2.second << "\n";
                    }
                }
            }
        }

        pt.second += 2;

        if (hash_table.find(pt) != hash_table.end()) {
            vector<pdd> v1 = hash_table[pt];

            for (int j = 0; j < v1.size(); ++j) {
                for (int k = 0; k < v.size(); ++k) {
                    double distance = dist(v1[j], v[k]);
                    if (res > distance) {
                        res = distance;
                        p1 = v1[j];
                        p2 = v[k];
                        // cout << "5\n";
                        // cout << p1.first << " " << p1.second << "\n";
                        // cout << p2.first << " " << p2.second << "\n";
                    }
                }
            }
        }
        
        pt.second--;

    }

    cout << p1.first << " " << p1.second << "\n";
    cout << p2.first << " " << p2.second << "\n";

    fout << p1.first << " " << p2.first << "\n";
    fout << p1.second << " " << p2.second << "\n";

    return res;
}

int main()
{
    // Input from the file
    fstream fin;
    fin.open("input.csv");
    int n;  // number of points
    fin >> n;

    vector<pdd> p(n);
    
    for (int i = 0; i < n; ++i) {
        int a, b;
        char s;
        fin >> a >> s >> b;
        p[i].first = a;
        p[i].second = b;
    }

    fout.open("output.txt");
    cout << rabin_algo(p) << "\n";
}