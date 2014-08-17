#ifndef NODE_H
#define NODE_H

#include <cmath>
#include <string>

class Node {
  protected:        //// should be private
    int nid;
    double x;
    double y;

  public:
    // accessors
    int getnid() const { return nid; };
    int getx() const { return x; };
    int gety() const { return y; };

    double distance(const Node &n) const {
        double dx = n.x - x;
        double dy = n.y - y;
        return sqrt( dx*dx + dy*dy );
    };

    void dump() const;

    // state
    bool isvalid() const { return nid > -1; };

    //// these 2 should be const ??
    bool isSamePos(const Node &n) const  { return distance(n) == 0; };
    bool isSamePos(const Node &n, double tol) const { return distance(n) < tol; };

    // mutators
    void set(int _nid, double _x, double _y) {
        nid = _nid;
        x = _x;
        y = _y;
    };

    void setnid(int _nid) { nid = _nid; };
    void setx(double _x) { x = _x; };
    void sety(double _y) {y = _y; };

    // operators
    bool operator<(const Node &n) const { return nid < n.nid; };
    bool operator==(const Node &n) const { return nid == n.nid && x == n.x && y == n.y; };
    bool operator!=(const Node &n) const { return ! (*this == n); };
    bool operator>(const Node &n) const { return nid > n.nid; };

    // structors

    Node() {
        nid = -1;
        x = 0.0;
        y = 0.0;
    };

    Node(int _nid, double _x, double _y) {
        nid = _nid;
        x = _x;
        y = _y;
    };

    Node(const std::string line);

    ~Node() {};

};

#endif
