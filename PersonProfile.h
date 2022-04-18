//
//  PersonProfile.h
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/7/22.
//

#ifndef PERPROF_H
#define PERPROF_H

#include <iostream>
#include <string>

using namespace std;
#include "provided.h"
#include "RadixTree.h"

const int MAX_ATTVAL_PAIRS = 100;

class PersonProfile {
public:
PersonProfile(std::string name, std::string email);
~PersonProfile();
std::string GetName() const;
std::string GetEmail() const;
void AddAttValPair(const AttValPair& attval);
int GetNumAttValPairs() const;
bool GetAttVal(int attribute_num, AttValPair& attval) const;

private:
std::string personName;
std::string personEmail;
int numpairs;
RadixTree<AttValPair> pprt;
AttValPair* avpairPtr[MAX_ATTVAL_PAIRS]; //used to point to elements as they are inserted to facilitate GetAttVal
};

#endif
