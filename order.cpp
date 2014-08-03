
#include "node.h"
#include "order.h"




int Order::getoid() const{ return oid;}
//int Order::getpid() const {return pid;}
int Order::getRoute(){return routeId;}
//int Order::getdid() const {return did;}
double Order::getDistFromPickup(){return dist;}
double Order::getDistFromDelivery(){return dist2;}
void  Order::moveOrder(int toRoute) {routeId=toRoute;}

bool Order::checkIntegrity(int ordersCant) {
     bool flag=true;
     if (oid<0 or oid>ordersCant) {
        std::cout << "Order["<<oid<<"]: Order oid out of range:"<<oid<<"expected in [0,"<<ordersCant<<"] \n";
        flag=false;}
     return flag;
}


void Order::dump() {
    std::cout << "Order#"<<oid << ":  "
//              << pid << ", "
//              << did << ", "
              << dist <<  ", "
              << dist2 << std::endl;
    std::cout <<  "Pickup \n";
    pickup->dump();
    std::cout <<  "Delivery \n";
    delivery->dump();
}
