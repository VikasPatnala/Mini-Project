#include <bits/stdc++.h>

using namespace std;

struct point
{
    int id;
    int sign;   //to denote which side of the line the point is present
    double x;
    double y;
};

/*
    region class is for storing the rectangular region
    it will have the rectangle points and functions for
    telling whether the given point is in the region and
    whether the given region is intersecting or completely inside region.
*/
class region{
public:
    double x_lft;
    double x_rgt;
    double y_bot;
    double y_top;

    region(double x_lft,double x_rgt,double y_bot,double y_top){
        this->x_lft = x_lft;
        this->x_rgt = x_rgt;
        this->y_bot = y_bot;
        this->y_top = y_top;
    }

    // checking if point p is inside the region.
    bool check_inside_points(point* p){
        if(p->x <= x_rgt && p->x >= x_lft && p->y <= y_top && p->y >= y_bot){
            return true;
        }
        else{
            return false;
        }
    }

    // checking if the region reg is inside the region.
    bool check_reg_inside(region* reg){
        if(reg->x_lft >= x_lft && reg->x_rgt <= x_rgt && reg->y_bot >= y_bot && reg->y_top <= y_top){
            return true;
        }
        else{
            return false;
        }
    }

    // checking if the region reg is intersecting with the region.
    bool check_reg_intersect(region* reg){
        // cout<<reg->x_lft<<"-"<<reg->x_rgt<<"-"<<reg->y_bot<<"-"<<reg->y_top<<endl;
        // cout<<x_lft<<"-"<<x_rgt<<"-"<<y_bot<<"-"<<y_top<<endl;
        if(reg->x_lft == reg->x_rgt || reg->y_bot == reg->y_top || x_lft == x_rgt || y_bot == y_top){
            return false;
        }
        if(reg->x_lft > x_rgt || x_lft > reg->x_rgt){
            return false;
        }
        if(reg->y_bot > y_top || y_bot > reg->y_top){
            return false;
        }
        return true;
    }
};

/*
    class node is for storing information of node in the tree
    it consists left, right childs, w.r.t which axis it is splitting
    and if the node is leaf or not, if leaf it must should have the point
    and region 
*/
class node
{
public:
    node* left;
    node* right;
    int depth;
    bool isleaf;
    point* Point;
    double value;
    char axis;
    region* reg;

    node(int depth,double value,char axis,node* left, node* right) {
        this->depth = depth;
        this->value = value;
        this->axis = axis;
        this->isleaf = false;
        this->left = left;
        this->right = right;
        this->reg = NULL;
    }

    node(int depth, point* Point) {
        this->depth = depth;
        this->Point = Point;
        this->isleaf = true;
        this->left = NULL;
        this->right = NULL;
        this->reg = new region(Point->x,Point->x,Point->y,Point->y);
    }
};

bool comparepoint_x(point* p1, point* p2)
{
    if(p1->x == p2->x) {
        return (p1->y< p2->y);
    }
    else {
        return (p1->x < p2->x);
    }
}

bool comparepoint_y(point* p1, point* p2)
{
    if(p1->y == p2->y) {
        return (p1->x < p2->x);
    }
    else {
        return (p1->y < p2->y);
    }
}

node* BuildKDTree(vector<point*>& points, int depth, vector<point*>& x_sorted, vector<point*>& y_sorted)
{
    vector<point*> p1, p2;
    int median;
    double value;
    char axis;
    int n = points.size();
    if(n % 2 == 0) {
        median = n / 2 - 1;
    }
    else {
        median = n / 2;
    }

    node* left;
    node* right;
    node* curr;

    if(points.size() == 1) {
        return new node(depth, points[0]);
    }
    else if(depth % 2 == 0) {
        for(auto i : points){
            if(i->x <= x_sorted[median]->x){
                p1.push_back(i);
                i->sign = -1;
            }
            else{
                p2.push_back(i);
                i->sign = +1;
            }
        }
        value = x_sorted[median]->x;
        axis = 'x';
    }
    else {
        for(auto i : points){
            if(i->y <= y_sorted[median]->y){
                p1.push_back(i);
                i->sign = -1;
            }
            else{
                p2.push_back(i);
                i->sign = +1;
            }
        }
        value = y_sorted[median]->y;
        axis = 'y';
    }

    vector<point*> x_sorted_pos, y_sorted_pos;
    vector<point*> x_sorted_neg, y_sorted_neg;
    for(auto i : x_sorted) {
        if(i->sign == 1){
            x_sorted_pos.push_back(i);
        }
        else{
            x_sorted_neg.push_back(i);
        }
    }

    for(auto i : y_sorted) {
        if(i->sign == 1){
            y_sorted_pos.push_back(i);
        }
        else{
            y_sorted_neg.push_back(i);
        }
    }

    left = BuildKDTree(p1, depth + 1, x_sorted_neg, y_sorted_neg);
    right = BuildKDTree(p2, depth + 1, x_sorted_pos, y_sorted_pos);

    curr = new node(depth + 1, value, axis, left, right);
    region* reg = new region(x_sorted[0]->x,x_sorted[n-1]->x,y_sorted[0]->y,y_sorted[n-1]->y);
    curr->reg = reg;
    return curr;
}

ofstream fout;

void traverse(node* root, bool isfirst, bool isnormal)
{
    if(root->left) {
        if (isfirst) {
            fout << root->axis << " " << root->value << "\n";
        }
        traverse(root->left, isfirst, isnormal);
    }
    if(root->isleaf) {
        if (isnormal) {
            cout << root->Point->x << ", " << root->Point->y << endl;
        }
        else {
            fout << root->Point->x << ", " << root->Point->y << endl;
        }
    }
    if(root->right) {
        if(isfirst) {
            fout << root->axis << " " << root->value<< "\n";
        }
        traverse(root->right, isfirst, isnormal);
    }
}

void SearchKDTree(node* root, region Reg){
    if(root->isleaf){
        if(Reg.check_inside_points(root->Point)){
            fout << root->Point->x << " " << root->Point->y << endl;
        }
        return;
    }
    if(Reg.check_reg_inside(root->left->reg)){
        traverse(root->left, 0, 0);
    }
    else if(Reg.check_reg_intersect(root->left->reg)){
        SearchKDTree(root->left,Reg);
    }
    if(Reg.check_reg_inside(root->right->reg)){
        traverse(root->right, 0, 0);
    }
    else if(Reg.check_reg_intersect(root->right->reg)){
        SearchKDTree(root->right,Reg);
    }
}

int main()
{
    int num_of_points;
    ifstream fin;

    fin.open("input1.csv");
    fin >> num_of_points;
    
    vector<point*> vec_of_points;

    for(int i = 1; i <= num_of_points; ++i) {
        point* Point = new point;
        Point->id = i;
        string comma;
        fin >> Point->x >> comma >> Point->y;
        vec_of_points.push_back(Point);
    }

    vector<point*> x_sorted, y_sorted;
    x_sorted = vec_of_points;
    sort(x_sorted.begin(),x_sorted.end(),comparepoint_x);
    y_sorted = vec_of_points;
    sort(y_sorted.begin(),y_sorted.end(),comparepoint_y);

    // for(auto i : x_sorted){
    //     cout << i->id << " " << i->x << " "<< i->y << "\n";
    // }

    // for (auto i : y_sorted) {
    //     cout << i.second << " " << i.first << "\n";
    // }

    node* root = BuildKDTree(vec_of_points, 0, x_sorted, y_sorted);

    fout.open("output1.txt");
    traverse(root, 1, 1);
    //cout<<root->reg->x_lft<<"-"<<root->reg->x_rgt<<"-"<<root->reg->y_bot<<"-"<<root->reg->y_top<<endl;

    double x1,x2,y1,y2;
    string dummy;
    fin >> dummy >> x1 >> x2 >> y1 >> y2;
    x1=min(x1,x2);
    x2=max(x1,x2);
    y1=min(y1,y2);
    y2=max(y1,y2);

    region Reg(x1,x2,y1,y2);
    SearchKDTree(root,Reg);

    return 0;
}