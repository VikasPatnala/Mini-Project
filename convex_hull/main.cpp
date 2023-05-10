#include<bits/stdc++.h>
using namespace std;

struct point
{
    int id;
    double x_cor;
    double y_cor;
};

bool comparepoint(point p1, point p2)
{
    if(p1.x_cor == p2.x_cor) {
        return (p1.y_cor < p2.y_cor);
    }
    else {
        return (p1.x_cor < p2.x_cor);
    }
}

int compareside(point p1, point p2, point p3){
    double slope = ((p2.y_cor - p1.y_cor) / (p2.x_cor - p1.x_cor));
    double check = (p1.y_cor + slope * (p3.x_cor - p1.x_cor));
    
    if(p3.y_cor - check > 0) {
        return 1;
    }
    else if(p3.y_cor - check == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

bool compareturn(point p1, point p2, point p3)
{
    double check = ((p2.x_cor - p1.x_cor) * (p3.y_cor - p2.y_cor) 
                        - (p3.x_cor - p2.x_cor) * (p2.y_cor - p1.y_cor));
    if(check < 0) {
        return true;
    }
    else {
        return false;
    }
}

void print_point(point Point)
{
    cout << "(" << Point.x_cor << ", " << Point.y_cor << ") ";
}

void print_hull(string Context, vector<point> &points)
{
    cout << Context << "Convex Hull Formed by the points in Sequence are : ";
    for(auto i : points) {
        print_point(i);
    }
    cout << "\n";
}

int main()
{
    int num_of_points;
    ifstream fin;

    fin.open("input.csv");
    fin >> num_of_points;
    
    vector<point> vec_of_points;

    for(int i = 1; i <= num_of_points; ++i) {
        point Point;
        Point.id = i;
        string comma;
        fin >> Point.x_cor >> comma >> Point.y_cor;
        vec_of_points.push_back(Point);
    }
    
    sort(vec_of_points.begin(), vec_of_points.end(), comparepoint);
    
    point low_left = vec_of_points[0];
    point high_right = vec_of_points[num_of_points-1];
    
    // print_point(low_left);
    // print_point(high_right);

    // checking whether the given points lie on a same vertical line
    if(low_left.x_cor == high_right.x_cor) {
        vec_of_points.erase(vec_of_points.begin() + 1, vec_of_points.end() - 1);
        print_hull("", vec_of_points);
        return 0;
    }

    vector<point> upper_hull_points;
    vector<point> lower_hull_points;

    // dividing points into two groups Upper hull and Lower hull
    for(int i = 1; i < num_of_points - 1; i++) {
        int check = compareside(low_left, high_right, vec_of_points[i]);
        if(check == 1){
            upper_hull_points.push_back(vec_of_points[i]);
        }
        else if(check == -1){
            lower_hull_points.push_back(vec_of_points[i]);
        }
    }
    upper_hull_points.push_back(high_right);
    // print_hull(upper_hull_points);
    // print_hull(lower_hull_points);
    
    // Upper Hull Points
    vector<point> upper_hull;
    upper_hull.push_back(low_left);
    int i = 0;
    
    while(upper_hull.back().id != high_right.id) {
        if(upper_hull.size() < 2) {
            upper_hull.push_back(upper_hull_points[i++]);
        }
        else {
            point p2 = upper_hull.back();
            upper_hull.pop_back();
            point p1 = upper_hull.back();
            if(compareturn(p1, p2, upper_hull_points[i])) {
                upper_hull.push_back(p2);
                upper_hull.push_back(upper_hull_points[i++]);
            }
        }
    }
    print_hull("Upper ", upper_hull);
    
    // Lower Hull Points
    vector<point> lower_hull;
    reverse(lower_hull_points.begin(), lower_hull_points.end());
    lower_hull_points.push_back(low_left);
    lower_hull.push_back(high_right);
    i = 0;
    
    while(lower_hull.back().id != low_left.id) {
        if(lower_hull.size() < 2) {
            lower_hull.push_back(lower_hull_points[i++]);
        }
        else {
            point p2 = lower_hull.back();
            lower_hull.pop_back();
            point p1 = lower_hull.back();
            if(compareturn(p1, p2, lower_hull_points[i])) {
                lower_hull.push_back(p2);
                lower_hull.push_back(lower_hull_points[i++]);
            }
        }
    }
    print_hull("Lower ", lower_hull);

    vector<point> convex_hull;
    convex_hull.insert(convex_hull.end(), upper_hull.begin(), upper_hull.end());
    convex_hull.insert(convex_hull.end(), lower_hull.begin() + 1, lower_hull.end() - 1);

    print_hull("", convex_hull);

    ofstream fout;
    fout.open("output.txt");
    fout << low_left.x_cor << " " << low_left.y_cor << "\n";
    fout << high_right.x_cor << " " << high_right.y_cor << "\n";

    for (auto i : convex_hull) {
        fout << i.x_cor << ", " << i.y_cor << "\n";
    }

    return 0;
}