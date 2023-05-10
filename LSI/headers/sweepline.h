#ifndef SWEEPLINE_H
#define SWEEPLINE_H

#include "classes.h"

struct Eventcompare
{
    bool operator() (Event* e1, Event* e2) {
        if (e1->value > e2->value) {
            return true;
        }
        else
            return false;
    }
};

struct Segmentcompare
{
    bool operator() (Segment *s1, Segment *s2) {
        if (s1->value < s2->value) {
            return true;
        }
        else
            return false;
    }
};

// bool operator==(Segment *left, Segment *right)
// {
//     return left.x == right.x && left.y == right.y;
// }

class Sweepline
{
public:
    // data structures

    // Event queue
    set<Event *, Eventcompare> EventQ;

    // segments tree
    set<Segment *, Segmentcompare> SegmentTree;

    // vector for storing intersection points
    vector<Point*> res;

    set<pair<Segment*, Segment*>> Check;


    // Constructor
    Sweepline(vector<Segment*> data) {
        for (auto seg : data) {
            // inserting starting points of line
            this->EventQ.insert(new Event(seg->first(), seg, 0));
            // inserting ending points of line
            this->EventQ.insert(new Event(seg->second(), seg, 1));
        }
        // for (auto i : EventQ) {
        //     cout << i->point->y << "- type " << i->type << "- value " << i->value << "\n";
        // }
    }

    // ~Sweepline() {
    //     for (auto i : SegmentTree) {
    //         free(i);
    //     }
    // }

        // cout << "hai\n";
    // Intersecting points finding function
    void FindIntersections() {
        while(!this->EventQ.empty()) {
            Event* e = *(this->EventQ.begin());
            
            this->EventQ.erase(this->EventQ.begin());
            
            double L = e->value;
            // cout << "l is " << L << "\n";
            switch(e->type) {
                case 0: {
                    for (auto seg : e->segments) {
                        this->recompute(L);
                        this->SegmentTree.insert(seg);
                        // cout << SegmentTree.size() << "@@@@@@\n";
                        
                        auto it = this->SegmentTree.find(seg);
                        auto temp = it;
                        
                        if (it != this->SegmentTree.begin() && it != this->SegmentTree.end()) {
                            // cout << "L " << L << "!!!!!!!\n";
                            temp--;
                            Segment* lower = *(temp);
                            this->Intersection(lower, seg, L);
                        }

                        if (it != this->SegmentTree.end()) {
                            it++;
                            if(it != this->SegmentTree.end()){
                                Segment *higher = *it;
                                this->Intersection(higher, seg, L);
                            }
                        }
                    }
                    break;
                }
                case 1: {
                    for (auto seg : e->segments) {
                        auto it = this->SegmentTree.find(seg);
                        auto temp = it;

                        if (it != this->SegmentTree.begin() && it != this->SegmentTree.end()) {
                            it++;
                            if(it != this->SegmentTree.end()) {
                                temp--;
                                Segment *r = *(temp);
                                Segment *t = *it;
                                this->Intersection(r, t, L);
                            }
                        }
                        if(this->SegmentTree.find(seg) != this->SegmentTree.end())
                            this->SegmentTree.erase(this->SegmentTree.find(seg));
                    }
                    break;
                }
                case 2: {
                    // cout << "Hai$$\n";
                    Segment* s1 = e->segments[0];
                    Segment* s2 = e->segments[1];
                    L = e->value - 1e-10;
                    // for (auto i : SegmentTree) {
                    //     cout << i->first()->x << " " << i->first()->y << "&&&&&&\n";
                    // }
                    this->swap(s1, s2, L);
                    // cout << "Hai##\n";
                    // for (auto i : SegmentTree) {
                    //     cout << i->first()->x << " " << i->first()->y << "&&&&&&&&\n";
                    // }
                    // this->recompute(L);
                    if (s1->value < s2->value) {
                        auto it = this->SegmentTree.find(s2);
                        if (it != this->SegmentTree.end()) {
                            it++;
                            if(it != this->SegmentTree.end()) {
                                Segment *t = *it;
                                this->Intersection(t, s2, L);
                            }
                        }

                        it = this->SegmentTree.find(s1);
                        if (it != this->SegmentTree.begin() && it != this->SegmentTree.end()) {
                            it--;
                            Segment* r = *(it);
                            this->Intersection(r, s1, L);
                        }
                    }
                    else {
                        auto it = this->SegmentTree.find(s1);
                        if (it != this->SegmentTree.end()) {
                            it++;
                            if(it != this->SegmentTree.end()) {
                                Segment *t = *it;
                                this->Intersection(t, s1, L);
                            }
                        }

                        it = this->SegmentTree.find(s2);
                        if (it != this->SegmentTree.begin() && it != this->SegmentTree.end()) {
                            it--;
                            Segment* r = *(it);
                            this->Intersection(r, s2, L);
                        }
                    }

                    this->res.push_back(e->point);
                    break;
                }
            }
        }
    }


    // Function to find the intersection of lines and check whether the intesection is 
    // below our status line or not
    bool Intersection(Segment* s1, Segment* s2, double L) {
        if(this->Check.find({s1, s2}) != this->Check.end() 
            || this->Check.find({s2, s1}) != this->Check.end()) {
            return true;
        }
        
        double x1 = s1->first()->x;
        double y1 = s1->first()->y;
        double x2 = s1->second()->x;
        double y2 = s1->second()->y;
        double x3 = s2->first()->x;
        double y3 = s2->first()->y;
        double x4 = s2->second()->x;
        double y4 = s2->second()->y;

        double r = (x2 - x1) * (y4 - y3) - (y2 - y1) * (x4 - x3);
        if (r != 0) {
            double t = ((x3 - x1) * (y4 - y3) - (y3 - y1) * (x4 - x3)) / r;
            double u = ((x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1)) / r;
            if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
                    double x_intersection = x1 + t * (x2 - x1);
                    double y_intersection = y1 + t * (y2 - y1);
                    if (y_intersection < L)
                    {
                        vector<Segment*> list;
                        list.push_back(s1);
                        list.push_back(s2);
                        this->Check.insert({s1, s2});
                        // cout << y_intersection << "###\n";
                        // if(this->EventQ.find())
                        this->EventQ.insert(new Event(new Point(x_intersection, y_intersection), list, 2));
                        return true;
                    }
            }
        }
        return false;
    }

    // swap two segments are the intersection event
    void swap(Segment* s1, Segment* s2, double L) {
        if (this->SegmentTree.find(s1) != this->SegmentTree.end())
            this->SegmentTree.erase(this->SegmentTree.find(s1));
        if(this->SegmentTree.find(s2) != this->SegmentTree.end())
            this->SegmentTree.erase(this->SegmentTree.find(s2));

        s1->compute_value(L);
        s2->compute_value(L);
        this->recompute(L);

        this->SegmentTree.insert(s1);
        this->SegmentTree.insert(s2);
    }

    // calculate value of every segment intersection status line 
    void recompute(double L) {
        for (auto i : SegmentTree) {
            i->compute_value(L);
        }
    }

    // function for printing the intersection points
    void PrintIntersections() {
        cout << "Number of intersection points are " << res.size() << "\n";
        for (auto i : res) {
            cout << "(" << i->x << ", " << i->y << ")\n";
        }
        // for (auto i : res) {
        //     cout << i->x << ", ";
        // }
        // cout << "\n";
        // for (auto i : res) {
        //     cout << i->y << ", ";
        // }
        // cout << "\n";
    }

};

#endif