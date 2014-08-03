
//#include <stdexcept>
//#include <algorithm>
//#include <iostream>
//#include <fstream>
#include <sstream>
//#include <string>
//#include <vector>
#include <list>
//#include <math.h>

#include "order.h"
#include "node.h"
#include "pathnode.h"
#include "path.h"


void Path::dump() {
    std::cout<<"depot:\n";
    depot.dump();
    if(twv_depot) std::cout<<"depot: has twv\n";
    if(cv_depot) std::cout<<"depot: has cv\n";

     for (int i=0;i<path.size();i++){
          std::cout<<"\npath stop #:"<<i<<"\n";
          path[i].dump();
     };
}     

    void Path::push_back(pathNode pathstop) {
         if (path.size()==0) pathstop.setValues(depot);
         else pathstop.setValues(path.back());
         path.push_back(pathstop);
         setDepotValues();
}

    void Path::emplace(pathNode pathstop,int at) {
/*         pathNode &prev= (at==0)? depot: path[at];        
         pathstop.setValues(prev);
         path.insert(path.begin()+at,pathstop);
         setvalues(at);
*/    }

    void Path::setvalues(int at){
         if (at<path.size()) {
              if (at==0) path[at].setValues(depot);
              else path[at].setValues(path[at-1]);
              setvalues(at+1);
         } else {
              setDepotValues();
         };
     }

     void Path::setDepotValues() {
              int at= path.size()-1;
              D = path[at].totDistFromDepot+depot.distance(path[at].node);
              twv_depot=depot.lateArrival(D);
              cv_depot=path[at].cv;
              TWV = path[at].twvTot;
              CV = path[at].cvTot;
              TWV = (twv_depot)? TWV+1:TWV;
              CV = (cv_depot)? CV+1:CV;
      }

