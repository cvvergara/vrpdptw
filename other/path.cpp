
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



    void path::push_back(pathNode pathstop) {
         pathNode prev;
         prev= (path.size()) ? prev=depot: prev=path.back();        
         pathstop.setValues(prev);
         path.push_back(pathstop);
    };


    void path::emplace(pathNode pathstop,int at) {
         pathNode prev;
         prev= path[at];
         (at==0)? prev=depot: prev=path.[at];        
         pathstop.setValues(prev);
         path.emplace(path.begin()+at,pathstop);
    }

    void path::setvalues(int at){
         pathNode prev;
         (at==0)? prev=depot: prev=path.[at-1];
         if (at<path.size() {
              path[at].setvalues(prev);
              setvalues(at+1);
         } else {
              D = prev.totDistFromDepot+ depot.getDistFromStop(prev)
              twv_depot=depot.node.lateArrival(D);
              cv_depot=prev.cv;
              TWV = (twv_depot)? prev.twvTot+1:prev.twvTot;
              CV = (cv_depot)? prev.cvTot+1:prev.cvTot;
         };
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
