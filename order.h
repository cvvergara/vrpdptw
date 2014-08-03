#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "node.h"

class Order {
private:
   
  public:
    int oid;        // order id
//    int pid;        // pickup node id
//    int did;        // delivery node id
    int routeId;      // routID
    double dist;    // distance from depot to pickup location
    double dist2;   // distance from delivery to depot
    bool asigned;   // distance from delivery to depot
    Node *pickup;
    Node *delivery;



int setOrder(int i_oid, /*int i_pid, int i_did,*/ double i_dist, double i_dist2, bool i_asigned){
    oid=i_oid;
//    pid=i_pid;
//    did=i_did;
    dist=i_dist;
    dist2=i_dist2;
    asigned=i_asigned;
    return oid;
};

Order(Node &p, Node &d , int i_oid, const Node depot){ 
      fillOrder(p,d,i_oid,depot);
}

void fillOrder(Node &p, Node &d , int i_oid, const Node depot){ 
      oid=i_oid;
//      pid=p.getnid();
//      did=d.getnid();
      pickup=&p;
      delivery=&d;
      pickup->setoid(i_oid);
      delivery->setoid(i_oid);
      dist=pickup->distance(depot);
      dist2=delivery->distance(depot);
      asigned=false;
}

Order(const Order& other){
            pickup=other.pickup;
            delivery=other.delivery;

         setOrder(other.oid,/*other.pid,other.did,*/other.dist,other.dist2,other.asigned);
};

Order(){
         pickup=NULL;
         delivery=NULL;
         setOrder(-1,/*-1,-1,*/0,0,false);
}
    // ~Order() {};
/*
Order& operator=(const Order& other) {
            pickup=other.pickup;
            delivery=other.delivery;
            pickupPtr=other.pickupPtr;
            deliveryPtr=other.deliveryPtr;
std::cout<<"pickup node in asigment";
pickupPtr->dump();
         setOrder(other.oid,other.pid,other.did,other.dist,other.dist2,other.asigned);
         return *this;
}
*/
bool isUnasigned() const { return !asigned;};
bool isAsigned()   const { return asigned;};



    int getoid() const;
//    int getpid() const;
    int getRoute();
//    int getdid() const;
    bool checkIntegrity(int nodesCant);
    double getDistFromPickup();
    double getDistFromDelivery();
    void  moveOrder(int toRoute);


    void dump();
};

#endif
