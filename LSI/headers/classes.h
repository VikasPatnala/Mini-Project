#ifndef CLASSES_H
#define CLASSES_H

#include <bits/stdc++.h>

using namespace std;

class Point
{
public:
    double x;
    double y;

    Point(double _x, double _y) : x(_x), y(_y) {}
};

class Segment
{
public:
    Point *p_1;
    Point *p_2;
    double value; // value at any particular given y coordinate for the segment;

    Segment(Point *_p_1, Point *_p_2) : p_1(_p_1), p_2(_p_2) {
        this->compute_value(this->first()->y);
    }

    Point *first() {
        if (p_1->y <= p_2->y) {
            return p_2;
        }
        else {
            return p_1;
        }
    }

    Point *second() {
        if (p_1->y <= p_2->y) {
            return p_1;
        }
        else {
            return p_2;
        }
    }

    void compute_value(double value) {
        double x1 = p_1->x;
        double x2 = p_2->x;
        double y1 = p_1->y;
        double y2 = p_2->y;
        this->value = x1 + ((value - y1) * (x2 - x1)) / (y2 - y1);
    }
};

class Event
{
public:
    Point *point;
    vector<Segment *> segments;
    double value;
    int type;

    Event(Point *p, Segment *s, int t) : point(p), value(p->y), type(t) {
        segments.push_back(s);
    }

    Event(Point *p, vector<Segment *> s, int t) : point(p), segments(s), value(p->y), type(t) {}
};

#endif