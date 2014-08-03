
#include <limits>
#include "route.h"
#include "solution.h"

inline void swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

Route::Route(Problem& p) : P(p) , routePath(p.getdepot()) {
    updated = true;
    D = 0;
    TWV = 0;
    CV = 0;
    path.clear();
    orders.clear();
};


bool Route::earlyArrival(int pathstop, double D) const {
    return P.earlyArrival(path[pathstop],D);
}

bool Route::lateArrival(int pathstop, double D) const {
    return P.lateArrival(path[pathstop],D);
}

double Route::distanceToPrev(int pathstop) {
     if (pathstop == 0)  return P.distance(0, path[pathstop]);
     else  return P.distance(path[pathstop-1], path[pathstop]);
}

double Route::distanceToNext(int pathstop) {
     if (pathstop == path.size()-1)  return P.distance(0, path[pathstop]);
     else  return P.distance(path[pathstop+1], path[pathstop]);
}

int Route::nodeDemand(int pathstop) const {
    return P.nodeDemand(path[pathstop]);
}

int Route::nodeServiceTime(int pathstop) const {
    return P.nodeServiceTime(path[pathstop]);
}


bool Route::capacityViolation(double q) const {
    return (q<0 and q>P.Q);
}

void Route::update() {
    D = 0; //duration
    TWV = 0; //Time window violation
    CV = 0; //Capacity violations
    int q = 0; // current used capcity

    for (int i=0; i<path.size(); i++) {
        D += distanceToPrev(i);
        if (lateArrival(i,D)) TWV++;

        // if we arrive before the tw open time, we have to wait till then
        if (earlyArrival(i,D))  D = P.N[path[i]].opens();

        // add the demand for this node and check for violation
        q += nodeDemand(i);
        if (capacityViolation(q)) CV++;

        // add the service time for this node
        D +=nodeServiceTime(i);
    }

    // add the distance between last delivery node and depot
    if (path.size()) D += distanceToNext(path.size()-1);
    //if (D > P.DepotClose) {
    if (P.getdepot().lateArrival(D))  TWV++;
    cost = w1*D + w2*TWV + w3*CV;
    updated = false;
};





double Route::testPath(const std::vector<int>& tp) {
    tD = 0;
    tTWV = 0;
    tCV = 0;
    int q = 0; // current used capcity

    for (int i=0; i<tp.size(); i++) {
        // add the distance from the previous stop
        if (i == 0) {
            tD += P.distance(0, tp[i]);
        }
        else {
            tD += P.distance(tp[i-1], tp[i]);

            // if the current distance is > previous node close time
            if (tD > P.N[tp[i]].closes())
                tTWV++;
        }

        // if we arrive before the tw open time, we have to wait till then
        if (tD < P.N[tp[i]].opens())
            tD = P.N[tp[i]].opens();

        // add the demand for this node and check for violation
        q += P.N[tp[i]].getDemand();
        if (q < 0 || q > P.Q)
            tCV++;

        // update the capacity and pdist lists
        // capacity[i] = q; // capacity after node is loaded
        // pdist[i] = D; // distance at node max(arrival time, tw_open)

        // add the service time for this node
        tD += P.N[tp[i]].getServiceTime();
    }

    // add the distance between last delivery node and depot
    if (tp.size())
        tD += P.distance(tp[tp.size()-1], 0);
    if (tD > P.DepotClose)
        tTWV++;

    return w1*tD + w2*tTWV + w3*tCV;
};




double Route::getCost() {
    if (updated) {
        update();
        cost = w1*D + w2*TWV + w3*CV;
    }
    return cost;
}



bool Route::insertOrder(int oid, bool mustBeValid) {
    // check if the order is already in the route
    std::vector<int>::iterator it;
    it = std::find(orders.begin(), orders.end(), oid);
    if (it != orders.end()) return false;

    Node& np = P.N[P.O[oid].pid];
    Node& nd = P.N[P.O[oid].did];
//    Node& np = P.getPickupNodeFromOrder(oid);
//    Node& nd = P.getDeliveryNodeFromOrder(oid);

    double bestTestCost = std::numeric_limits<double>::max();
    int bestPosition = -1;
    std::vector<int> newpath; // path with predecessor inserted
    std::vector<int> newpath2; // path with predecessot and successor inserted

    for (int i=0; i<path.size(); i++) {
        newpath = path;
        std::vector<int>::iterator it2;

        // insert the predecessor and check for violations
        it2 = newpath.begin();
        newpath.insert(it2+i, np.getnid());
        testPath(newpath);
        // a valid placement of the predessor node
        // requires that there are NO CV ot TW violations
        if (tCV > 0 || tTWV > 0) continue;

        // got a good insertion point, so now try the successor
        for (int j=i; j<path.size(); j++) {
            newpath2 = newpath;
            it2 = newpath2.begin();
            newpath2.insert(it2+j, nd.getnid());
            double tcost = testPath(newpath2);
            // if we are eliminating a route then mustBeValid is true
            // and we must be able to also place the successor node
            // without creating violations
            if (mustBeValid && (tCV > 0 || tTWV > 0)) continue;

            // if this is better than the previous best then save it
            if (tcost < bestTestCost) {
                bestTestCost = tcost;
                bestPosition = j;
            }
        }

        // TODO: why did we have the following???
        // if (bestPosition != -1) break;
    }

    // if we did not insert it above see if we can append to this route
    if (bestPosition == -1) {
        newpath2 = path;
        newpath2.push_back(np.getnid());
        newpath2.push_back(nd.getnid());
        double tcost = testPath(newpath2);
        if (mustBeValid && tCV == 0 && tTWV == 0) {
            bestTestCost = tcost;
            bestPosition = path.size();
        }
    }

    if (bestPosition != -1) {
        // apply the moves to this route
        path.clear();
        std::vector<int>::iterator it;
        for (int i=0; i<newpath2.size(); i++) {
            path.push_back(newpath2[i]);
            if (newpath2[i] == np.getnid() || newpath2[i] == nd.getnid()) {
                it = orders.begin();
                orders.insert(it+i, oid);
            }
        }
        updated = true;
//std::cout << "insertOrder(" << oid << "," << mustBeValid << "): ";
//dump();
        return true;
    }
    return false;
}

void Route::addOrder( Order &o) {
//Nodopid de la orden

//    pathNode pickup(P.N[o.pid]);
    pathNode pickup(*o.pickup);
    pathNode delivery(*o.delivery);
    routePath.push_back(pickup);
    routePath.push_back(delivery);
//    routePath.dump();
//std::cout<<"\nooooooooooooooooooooooooooooooooooooooooooo\n";

    path.push_back(o.pid);
    path.push_back(o.did);
    orders.push_back(o.oid);
    orders.push_back(o.oid);
    updated = true;
}

void Route::removeOrder(const Order &o) {

    std::vector<int>::iterator it;
    it = std::find(path.begin(), path.end(), o.pid);
    if (it != path.end()) path.erase(it);
    it = std::find(path.begin(), path.end(), o.did);
    if (it != path.end()) path.erase(it);
    it = std::find(orders.begin(), orders.end(), o.oid);
    if (it != orders.end()) orders.erase(it);
    it = std::find(orders.begin(), orders.end(), o.oid);
    if (it != orders.end()) orders.erase(it);
    updated = true;
}


void Route::removeOrder(const int oid) {
    const Order& o = P.O[oid];
    removeOrder(o);
}

int Route::addPickup(const Order &o) {
    pathNode pickup(*o.pickup);
    routePath.push_back(pickup);

    path.push_back(o.pid);
    orders.push_back(o.oid);
    hillClimbOpt();
    update();
    return (TWV || CV)? 0 : 1;
}


void Route::addDelivery(const Order &o) {
    pathNode delivery(*o.delivery);
    routePath.push_back(delivery);

    path.push_back(o.did);
    orders.push_back(o.oid);
    hillClimbOpt();
    update();
}


void Route::hillClimbOpt() {
//std::cout << "Enter Route::hillClimbOpt: rid: " << rid << std::endl;
    double oldcost = getCost();
    while (true) {
        bool improved = false;
        for (int i=0; i<path.size(); i++) {
            for (int j=i+1; j<path.size(); j++) {
                // don't move the delivery ahead of the pickup
                if (orders[i] == orders[j]) continue;
                if (P.N[path[j]].closes() < P.N[path[i]].closes()) {
                    swap(path[i], path[j]);
                    swap(orders[i], orders[j]);
                    update();
                    double newcost = getCost();
                    if (newcost < oldcost) {
                        improved = true;
//std::cout << "rid: " << rid << ", HC[" << i << "," << j << "] old: " << oldcost << ", new: " << newcost << std::endl;
                        oldcost = newcost;
                    }
                    else {
                        swap(path[j], path[i]);
                        swap(orders[j], orders[i]);
                        update();
                    }
                }
            }
        }
        if (!improved) break;
    }
    //std::cout << "Exit Route::hillClimbOpt\n";
}


void Route::dump() {
    update();
    std::cout << rid << ", "
              << D << ", "
              << TWV << ", "
              << CV << ", "
              << getCost() << ", [";
    for (int i=0; i<path.size(); i++) {
        if (i) std::cout << ", ";
        std::cout << path[i];
    }
    std::cout << "], [";
    for (int i=0; i<orders.size(); i++) {
        if (i) std::cout << ", ";
        std::cout << orders[i];
    }
    std::cout << "]" << std::endl;
    routePath.dump();
}

