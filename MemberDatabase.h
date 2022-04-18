//
//  MemberDatabase.h
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/7/22.
//

#ifndef MEMBER_DB_H
#define MEMBER_DB_H

#include <vector>
using namespace std;

#include "PersonProfile.h"

const int MAXL = 100;
const int MAXMEM = 100100;

class MemberDatabase {
public:
MemberDatabase();
~MemberDatabase();
bool LoadDatabase(std::string filename);
std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
const PersonProfile* GetMemberByEmail(std::string email) const;
//void printDB();

private:
int num_mem;
PersonProfile* ppptr_arr[MAXMEM];
//RadixTree<int> emailppRT;
RadixTree<PersonProfile*> emailppRT;
//RadixTree<std::string> attvalemailRT;
RadixTree<std::vector<std::string>> attvalemailRT;
void addNewEmail(std::string s, std::string c);
};


#endif
