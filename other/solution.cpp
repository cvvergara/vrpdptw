nclude "route.h"
#include "solution.h"

// NON class functions for sorting
bool sortByOid(Order a, Order b)
{
    return a.oid < b.oid;
}

// Class functions

/*
void Solution::dumbConstruction() {
Route dumbroute(P);
P.sortOrdersbyDistReverse();
for (int i=0; i<P.getOrderCount(); i++) {
dumbroute.addOrder(P.getOrder(i));
}
dumbroute.dump();
R.push_back(dumbroute);
};

void Solution::dumbConstructionAndBestMoveForward() {
Route dumbroute(P);
int bestI;
int bestJ;
for (int i=0; i<P.getOrderCount(); i++) {
dumbroute.addOrder(P.getOrder(i));
}
dumbroute.dumppath();
dumbroute.findBetterForward(bestI, bestJ);
std::cout<<"best I"<<bestI<<", best J"<<bestJ<<"\n";
dumbroute.move(bestI,bestJ);
dumbroute.dumppath();
R.push_back(dumbroute);
};
void Solution::withSortedOrdersConstruction() {
P.sortOrdersbyDist();
dumbConstruction();
};

void Solution::dumbAndHillConstruction() {
Route dumbroute(P);
P.sortOrdersbyDistReverse();
for (int i=0; i<P.getOrderCount(); i++) {
dumbroute.addOrder(P.getOrder(i));
}
dumbroute.hillClimbOpt();
dumbroute.dump();
R.push_back(dumbroute);
};

void Solution::deliveryBeforePickupConstruction() {
Route dumbroute(P);
for (int i=0; i<P.getOrderCount(); i++) {
dumbroute.addDelivery(P.getOrder(i));
dumbroute.addPickup(P.getOrder(i));
}
dumbroute.dump();
R.push_back(dumbroute);
};

void Solution::sequentialConstruction() {
// std::cout << "Enter Problem::sequentialConstruction\n";
R.clear();
Order order;
std::deque<Order> unOrders;
std::deque<Order> waitOrders;
P.sortOrdersbyDist();
unOrders=P.O;
while (!unOrders.empty()) {
Route route(P);
std::cout<<"\n\n*******1 original orders"<<P.O.size()<<" wait orders "<< waitOrders.size()<<" unassigned Orders "<<unOrders.size()<<"\n";
while (!unOrders.empty()) {
order=unOrders.front();
unOrders.pop_front();
route.addOrder(order);
route.hillClimbOpt();
if (!route.feasable()) {
route.removeOrder(order);
waitOrders.push_back(order);
}
}
R.push_back(route);
unOrders=waitOrders;
waitOrders.clear();
}
dump();
}
*/
/*
bppos, bdpos = best pickup postition, best delivery postition
ppos, dpos = pickup postition, delivery postition
*/

void Solution::initialFeasableSolution() {
    int bppos, bdpos;
    int ppos, dpos;
    double actualcost, bestcost;
    R.clear();
    Order order;
    std::deque<Order> unOrders;
    std::deque<Order> waitOrders;
    P.sortOrdersbyDistReverse();
    unOrders=P.O;
    while (!unOrders.empty()) {
       Route route(P);
       while (!unOrders.empty()) {
         order=unOrders.front();
          unOrders.pop_front();
          route.addOrder(order);
          ppos=bppos=route.getppos(order.oid);
          dpos=bdpos=route.getdpos(order.oid);
          actualcost=getcost();
          bestcost=route.findBestCostBackForw(order.oid,bppos,bdpos); //can it come back with already tested for feasability
          if (bestcost<actualcost) { //found a better place
             if (bppos<bdpos) {
                 route.move(ppos,bppos);
                 route.move(dpos,bdpos);
             }
          }
          if (!route.feasable() ) {
                route.removeOrder(order);
                waitOrders.push_back(order);
          }
       }
       R.push_back(route);
       unOrders=waitOrders;
       waitOrders.clear();
     }
     dump();
}


/*
// std:dd:cout << "Enter Problem::sequentialConstruction\n";
int M = 0;
R.clear();
P.sortOrdersbyDist();
//int numUnassigned = P.O.size() - 1;
int numUnassigned = P.getOrderCount(); //-1 because of Oredr[0] from DEPOT
while (numUnassigned > 0) {
Route r(P);
r.rid = M;

for (int i=0; i<P.getOrderCount(); i++) {
if (P.isAsignedOrder(i)) continue;

r.addOrder(P.getOrder(i));
//mapOtoR[P.getOrderOid(i)] = r.rid;
r.hillClimbOpt();

// if route is not feasible
if (r.orders.size() > 1 && (r.TWV > 0 || r.CV > 0)) {
r.removeOrder(P.O[i]);
// mapOtoR[P.O[i].oid] = -1;
// mapOtoR[P.getOrderOid(i)] = -1;
}
// else if it is feasible
else {
// mapOtoR[P.O[i].oid] = r.rid;
// mapOtoR[P.getOrderOid(i)] = r.rid;
numUnassigned--;
}
}
R.push_back(r);
M++;
}

sort(P.O.begin(), P.O.end(), sortByOid);

//std::cout << "Exit Problem::sequentialConstruction\n";
}



void Solution::initialNoHillConstruction() {
for (int i=0; i<P.getOrderCount(); i++) {
Route dumbroute(P);
dumbroute.addOrder(P.getOrder(i));
R.push_back(dumbroute);
}
dumproutes();
};

void Solution::initialConstruction() {
int M = 0;
R.clear();

for (int i=0; i<P.getOrderCount(); i++) {
// for (int i=0; i<P.O.size(); i++) {
// if (P.O[i].oid == 0) continue; // don't add the depot
if (P.getOrderOid(i) == 0) continue; // don't add the depot
Route r(P);
r.rid = M++;
// r.addOrder(P.O[i]);
// mapOtoR[P.O[i].oid] = r.rid;
r.addOrder(P.getOrder(i));
//mapOtoR[P.getOrderOid(i)] = r.rid;
r.addOrder(P.getOrder(i));
//mapOtoR[P.getOrderOid(i)] = r.rid;
R.push_back(r);
}

sort(P.O.begin(), P.O.end(), sortByOid);
}
*/

void Solution::computeCosts() {
    totalCost = 0.0;
    totalDistance = 0.0;
    for (int i=0; i<R.size(); i++) {
        totalCost += R[i].getcost();
        totalDistance += R[i].D;
    }
}

double Solution::getcost() {
    computeCosts(); // somewhere in the code the getcost returns 0 because the cost hant been computed
    return totalCost;
}

double Solution::getDistance() {
    computeCosts();
    return totalDistance;
}




void Solution::tau() {
    std::cout<< "\nTau:" << std::endl;
    for (int i=0; i<R.size(); i++) {
        if (i) std::cout<< ",";
        R[i].tau();
    };
    std::cout<<"0\n";
}
void Solution::dumproutes() {
    std::cout<< "\nRoutes:" << std::endl;
    for (int i=0; i<R.size(); i++) {
        std::cout<<"\n -----> Route#"<<i<<"\n";
        R[i].dump();
    }
    tau();
}


void Solution::dump() {
    computeCosts();
    std::cout << "Solution: totalDistance: " << totalDistance
              << ", totalCost: " << totalCost
              << std::endl;
    tau();
    for (int i=0; i<R.size(); i++) {
        R[i].dumppath();
    }
}


double Solution::getAverageRouteDurationLength() {
    double len = 0.0;
    int n = 0;
    for (int i=0; i<R.size(); i++) {
        if (R[i].path.size() == 0) continue;
        if (R[i].updated) R[i].update();
        len += R[i].D;
        n++;
    }
    if (n == 0) {
        std::string errmsg = "Solution.getAverageRouteDurationLength: There do not appear to be any routes!";
        throw std::runtime_error(errmsg);
    }
    return len/n;
}
