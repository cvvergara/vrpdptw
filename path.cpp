
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



    void Path::removeOrder(int oid){
         removePickup(oid);
         removeDelivery(oid);
    }


    void Path::removePickup(int oid){
          for (int i=0;i<path.size();i++) {
               if (path[i].ispickup() and path[i].getoid()==oid ){
                   remove(i); break; //only 1 pickup per order
               }

         }
    }

    void Path::removeDelivery(int oid){
           for (int i=0;i<path.size();i++) {
               if (path[i].isdelivery() and path[i].getoid()==oid ){
                   remove(i); break; //only 1 delivery per order
               }
           }
    }      

    void Path::remove(int at){ 
          if (!path.empty()) path.erase(path.begin()+at);
    }
 

    void Path::push_back(pathNode pathstop) {
          path.push_back(pathstop);
          setvalues(0);
/*         if (path.size()==0) pathstop.setValues(*depot);
         else pathstop.setValues(path.back());
         path.push_back(pathstop);
         setDepotValues();*/
    }

    void Path::emplace(pathNode pathstop,int at) {
/*         pathNode &prev= (at==0)? depot: path[at];        
         pathstop.setValues(prev);
         path.insert(path.begin()+at,pathstop);
         setvalues(at);
*/    }

    void Path::setvalues(int at){
         if (at<path.size()) {
              if (at==0) path[at].setValues(*depot);
              else path[at].setValues(path[at-1]);
              setvalues(at+1);
         } else {
              setDepotValues();
         };
     }

     

     void Path::swapnodes(int i,int j){
          if(i>j)  std::cout<<"This is a restrictive swap, requierment: i<j\n";  
          else if (ispickup(i) and isdelivery(j) and sameorder(i,j)) std::cout<<"This is a restrictive swap, requierment: cant swap from the same order\n";
          else {
              pathNode temp(path[i]);
              path[i]=path[j];
              path[j]=temp;
              setvalues(i); //update values starting from i
              setvalues(0);
          }
     }

     void Path::swap(int i,int j){
          pathNode temp(path[i]);
          path[i]=path[j];
          path[j]=temp;
          if (i<j) setvalues(i);
          else setvalues(j);
          setvalues(0);
     }
                 

     void Path::setDepotValues() {
              int at= path.size()-1;
              D = path[at].totDistFromDepot+depot->distance(path[at].getnode());
              twv_depot=depot->lateArrival(D);
              cv_depot=path[at].cv;
              TWV = path[at].twvTot;
              CV = path[at].cvTot;
              TWV = (twv_depot)? TWV+1:TWV;
              CV = (cv_depot)? CV+1:CV;
      }


void Path::dump() {
    std::cout << "D="<<D << ", "
              << "TWV="<<TWV << ", "
              << "CV=" <<CV<< ", ";
    if(twv_depot) std::cout<<"depot: has twv ";
    if(cv_depot) std::cout<<"depot: has cv ";
     for (int i=0;i<path.size();i++){
          std::cout<<"\npath stop #:"<<i<<"\n";
          path[i].dump();
     };
}     



void Path::smalldump() {
    std::cout << "\nPath(nid,oid): [";
    for (int i=0; i<path.size(); i++) {
        if (i) std::cout << ", ";
        std::cout << "("<<getnid(i)<<","<<getoid(i)<<")";
    }
    std::cout << "]\n";
}
