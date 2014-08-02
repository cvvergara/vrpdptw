
#include "node.h"
#include "order.h"




int Order::getoid() const{ return oid;}
int Order::getpid() const {return pid;}
int Order::getRoute(){return routeId;}
int Order::getdid() const {return did;}
double Order::getDistFromPickup(){return dist;}
double Order::getDistFromDelivery(){return dist2;}
void  Order::moveOrder(int toRoute) {routeId=toRoute;}
bool Order::checkIntegrity(int nodesCant) {
     bool flag=true;
     if (pid<0 or pid>nodesCant) {
        std::cout << "Order["<<oid<<"]: pickup id out of range:"<<pid<<"expected in [0,"<<nodesCant<<"] \n";
        flag=false;}
     if (did<0 or did>nodesCant) {
        std::cout << "Order["<<oid<<"]: pickup id out of range:"<<did<<"expected in [0,"<<nodesCant<<"] \n";
        flag=false;}
     return flag;
}


void Order::dump() {
    std::cout << "Order#"<<oid << ":  "
              << pid << ", "
              << did << ", "
              << dist <<  ", "
              << dist2 << std::endl;
    std::cout <<  "pickupPtr \n";
    pickup->dump();
    std::cout <<  "deliveryPtr \n";
    delivery->dump();
}
