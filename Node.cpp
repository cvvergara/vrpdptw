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
