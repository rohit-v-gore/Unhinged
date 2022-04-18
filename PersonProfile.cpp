//
//  PersonProfile.cpp
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/7/22.
//

#include <iostream>
#include <string>

using namespace std;
#include "PersonProfile.h"

PersonProfile::PersonProfile(std::string name, std::string email) {
personName = name; personEmail = email; numpairs = 0;
}

PersonProfile::~PersonProfile() {}

std::string PersonProfile::GetName() const {return personName;}

std::string PersonProfile::GetEmail() const {return personEmail;}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
std::string att = attval.attribute;
std::string val = attval.value;
AttValPair* p;
//AttValPair pnew;
std::string s = att + "," + val; //use a comma separator and insert entire string in tree

// first use search to see if s is already present
p = pprt.search(s);
if (p != nullptr) { //found a pair so just modify it
//   p->attribute = att;
//   p->value = val;
} else { //do an insert, update number of pairs, update matrix

pprt.insert(s, attval);
//find pointer to new AttValPair
p = pprt.search(s);
avpairPtr[numpairs] = p;
numpairs++;
//cerr << s << " " << numpairs << endl;
}
}

int PersonProfile::GetNumAttValPairs() const {return numpairs;}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
if (attribute_num < 0 || attribute_num >= numpairs) return false;
else {attval.attribute = avpairPtr[attribute_num]->attribute;
      attval.value = avpairPtr[attribute_num]->value;
      return true;}
}
