#include <sstream>
#include "node.h"

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
        if (nid==0) dist=0;
        oid =-1;
        order=NULL;
}

bool Node::checkIntegrity(int nodesCant) {
     bool flag=true;
     if (pid<0 or pid>nodesCant) {
        std::cout << "Node["<<nid<<"]: pickup id out of range:"<<pid<<"expected in [0,"<<nodesCant<<"] \n";
        flag=false;}
     if (did<0 or did>nodesCant) {
        std::cout << "Node["<<nid<<"]: pickup id out of range:"<<did<<"expected in [0,"<<nodesCant<<"] \n";
        flag=false;}
     if (ispickup() and demand<0) {
        std::cout << "Node["<<nid<<"]: Marked as pickup with a demand of a delivery\n";
        flag=false;}
     if (isdelivery() and demand>0) {
        std::cout << "Node["<<nid<<"]: Marked as delivery with a demand of a pickup\n";
        flag=false;}
     return flag;
}


void Node::dump()const {
    std::cout << nid << ", "
              << x << ", "
              << y << ", "
              << dist<<", "
              << demand << ", "
              << tw_open << ", "
              << tw_close << ", "
              << service << ", "
              << pid << ", "
              << did << ","
              << getoid() << std::endl;
}

