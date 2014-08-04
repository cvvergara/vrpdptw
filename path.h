#ifndef PATH_H
#define PATH_H

//#include <stdexcept>
//#include <algorithm>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
#include <deque>
//#include <math.h>

#include "order.h"
#include "node.h"
#include "pathnode.h"
#include "problem.h"  
//eventually problem.h wont be added herethis disapears


class Path{
  private:
    Node *depot;
    double w1,w2,w3;
       
  public:
    int rid;

    std::deque<pathNode> path;      // node ids along the path and more
    bool twv_depot;
    bool cv_depot;
    double D;      // duration
    int TWV;    // TW violations
    int CV;     // capacity violations


    Path (Node &d){
         depot = &d;
         twv_depot=false;
         cv_depot=false;
	 D= TWV=CV=0;
         w1=w2=w3=1;
         pathNode dep(d);
         path.push_back(dep);
     };

    ~Path() {};

    void seteval(double iw1,double iw2, double iw3){w1=iw1;w2=iw2;w3=iw3;};
    int getnid(int i) { return path[i].getnid(); };
    int  getoid(int i) { return path[i].getoid(); };
    void swapnodes(int i,int j);
    void swap(int i,int j);
    void push_back(pathNode pathstop);
    void emplace(pathNode pathstop,int at);
    void setvalues(int at);
    void setDepotValues();
    void dump();
    void smalldump();
    bool ispickup(int i) {return path[i].ispickup();}
    bool isdelivery(int i) {return path[i].isdelivery();}
    bool isdepot(int i) {return path[i].isdepot();}
    bool sameorder(int i,int j){return path[i].sameorder(path[j]);}
    bool findImprovment(int i);
    void hillClimbOpt();
    double getcost() {
       return   w1*D + w2*TWV + w3*CV;
    }


};
/*
    Route &operator = (const Route &r) { P = r.P; return *this; };

    void update();
    bool earlyArrival(int pathstop,double D) const;
    bool lateArrival(int  pathstop,double D) const;
    double distanceToPrev(int pathstop);
    double distanceToNext(int pathstop);
    int nodeDemand(int pathstop) const;   
    int nodeServiceTime (int pathstop) const;   
    double testPath(const std::vector<int>& tp);
    bool capacityViolation(double q) const;

    double getCost();

    void addOrder(const Order &o);

    bool insertOrder(int oid, bool mustBeValid);

    void removeOrder(const Order &o);
    void removeOrder(const int oid);

    int addPickup(const Order &o);
    void addDelivery(const Order &o);

    void hillClimbOpt();

    void dump();
};
*/
#endif
