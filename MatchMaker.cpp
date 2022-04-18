//
//  MatchMaker.cpp
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/7/22.
//

#include "MatchMaker.h"
#include <map>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) {
mdbptr = &(mdb);
atptr = &(at);
}

MatchMaker::~MatchMaker() {}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const {
//for member with email, find their attribute value pairs
//use GetAttVal to retrieve pairs one by one
//for each pair, find matching pairs from translator
//build a list without duplicates
//find members who have at least the threshold number of matching pairs, use the email count struct
//can build a list of all members first and then erase the once with smaller than threshold
//also have to sort in descending order of count and ascending order of email address

std::vector<EmailCount> v;
std::map<string, int> m;
std::map<std::string, int>::iterator itm;
std::string temps;

const PersonProfile* pp;
if ((pp = mdbptr->GetMemberByEmail(email)) == nullptr) cerr << "Person not found" << endl;
else {
AttValPair av;
std::vector<AttValPair> allpairs; //build all compatible pairs
std::vector<AttValPair>::iterator it; //iterator

int num = pp->GetNumAttValPairs();
bool found;

std::vector<AttValPair> compv; //compatible pairs

for (int i = 0; i < num; i++) {
   found = pp->GetAttVal(i, av); // retrieve ith pair in av

   if (!found) {cerr << "Should have found but did not, error condition" << endl; exit(1);}
   //now find vector of compatible pairs using FindCompatibleAttValPairs from AttributeTranslator
   compv = atptr->FindCompatibleAttValPairs(av);
   // ensure vector is not empty
   if (compv.size() == 0) {cerr << "Found an empty vector of compatible pairs, not good" << endl;}
   else {
   for (it = compv.begin(); it < compv.end(); it++) // for each pair do NoDupInsert in allpairs
       {NoDupInsert(allpairs, (*it));}
   }
} // for

//cerr << "Found all compatible pairs for " << pp->GetName() << endl;

// now allpairs has all matching pairs with no duplicates
// for each pair, find all matching members using FindMatchingMembers from MemberDatabase
// this returns a vector of email addresses
std::vector<std::string> emvec;
std::vector<std::string>::iterator emit;
AttValPair avp;
for (it = allpairs.begin(); it < allpairs.end(); it++) {

   avp = (*it);

   emvec = mdbptr->FindMatchingMembers(*it);

   //j = 0;
   for (emit = emvec.begin(); emit < emvec.end(); emit++)
      if ((*emit) != email) {

//         AddUpdate(v, (*emit)); // do not include own email
         AddUpdateMap(m, (*emit)); // do not include own email
      }
}

//Now build vector from map
for (itm = m.begin(); itm != m.end(); itm++) {
struct EmailCount *emc = new EmailCount(itm->first, itm->second);
v.push_back(*emc);
}

//now remove those below threshold
std::vector<EmailCount>::iterator ecv;
ecv = v.begin();
while (ecv != v.end()) {
if ((*ecv).count < threshold) ecv = v.erase(ecv);
else ecv++;
}

    std::sort(v.begin(), v.end(), GTEmailCount);
} // else
return v;
}
