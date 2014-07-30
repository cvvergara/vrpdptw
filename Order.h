#ifndef ORDER_H
#define ORDER_H

#include <iostream>
class Node;

class Order {
  public:
    int oid;        // order id
    int pid;        // pickup node id
    int did;        // delivery node id
    double dist;    // distance from depot to pickup location
    double dist2;   // distance from delivery to depot

    Order() ;
    Order(const Order& other );
    Order(int i_oid);
    Order(int i_oid,const Node &n, const Node &depot);
    Order(int i_oid, int i_pid, int i_did, double i_dist, double i_dist2);
    int setOrder(int i_oid, int i_pid, int i_did, double i_dist, double i_dist2);
    int getoid();
    int getpid();
    int getdid();
    double getDistFromPickup();
    double getDistFromDelivery();

    // ~Order() {};

    void dump();
};

#endif
