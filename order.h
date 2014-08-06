#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "node.h"

class Order {
private:
   
  public:
    int oid;        // order id
    int rid;
//    double dist;    // distance from depot to pickup location  can be calculated
//    double dist2;   // distance from delivery to depot
    bool asigned;   
    Node *pickup;
    Node *delivery;



Order(Node &p, Node &d , int i_oid, const Node depot){ 
      fillOrder(p,d,i_oid,depot);
}

void fillOrder(Node &p, Node &d , int i_oid, const Node depot){ 
      oid=i_oid;
      pickup=&p;
      delivery=&d;
      pickup->setoid(i_oid);  //tell pickup and delivery they belong to the order
      delivery->setoid(i_oid);
      pickup->setdist(depot);
      delivery->setdist(depot);
      asigned=false;
}



Order(const Order& other){
      oid=other.oid;
      rid=other.rid;
      asigned=other.asigned;
      pickup=other.pickup;
      delivery=other.delivery;
};

Order(){ 
         oid=-1;
         rid=-1;
         asigned=false;
         pickup=NULL;
         delivery=NULL;
}

/*************accesosrs*/
int getpid() const {return pickup->getpid();}
int getdid() const {return delivery->getdid();}
int getoid() const {return oid;};int getrid() const {return rid;};

double getdistPickupDepot() const {return pickup->getdist();};
double getdistDeliveryDepot() const {return delivery->getdist();};
double getdistPickupOther(const Node other) const {return pickup->distance(other);};
double getdistDeliveryOther(const Node other) const {return pickup->distance(other);};
double getdistPickDeliver() const {return pickup->distance(*delivery);};
/************state*/
bool isUnasigned() const { return !asigned;}
bool isAsigned()   const { return asigned;}
bool checkIntegrity(const int nodesCant) const;
/************ mutators*/
void  moveOrder(const int toRoute);
/************ output */
void shortdump() const;
void dump() const;
};

#endif
