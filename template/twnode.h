#ifndef VTWNODE_H
#define VTWNODE_H
#include <stdexcept>
#include <math.h>

#include <iostream>
#include "node.h" 

//class Order;

class Twnode: public Node {
protected:
    int demand;     // capacity demand
    int tw_open;    // earliest window time
    int tw_close;   // latest window time
    int service;    // service time

  public:
    int opens() const {return tw_open;};
    int closes() const {return tw_close;};
    double getdemand() const{ return demand;};
    double getservicetime() const{  return service;};
    int windowlength() const { return  tw_close - tw_open; };
/*state functions***/
    bool checkintegrity() const;
    bool earlyarrival(double D) const { return D < tw_open;};
    bool latearrival(double D) const { return D > tw_close;};

    bool hasdemand() const { return demand>0; };
    bool hassupply() const { return demand<0; };
    bool hasnogoods() const { return demand==0; };
/*print gunctions***/
    void dump() const;
    void debugdump() const;
    void setvalues(int _nid, double _x, double _y, int _demand,
                   int _tw_open, int _tw_close, int _service);

/* operators */



/*constructors and destructors */
    Twnode() {
        Node();
        demand = 0;
        tw_open = 0;
        tw_close = 0;
        service = 0;
    };
    Twnode(const Twnode &tw):Node(tw){
        demand = tw.demand;
        tw_open = tw.tw_open;
        tw_close = tw.tw_close;
        service = tw.service;
    };

    Twnode(const Node &n):Node(n) {
        demand = 0;
        tw_open = 0;
        tw_close = 0;
        service = 0;
    };
    Twnode(int nid,double x, double y):Node(nid,x,y) {
        demand = 0;
        tw_open = 0;
        tw_close = 0;
        service = 0;
    };

    Twnode(std::string line) ;
    ~Twnode() {};

};

#endif
