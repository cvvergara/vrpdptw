#ifndef NODE_H
#define NODE_H
#include <stdexcept>
#include <math.h>


#include <iostream>

class Node {
  public:
    int nid;        // node number (0 = depot
    double x;       // x location
    double y;       // y location
    int demand;     // capacity demand
    int tw_open;    // earliest window time
    int tw_close;   // latest window time
    int service;    // service time
    int pid;        // pickup (id of sibling)
    int did;        // delivery (id of sibling)

    bool isDepot() const {return nid==0;};

    double distance(const Node &n2) const {
         double dx = n2.x - x;
         double dy = n2.y - y;
         return sqrt( dx*dx + dy*dy );
    };

    int windowLength() const {
         return  tw_close - tw_open;
    };
    int pickupId() const { return pid;};
    int deliveryId() const {return did;};

    bool earlyArrival(double D){ return D < tw_open;};

    Node() {};
    Node(std::string line) ;
    // ~Node() {};

    void dump();
};

#endif
