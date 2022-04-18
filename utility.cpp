//
//  utilities.cpp
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/8/22.
//


#include "utility.h"

void NoDupInsert(std::vector<AttValPair>& v, AttValPair av) {
// insert a new pair in a vector if not already present, use ==, != defined for AttValPair
AttValPair avp = AttValPair(av.attribute, av.value);
std::vector<AttValPair>::iterator it; //iterator
bool found = false;
for (it = v.begin(); it < v.end(); it++) {
if ((*it) == avp) {found = true; break;}
}
if (!found) v.push_back(avp);
}

bool EQEmailCount(const EmailCount& lhs, const EmailCount& rhs) {
return (lhs.count == rhs.count && lhs.email == rhs.email);
}

bool GTEmailCount(const EmailCount& lhs, const EmailCount& rhs) {
return (lhs.count > rhs.count || (lhs.count == rhs.count && lhs.email < rhs.email));
}

void swapEmailCount(EmailCount& lhs, EmailCount& rhs) {
int tempn;
std::string temps;
      tempn = lhs.count;
      lhs.count = rhs.count;
      rhs.count = tempn;
      temps = lhs.email;
      lhs.email = rhs.email;
      rhs.email = temps;
}

void AddUpdate(std::vector<EmailCount>& v, std::string email) {
//if email is not in vector add new element with count as 1, else increment count for existing email
//also maintain sorted order
std::vector<EmailCount>::iterator it;
std::string temps;
bool found = false;
int i = 0;
size_t j;
for (it = v.begin(); it < v.end(); it++) {
if ((*it).email == email) {found = true; (*it).count = (*it).count + 1; break;}
else i++;
}
if (found)
   while (i > 0 && GTEmailCount(v[i], v[i-1])) {
      swapEmailCount(v[i], v[i-1]);
      i--;
   }
else { // not found so insert
struct EmailCount* ec = new EmailCount(email, 1);
v.push_back(*ec);
j = v.size() - 1;
while (j > 0 && GTEmailCount(v[j], v[j-1])) {
      swapEmailCount(v[j], v[j-1]);
      j--;
}
}
}

void AddUpdateMap(std::map<std::string, int>& m, std::string email) {
//if email is not in map add new element with count as 1, else increment count for existing email
//also maintain sorted order
std::map<std::string, int>::iterator it;

int j;
it = m.find(email);
if (it == m.end()) m.insert(std::pair<std::string,int>(email,1));
else {
   j = it->second;
   m.erase(it);
   m.insert(std::pair<std::string,int>(email,j+1));
}
}
