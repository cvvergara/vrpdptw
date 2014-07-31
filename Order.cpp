
#include "Node.h"
#include "Order.h"

Order::Order() {
   setOrder(-1,0,0,0.0,0.0);
}

Order::Order(int i_oid){
   setOrder(i_oid,0,0,0.0,0.0);
}

Order::Order(const Order& other){
   setOrder(other.oid,other.pid,other.did,other.dist,other.dist2);
}

Order::Order(int i_oid, int i_pid, int i_did, double i_dist, double i_dist2){
   setOrder(i_oid,i_pid,i_did,i_dist,i_dist2);
}


int Order::setOrder(int i_oid, int i_pid, int i_did, double i_dist, double i_dist2){
    oid=i_oid;
    pid=i_pid;
    did=i_did;
    dist=i_dist;
    dist2=i_dist2;
    return getoid();
}

int Order::getoid(){ return oid;}
int Order::getpid(){return pid;}
int Order::getRoute(){return routeId;}
int Order::getdid(){return did;}
double Order::getDistFromPickup(){return dist;}
double Order::getDistFromDelivery(){return dist2;}
void  Order::moveOrder(int toRoute) {routeId=toRoute;}


void Order::dump() {
    std::cout << oid << ", "
              << pid << ", "
              << did << ", "
              << dist <<  ", "
              << dist2 << std::endl;
}
