#ifndef PROBLEM_H
#define PROBLEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

#include "Node.h"
#include "Order.h"
class Solution;

const double w1 = 1.0;  // route duration weighting
const double w2 = 1000.0;  // total number of time violations weight
const double w3 = 1.0;  // total number of capacity violations weight

class Problem {
  public:
    int K;      // number of vehicles
    int Q;      // capacity
    int DepotClose;
    Node depot;
    double atwl;
    std::vector<Node> N;    // vector of nodes
    std::vector<Order> O;   // vector of orders


    // variables for plotting
    double extents[4];

    // Problem() {};
    // ~Problem() {};

    void loadProblem(char *infile);

    unsigned int getNodeCount();
    bool checkIntegrity() const;

    unsigned int getOrderCount();

    double distance(int n1, int n2) const;
    double DepotToPickup(int n1) const ;
    double DepotToDelivery(int n1) const ;
    int getOrderOid(int i) const;
    int getOrderPid(int i) const;
    int getOrderDid(int i) const;
    double nodeDemand(int i) const;
    double nodeServiceTime(int i) const;
    bool earlyArrival(int nid,double D) const; 
    bool lateArrival(int nid,double D) const; 
    Node& getDeliveryNodeFromOrder(int i);
    Node& getPickupNodeFromOrder(int i);

    Order getOrder(int i) const;

    void makeOrders();

    void dump();

    void calcAvgTWLen();
};

#endif
