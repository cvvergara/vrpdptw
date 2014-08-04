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
private:
    Node *node;
public:
static const double cargoLimit=100; //need to set this data
    bool twv;
    bool cv;
    int twvTot;
    int cvTot;
    double cargo;
    double distPrev;
    double totDistFromDepot;

    Node& getnode(){return *node;};
    bool ispickup() const {return node->ispickup();}
    bool isdepot() const {return node->isdepot();}
    bool isdelivery() const {return node->isdelivery();}
    bool sameorder(pathNode &n) const {return node->sameorder(n.getnode());}
    int getnid() {return node->getnid();}
    int getoid() {return node->getoid();}

    


    void dump() {
        node->dump();
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
              node=other.node;
              twv=other.twv;
              cv=other.cv;
              twvTot=other.twvTot;
              cvTot=other.cvTot;
              cargo=other.cargo;
              distPrev=other.distPrev;
              totDistFromDepot=other.totDistFromDepot;
             };

   pathNode(Node &n) {
              node=&n;
              twv=false;
              cv=false;
              twvTot=0;
              cvTot=0;
              cargo=0;
              distPrev=0;
              totDistFromDepot=0;
    };
    pathNode(const pathNode &other):node(other.node) {
              copyvalues(other);
     };
    pathNode& operator=(const pathNode &other) {
              copyvalues(other);
     };        

    double setDistPrev(const Node &prev) {
          distPrev=node->distance(prev);
   };
    double getDistFromStop(pathNode &other) {return node->distance(other.getnode());};
    void   setValues(pathNode &prev);
    void   setValues(const Node &depot);

    ~pathNode(){};
};    

#endif
