#ifndef PATH_H
#define PATH_H

//#include <stdexcept>
//#include <algorithm>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
//#include <math.h>

#include "Order.h"
#include "Node.h"
#include "pathNode.h"
//#include "Problem.h"


class path{
  public:
    int rid;

    std::vector<pathNode> path;      // node ids along the path and more
    pathNode depot;
    bool twv_depot;
    bool cv_depot;
    int D;      // duration
    int TWV;    // TW violations
    int CV;     // capacity violations

    double cost;

    path(Problem& p):depot(p.depot) {};
    ~path() {};

    void push_back(pathNode pathstop);
    void emplace(pathNode pathstop,int at);
    void setvalues(int at);
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
