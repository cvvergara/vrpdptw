#ifndef PATHNODE_H
#define PATHNODE_H

//#include <stdexcept>
//#include <algorithm>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
//#include <math.h>

#include "order.h"
#include "node.h"
//#include "Problem.h"

class pathNode {
public:
    Node &node;
//    Order order;
static const double cargoLimit=100; //need to set this data
    bool twv;
    bool cv;
    int twvTot;
    int cvTot;
    double cargo;
    double distPrev;
    double totDistFromDepot;

    void dump() {
        node.dump();
        std::cout<<"twv="<<twv
                 <<",cv="<<cv
                 <<",twvTot="<<twvTot
                 <<",cvTot="<<cvTot
                 <<",cargo="<<cargo
                 <<",distPrev="<<distPrev
                 <<",totDistFromDepot="<<totDistFromDepot
                 <<"\n";
    }
/***********************/     
    void copyvalues (const pathNode &other) {
//              order=other.order;
           //   cargoLimit=other.cargoLimit;
              twv=other.twv;
              cv=other.cv;
              twvTot=other.twvTot;
              cvTot=other.cvTot;
              cargo=other.cargo;
              distPrev=other.distPrev;
              totDistFromDepot=other.totDistFromDepot;
             };
   pathNode(Node &n) :node(n) {
              twv=false;
              cv=false;
              twvTot=0;
              cvTot=0;
              cargo=0;
              distPrev=0;
              totDistFromDepot=0;
   /*pathNode(const Node &n) :node(n) {
              twv=false;
              cv=false;
              twvTot=0;
              cvTot=0;
              cargo=0;
              distPrev=0;
     o*/         totDistFromDepot=0;

///std::cout<<"constructor1"; dump();
};
//    pathNode(Node &n, const Order &o) :node(n) {order=o;};
    pathNode(const pathNode &other):node(other.node) {
              copyvalues(other);
//              std::cout<<"constructor2"; dump();
     };
    pathNode& operator=(const pathNode &other) {
           //   node=other.node;
              copyvalues(other);
     };        

/*
    pathNode() {} ;
    pathNode(Node &n) {node=n;};
    pathNode(const pathNode &other) {
              node=other.node;
              order=other.order;
              cargoLimit=other.cargoLimit;
              twv=other.twv;
              cv=other.cv;
              twvTot=other.twvTot;
              cvTot=other.cvTot;
              cargo=other.cargo;
              distPrev=other.distPrev;
              totDistFromDepot=other.totDistFromDepot;
             };
  */
    double setDistPrev(const Node &prev) {
try{
          distPrev=node.distance(prev);
}
catch (std::exception& e)
{
    std::cerr << "Exception catched : " << e.what() << std::endl;
}
   };
    double getDistFromStop(pathNode &other) {return node.distance(other.node);};
    void   setValues(pathNode &prev);
    void   setValues(const Node &depot);

    ~pathNode(){};
};    

#endif
