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
    bool checkIntegrity(int nodesCant);
    bool earlyArrival(double D) const { return D < tw_open;};
    bool lateArrival(double D) const { return D > tw_close;};
    double getDemand() const{ return demand;};
    double getServiceTime() const{  
//    std::cout << "Problem service node"<<nid<<"="<< service<<"\n";
         return service;};

    Node() {};
    Node(std::string line) ;
    // ~Node() {};

    void dump();
};

#endif
