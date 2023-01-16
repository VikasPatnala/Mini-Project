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
    if(p1.x_cor == p2.x_cor){
        return (p1.y_cor < p2.y_cor);
    }
    else{
        return (p1.x_cor < p2.x_cor);
    }
}

int compareside(point p1, point p2, point p3){
    double slope = ((p2.y_cor - p1.y_cor)/(p2.x_cor - p1.x_cor));
    double check = (p1.y_cor + (slope*(p3.x_cor - p1.x_cor)));
    if(p3.y_cor - check > 0){
        return 1;
    }
    else if(p3.y_cor  - check == 0){
        return 0;
    }
    else{
        return -1;
    }
}

bool compareturn(point p1, point p2, point p3)
{
    double check = ((p2.x_cor-p1.x_cor) * (p3.y_cor-p2.y_cor) - (p3.x_cor-p2.x_cor) * (p2.y_cor-p1.y_cor));
    if(check<=0){
        return true;
    }
    else{
        return false;
    }
}

int main()
{
    int num_of_points;
    ifstream fin;
    string str;
    fin.open("input.csv");
    getline(fin, str);
    num_of_points = stod(str);
    vector<point> vec_of_points;
    int id = 1;
    while(getline(fin, str))
    {
        stringstream ss(str);
        point Point;
        Point.id = id++;
        string coor;
        ss>>coor;
        Point.x_cor = stod(coor);
        ss>>coor;
        Point.y_cor = stod(coor);
        vec_of_points.push_back(Point);
    }
    
    sort(vec_of_points.begin(),vec_of_points.end(),comparepoint);
    point low_left = vec_of_points[0];
    point high_right = vec_of_points[num_of_points-1];
    if(vec_of_points[0].x_cor == vec_of_points[num_of_points-1].x_cor){
        /* return just the first and last points */
    }
    vector<point> upper_hull_points;
    vector<point> lower_hull_points;
    for(int i=1;i<num_of_points-1;i++){
        int check = compareside(low_left,high_right,vec_of_points[i]);
        if(check==1){
            upper_hull_points.push_back(vec_of_points[i]);
        }
        else if(check==-1){
            lower_hull_points.push_back(vec_of_points[i]);
        }
    }
    
    stack<point> upper_hull;
    upper_hull.push(low_left);
    int i = 0;
    while(upper_hull.top().id != high_right.id)
    {
        if(upper_hull.size() < 2){
            upper_hull.push(upper_hull_points[i]);
            i++;
        }
        else{

        }
    }
    

    for(int i=0;i<num_of_points;i++){
        cout<<vec_of_points[i].id<<"-"<<vec_of_points[i].x_cor<<"-"<<vec_of_points[i].y_cor<<endl;
    }
    return 0;
}