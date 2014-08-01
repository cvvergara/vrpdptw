#include <limits>
#include <stdexcept>
#include <algorithm>
#include <math.h>

#include "Problem.h"

// NON class functions for sorting

bool sortByDist(Order a, Order b)
{
    return a.dist > b.dist;
}

// Class functions

unsigned int Problem::getNodeCount() {
    return (unsigned int) N.size();
}

unsigned int Problem::getOrderCount() {
    return (unsigned int) O.size();
}

int Problem::getOrderOid(int i) const{
    return O[i].oid;
    //return  (i>=0 && i < O.size()) ? O[i].oid :1;
};

int Problem::getOrderPid(int i) const{
    return O[i].pid;
    //return  (i>=0 && i < O.size()) ? O[i].oid :1;
};

int Problem::getOrderDid(int i) const{
    return O[i].did;
    //return  (i>=0 && i < O.size()) ? O[i].oid :1;
};

Node& Problem::getDeliveryNodeFromOrder(int i){
    return N[getOrderDid(i)];
}

Node& Problem::getPickupNodeFromOrder(int i){
    return N[getOrderPid(i)];
}

double Problem::nodeDemand(int i) const {
    return N[i].getDemand();
}

bool Problem::lateArrival(int nid,double D) const {
    return N[nid].lateArrival(D);
}

bool Problem::earlyArrival(int nid,double D) const {
    return N[nid].earlyArrival(D);
}


double Problem::nodeServiceTime(int nid) const {
//    std::cout << "Problem service node"<<nid<<"="<< N[nid].getServiceTime()<<"\n";
    return N[nid].getServiceTime();
}

Order Problem::getOrder(int i) const {
    return O[i];
    //return  (i>=0 && i <= O.size()) ? O[i]: O[0] ;
}

double Problem::DepotToDelivery(int n1) const {
    return  (n1>=0 && n1 <= N.size()) ? N[N[n1].did].distance(depot):-1;
    //return N[N[n1].did].distance(depot);
}

double Problem::DepotToPickup(int n1) const {
    return  (n1>=0 && n1 <= N.size()) ? N[n1].distance(depot):-1;
    //return N[n1].distance(depot);
}

double Problem::distance(int n1,int n2) const {
    return N[n1].distance(N[n2]);
/*    double dx = N[n2].x - N[n1].x;
    double dy = N[n2].y - N[n1].y;
    return sqrt( dx*dx + dy*dy );*/
}

bool Problem::checkIntegrity() const {
   bool flag=true;
   int nodesCant=N.size();
   int ordersCant=O.size();
   if (N.empty()) {
        std::cout << "Nodes is empty\n";
        flag=false; }
   else std::cout << "# of Nodes:"<<nodesCant<<"\n";

   if (O.empty()) {
        std::cout << "Orders is empty\n";
        flag=false;}
   else std::cout << "# of Orders:"<<ordersCant<<"\n";

   if (ordersCant != (nodesCant-1)/2) {
        std::cout << "Expected "<<(nodesCant-1)/2<<" Orders. Found "<<ordersCant<<" Orders\n";
        flag=false;}
   else std::cout << "Found expected # of Orders\n";

  for (std::vector<Node>::const_iterator it= N.begin(); it!=N.end(); ++it) {
     bool flag1=true;
     Node node=*it;
     flag= flag and node.checkIntegrity(nodesCant);
   }
  for (std::vector<Order>::const_iterator it= O.begin(); it!=O.end(); ++it) {
     Order order=*it;
     flag= flag and order.checkIntegrity(nodesCant);
   }
   return flag;
}

void Problem::dump() {
    std::cout << "---- Problem -------------\n";
    std::cout << "K: " << K << std::endl;
    std::cout << "Q: " << Q << std::endl;
    std::cout << "w1: " << w1 << std::endl;
    std::cout << "w2: " << w2 << std::endl;
    std::cout << "w3: " << w3 << std::endl;
    std::cout << "extents: " << extents[0] << ", "
                             << extents[1] << ", "
                             << extents[2] << ", "
                             << extents[3] << std::endl;
    std::cout << "---- Orders --------------\n";
    for (int i=0; i<O.size(); i++)
        O[i].dump();
    std::cout << "---- Nodes  --------------\n";
    for (int i=0; i<N.size(); i++)
        N[i].dump();
    std::cout << std::endl;
}


void Problem::loadProblem(char *infile)
{
    std::ifstream in( infile );
    std::string line;

    // read header line
    std::getline(in, line);
    std::istringstream buffer( line );
    buffer >> K;
    buffer >> Q;

    // initialize the extents
    extents[0] = std::numeric_limits<double>::max();
    extents[1] = std::numeric_limits<double>::max();
    extents[2] = std::numeric_limits<double>::min();
    extents[3] = std::numeric_limits<double>::min();


    // read the nodes
    while ( getline(in, line) ) {
        Node node(line);
       /*std::istringstream buffer( line );
        buffer >> node.nid;
        buffer >> node.x;
        buffer >> node.y;
        buffer >> node.demand;
        buffer >> node.tw_open;
        buffer >> node.tw_close;
        buffer >> node.service;
        buffer >> node.pid;
        buffer >> node.did;
*/
        // compute the extents as we load the data for plotting
        if (node.x < extents[0]) extents[0] = node.x;
        if (node.y < extents[1]) extents[1] = node.y;
        if (node.x > extents[2]) extents[2] = node.x;
        if (node.y > extents[3]) extents[3] = node.y;

        N.push_back(node);

        //if (node.nid == 0)
        if (node.isDepot()) {
            DepotClose = node.tw_close;
            depot = node;
        }
    }
    in.close();

    // add a small buffer around the extents
    extents[0] -= (extents[2] - extents[0]) * 0.02;
    extents[2] += (extents[2] - extents[0]) * 0.02;
    extents[1] -= (extents[3] - extents[1]) * 0.02;
    extents[3] += (extents[3] - extents[1]) * 0.02;

    // make orders from the nodes
    makeOrders();

    // sort the orders
    sort(O.begin(), O.end(), sortByDist);

    calcAvgTWLen();
}


void Problem::makeOrders ()
{
    if (getNodeCount() == 0 || ((getNodeCount()-1)%2 != 0)) {
        std::string errmsg = "Problem::makeOrders - Nodes have not be correctly loaded.";
        throw std::runtime_error(errmsg);
    }

    O.reserve( (getNodeCount()-1)/2+1 );

    int oid = 0;

    // add the depot to the order   --- DEPOT doesnt have an order
    Order order(oid++);
    O.push_back(order);

    // for each pickup, get its delivery and create an order
    for (int i=1; i<getNodeCount(); i++) {
        if (N[i].pid == 0) {
            //Order order(oid++,i,N[i].did,N[i].distance(N[0]),N[N[i].did].distance(N[0]));
            Order order(oid++,i,N[i].did,DepotToPickup(i),DepotToDelivery(i));
            O.push_back(order);
        }
    }
}


void Problem::calcAvgTWLen() {
    // get the average time window length
    atwl = 0;
    for (int i=0; i<N.size(); i++)
        atwl += N[i].windowLength();
        //atwl += (N[i].tw_close - N[i].tw_open);
    atwl /= N.size();
};

