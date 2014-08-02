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

    pathNode::setValues(const pathNode &prev) {
        setDistPrev(prev.node);
        totDistFromDepot=prev.totDistfromdepot + distPrev;
        twv=node.lateArrival(totDistFromDepot)
        if (node.earlyArrival(totDistFromDepot)) totDistFromDepot=node.tw_open;
        totDistFromDepot+=node.getServiceTime();
        cargo+=prev.cargo+node.getdemand();
        cv= cargo>cargolimit or cargo < 0;
        twvTot = (twv)?: prev.twvTot++:prev.twvTot;
        cvTot = (cv)?: prev.cvTot++:prev.cvTot;
    };

