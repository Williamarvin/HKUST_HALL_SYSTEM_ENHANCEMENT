#include <iostream>
#include "Student.h"

using namespace std;

// TODO: Task 1.1
Student::Student(int sid,
                 const string& name,
                 const string& major,
                 bool isLocal,
                 int ECANum,
                 int travelFastest,
                 int travelCheapest,
                 bool isFirstApplication) 
                 
                 : sid(sid), name(name), major(major), isLocal(isLocal), ECANum(ECANum), travelCheapest(travelCheapest), travelFastest(travelFastest), isFirstApplication(isFirstApplication)
                 {
                    if(isLocal){
                        totalHallPoints = (travelCheapest + travelFastest) / 4 + ECANum * 5 + isFirstApplication * 5;
                    }
                    else{
                        totalHallPoints = 15 + isFirstApplication * 20 + ECANum * 5;
                    }
                    status = HallApplicationStatus::QUEUEING;
                 }

// TODO: Task 1.2
bool Student::operator==(int sid) const {
    if(this->sid == sid){
        return true;
    }
    return false;
}
