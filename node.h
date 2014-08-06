#ifndef NODE_H
#define NODE_H
#include <stdexcept>
#include <math.h>

#include <iostream>
class Order;

class Node {
private:
    int nid;        // node number (0 = depot
    double x;       // x location
    double y;       // y location
    int demand;     // capacity demand
    int tw_open;    // earliest window time
    int tw_close;   // latest window time
    int service;    // service time
    int pid;        // pickup (id of sibling)
    int did;        // delivery (id of sibling)

    int dist;       //distance to depot
    int oid;        // the order to which it belongs
    Order *order;    //point to its order

  public:
/*Accesors */
   int pickupId() const { return pid;};
    int deliveryId() const {return did;};
    int getoid() const { return oid;};  
    int getpid() const { return pid;};
    int getdid() const {return did;};
    int getnid() const {return nid;};
    int getdist() const {return dist;};
    int getx() const {return x;};
    int gety() const {return y;};
    int opens() const {return tw_open;};
    int closes() const {return tw_close;};
    double getDemand() const{ return demand;};
    double getServiceTime() const{  return service;};
    int windowLength() const { return  tw_close - tw_open; };
/*Mutators***/
    void setdist(const Node depot)  { if (nid==0) dist=0; else dist=distance(depot); }  
    void setoid(const int i_oid)  { oid=i_oid;}  
    void setorder(Order &o) {order=&o;};  
/****/
    bool checkIntegrity(int nodesCant);
    bool earlyArrival(double D) const { return D < tw_open;};
    bool lateArrival(double D) const { return D > tw_close;};
    bool ispickup() const { return did and nid!=0;};
    bool isdelivery() const { return pid and nid!=0;};
    bool isdepot() const {return nid==0;};
    bool sameorder(Node &n) {return order == n.order;};
    double distance(const Node &n2) const {
         double dx = n2.x - x;
         double dy = n2.y - y;
         return sqrt( dx*dx + dy*dy );
    };

/****/
    void dump() const;

    Node() {};
    Node(std::string line) ;
    ~Node() {};

};

#endif
