#ifndef PATH_H
#define PATH_H

//#include <stdexcept>
//#include <algorithm>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
//#include <math.h>

#include "Order.h"
#include "Node.h"
//#include "Problem.h"

class pathNode {
public:
    Node& node;
    Order& order;
    double cargoLimit;
    bool twv;
    bool cv;
    int twvTot;
    int cvTot;
    double cargo;
    double distPrev;
    double totDistFromDepot;
    pathNode(){};
    pathrNnode(Node &n): node(n) {} ;
    pathrNnode(Node &n,Order &o): node(n); order(o) {} ;
    pathrNnode(Node &n,Order &o, const pathNode &prev): node(n); order(o) { setvalues(prev);};
//    pathNode &operator = (const pathNode &p) {node=p.node; order=p.order,distPrev=-1,totDistFromDepot=-1;};
    getDistFromStop(pathNode &other) {return node.distance(other.node)};
    setValues(const pathNode &prev);

    ~pathNode(){};
private:
    setDistPrev(Node &prev) {distPrev=node.distance(prev);};
}    

#endif
