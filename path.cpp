
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
              std::cout<<"\nSwaping ("<<i<<","<<j<<")!";
              pathNode temp(path[i]);
              path[i]=path[j];
              path[j]=temp;
              setvalues(i); //update values starting from i
              setvalues(0);
          }
     }

     void Path::swap(int i,int j){
          std::cout<<"\nReSwaping ("<<i<<","<<j<<")";
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

     bool Path::findImprovment(int i) {
               double oldcost= getcost();
               bool improved=false;
               std::cout<<"\nWorking with ("<<i<<")\n";
               if (isdepot(i)) {
                    std::cout<<"Node is depot\n";
                    return false;}
               for (int j=i+1; j<path.size(); j++) {
                   std::cout<<"\nWorking with ("<<i<<","<<j<<") ";
                   if (ispickup(i) and isdelivery(j) and sameorder(i,j)) {  //poner dentro del for
                           std::cout<<"Node"<<i<<" is pickup and Node"<<j<<" is delivery from the same order \n";
                           return false;} //getting out from the j loop (pickup caatched up with delivery)
                   else {
                       swapnodes(i,j);
                       std::cout<<"costs (new,old) ("<<getcost()<<","<<oldcost<<")\n";
                       if (getcost()<oldcost) { return true;  //path has being improved
                              std::cout<<"New cost is better\n";}
                       else { swap(i,j);
                              std::cout<<"costs (old,restored) ("<<oldcost<<","<<getcost()<<")\n";
                            }
                   }
                }
              return false;
      }
   

      void Path::hillClimbOpt() {
           double original=getcost();
           double oldcost;
           std::cout<<"\nHILL\n";
           int i=0;
           while (i<path.size()-1) {
              if (!findImprovment(i)) i++;
              else i=0;
           }
           /*
           for (int i=0;  i<path.size()-1; i++) {
              findImprovment(i)
               std::cout<<"\nWorking with ("<<i<<")\n";
                 if (isdepot(i)) {
                    std::cout<<"Node is depot\n";
                    continue;}
               oldcost= getcost();
               improved=false;
               for (int j=i+1; j<path.size() and !improved; j++) {
                   std::cout<<"\nWorking with ("<<i<<","<<j<<") ";
                   if (ispickup(i) and isdelivery(j) and sameorder(i,j)) {  //poner dentro del for
                           std::cout<<"Node"<<i<<" is pickup and Node"<<j<<" is delivery from the same order \n";
			   j=path.size();} //getting out from the j loop (pickup caatched up with delivery)
                   else {
                       swapnodes(i,j); 
                       std::cout<<"costs (new,old) ("<<getcost()<<","<<oldcost<<")\n";
                       if (getcost()<oldcost) {improved=true;  //geting out of the j loop (path has being improved
                              std::cout<<"New cost is better\n";}
                       else { swap(i,j);
                              std::cout<<"costs (old,restored) ("<<oldcost<<","<<getcost()<<")\n";
                            }                  
                   }
               }*/
            
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
