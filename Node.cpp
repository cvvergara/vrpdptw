#include <sstream>
#include "Node.h"

Node::Node(std::string line) {
        std::istringstream buffer( line );
        buffer >> nid;
        buffer >> x;
        buffer >> y;
        buffer >> demand;
        buffer >> tw_open;
        buffer >> tw_close;
        buffer >> service;
        buffer >> pid;
        buffer >> did;
}

bool Node::checkIntegrity(int nodesCant) {
     bool flag=true;
     if (pid<0 or pid>nodesCant) {
        std::cout << "Order["<<nid<<"]: pickup id out of range:"<<pid<<"expected in [0,"<<nodesCant<<"] \n";
        flag=false;}
     if (did<0 or did>nodesCant) {
        std::cout << "Order["<<nid<<"]: pickup id out of range:"<<did<<"expected in [0,"<<nodesCant<<"] \n";
        flag=false;}
     return flag;
}


void Node::dump() {
    std::cout << nid << ", "
              << x << ", "
              << y << ", "
              << demand << ", "
              << tw_open << ", "
              << tw_close << ", "
              << service << ", "
              << pid << ", "
              << did << std::endl;
}
