#include <bits/stdc++.h>

using namespace std;

struct point
{
    int id;
    double x;
    double y;
};

double distance(point a, point b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

vector<point> p, q;

fstream fout;

double m, c;    // slope and constant in y = mx + c

bool comparepoint(point p1, point p2)
{
    double p1_x = (p1.x + m * p1.y) / sqrt(m * m + 1);
    double p1_y = (p1.y - m * p1.x) / sqrt(m * m + 1);

    double p2_x = (p2.x + m * p2.y) / sqrt(m * m + 1);
    double p2_y = (p2.y - m * p2.x) / sqrt(m * m + 1);

    if(p1_x == p2_x) {
        return (p1_y < p2_y);
    }
    else {
        return (p1_x < p2_x);
    }
}

int PMS(vector<vector<int>> &a)
{
    int n = p.size(), m = q.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    // dp[i][j] is max value of sets till p[i], q[j]

    vector<pair<int, int>> res;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1][j - 1] == 1) {
                
                if (!res.empty()) {
                    if (a[res.back().first][j - 1] != 1 && a[i - 1][res.back().second] != 1) {
                        dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + 1});
                        
                        if (dp[i][j] != dp[i][j - 1] && dp[i][j] != dp[i - 1][j]) {
                           res.push_back({i - 1, j - 1});
                        }
                    }
                } else {
                    dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + 1});
                    if (dp[i][j] != dp[i][j - 1] && dp[i][j] != dp[i - 1][j]) {
                        res.push_back({i - 1, j - 1});
                    }
                }
            }
            else {
                dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         // cout << dp[i][j] << " ";
    //         if (dp[i][j] != dp[i][j - 1] && dp[i][j] != dp[i - 1][j]) {
    //             res.push_back({i - 1, j - 1});
    //         }
    //     }
    //     // cout << "\n";
    // }

    // fout << "Points in the Perfectly Matched Sets are \n";
    for (auto i : res) {
        fout << p[i.first].x << " " << p[i.first].y << " ";
        fout << q[i.second].x << " " << q[i.second].y << "\n";
    }
    // fout << "\n\n\n";
    // for (auto i : res) {
    //     fout << p[i.first].x << ", ";
    // }

    // fout << "\n\n\n";
    // for (auto i : res) {
    //     fout << p[i.first].y << ", ";
    // }

    // fout << "\n\n\n";
    // for (auto i : res) {
    //     fout << q[i.second].x << ", ";
    // }

    // fout << "\n\n\n";
    // for (auto i : res) {
    //     fout << q[i.second].y << ", ";
    // }
    return dp[n][m];
}

vector<vector<int>> ConstructAdjacencyMatrix()
{
    vector<vector<int>> a(p.size(), (vector<int>(q.size(), 0)));
    for (int i = 0; i < p.size(); ++i) {
        for (int j = 0; j < q.size(); ++j) {
            if (distance(p[i], q[j]) <= 4.0){
                a[i][j] = 1;
            } else a[i][j] = 0;
        }
    }
    return a;
}

int main()
{
    int n, m;   // number of vertices on both sides
    ifstream fin;
    fin.open("input.csv");
    
    fin >> n;
    
    for (int i = 1; i <= n; ++i)
    {
        point Point;
        Point.id = i;
        string comma;
        fin >> Point.x >> comma >> Point.y;
        p.push_back(Point);
    }

    fin >> m;

    for (int i = 1; i <= m; ++i)
    {
        point Point;
        Point.id = i;
        string comma;
        fin >> Point.x >> comma >> Point.y;
        q.push_back(Point);
    }

    // taking the slope of equation of line seperating these set of two points
    // eqn ==> y = mx + c , m is slope

    // double m, c;

    // fin >> m >> c;

    sort(p.begin(), p.end(), comparepoint);
    sort(q.begin(), q.end(), comparepoint);

    vector<vector<int>> matrix = ConstructAdjacencyMatrix();

    fout.open("output.txt");

    cout << "Max number of matching is " << PMS(matrix) << "\n";
}