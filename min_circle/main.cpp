#include <bits/stdc++.h>
using namespace std;

#define ld long double

struct point
{
    int id;
    ld x_cor;
    ld y_cor;
};

struct circle
{
    point centre;
    ld radius;
    bool Is_inside(point p)
    {
        ld dist = (p.x_cor - centre.x_cor) * (p.x_cor - centre.x_cor) + 
                    (p.y_cor - centre.y_cor) * (p.y_cor - centre.y_cor);
        if ((radius * radius >= (dist) - 1e-9))
        {
            return 1;
        }
        return 0;
    }
};

ld Dist_Two_Points(point p1, point p2)
{
    ld dist = pow((p1.x_cor - p2.x_cor), 2) + pow((p1.y_cor - p2.y_cor), 2);
    dist = sqrt(dist);
    return dist;
}

point Intersection_of_Lines(ld x1, ld x2, ld y1, ld y2, ld s1, ld s2)
{
    point res;
    res.x_cor = ((y2 - y1) + s1 * x1 - s2 * x2) / (s1 - s2);
    res.y_cor = ((s1 * (y2 - y1 + s2 * (x1 - x2))) / (s1 - s2)) + y1;
    return res;
}

circle CircumCircle(point p1, point p2, point p3)
{
    ld x1 = (p1.x_cor + p2.x_cor) / 2;
    ld x2 = (p1.x_cor + p3.x_cor) / 2;
    ld y1 = (p1.y_cor + p2.y_cor) / 2;
    ld y2 = (p1.y_cor + p3.y_cor) / 2;

    if(p2.y_cor == p1.y_cor)
    {
        circle res;
        point center;
        center.x_cor = (p1.x_cor + p2.x_cor) / 2;
        center.y_cor = (p1.y_cor + p3.y_cor) / 2 + ((p1.x_cor - p3.x_cor) * 
                            (center.x_cor - ((p1.x_cor + p3.x_cor) / 2))) / (p3.y_cor - p1.y_cor);
        res.centre = center;
        res.radius = Dist_Two_Points(center, p1);
        return res;
    }
    if(p3.y_cor == p1.y_cor)
    {
        circle res;
        point center;
        center.x_cor = (p1.x_cor + p3.x_cor) / 2;
        center.y_cor = (p1.y_cor + p2.y_cor) / 2 + ((p1.x_cor - p2.x_cor) * 
                            (center.x_cor - ((p1.x_cor + p2.x_cor) / 2))) / (p2.y_cor - p1.y_cor);
        res.centre = center;
        res.radius = Dist_Two_Points(center, p1);
        return res;
    }

    ld s1 = (p1.x_cor - p2.x_cor) / (p2.y_cor - p1.y_cor);
    ld s2 = (p1.x_cor - p3.x_cor) / (p3.y_cor - p1.y_cor);

    circle res;
    res.centre = Intersection_of_Lines(x1, x2, y1, y2, s1, s2);
    res.radius = Dist_Two_Points(res.centre, p1);
    return res;
}

circle Circle_of_Diameter(point p1, point p2)
{
    circle ret_Circle;
    ld dist = Dist_Two_Points(p1, p2);
    ret_Circle.radius = dist / 2;
    ret_Circle.centre.x_cor = (p1.x_cor + p2.x_cor) / 2;
    ret_Circle.centre.y_cor = (p1.y_cor + p2.y_cor) / 2;
    return ret_Circle;
}

bool isValid(vector<point> p, circle c)
{
    for(auto i : p)
    {
        if(!c.Is_inside(i))
        {
            return false;
        }
    }
    return true;
}

circle min_cir(vector<point> &Points, vector<point> On_circle_points, vector<point> Original_points)
{
    if (Points.size() == 0 || On_circle_points.size() == 3)
    {
        circle ret_Circle;
        if (On_circle_points.size() == 0)
        {
            ret_Circle.centre.x_cor = 0;
            ret_Circle.centre.y_cor = 0;
            ret_Circle.radius = 0;
        }
        else if (On_circle_points.size() == 1)
        {
            ret_Circle.centre = On_circle_points[0];
            ret_Circle.radius = 0;
        }
        else if (On_circle_points.size() == 2)
        {
            ret_Circle = Circle_of_Diameter(On_circle_points[0], On_circle_points[1]);
        }
        else if (On_circle_points.size() == 3)
        {
            ret_Circle = CircumCircle(On_circle_points[0], On_circle_points[1], On_circle_points[2]);
        }
        return ret_Circle;
    }

    srand(time(0));
    int rand_num = rand() % Points.size();
    point p_temp = Points[rand_num];
    Points.erase(Points.begin() + rand_num);

    circle C_temp = min_cir(Points, On_circle_points, Original_points);
    if (C_temp.Is_inside(p_temp))
    {
        Points.push_back(p_temp);
        return C_temp;
    }
    On_circle_points.push_back(p_temp);
    circle ans = min_cir(Points, On_circle_points, Original_points);
    Points.push_back(p_temp);
    return ans;
}

int main()
{
    int num_of_points;
    ifstream fin;
    fin.open("input.csv");
    fin >> num_of_points;

    vector<point> set_of_points;

    for (int i = 1; i <= num_of_points; ++i)
    {
        point Point;
        Point.id = i;
        string comma;
        fin >> Point.x_cor >> comma >> Point.y_cor;
        set_of_points.push_back(Point);
    }
    vector<point> duplicate = set_of_points;
    random_shuffle(duplicate.begin(), duplicate.end());


    vector<point> P;
    circle Circle = min_cir(duplicate, P, set_of_points);

    ofstream fout;
    fout.open("output.txt");
    fout << Circle.radius << "\n";
    fout << Circle.centre.x_cor << ", " << Circle.centre.y_cor << "\n";
    cout << "center is (" << Circle.centre.x_cor << ", " << Circle.centre.y_cor << ") and radius is " << Circle.radius << "\n";

    return 0;
}