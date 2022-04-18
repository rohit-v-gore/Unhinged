//
//  utilities.hpp
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/8/22.
//

#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include <map>
#include "provided.h"

void NoDupInsert(std::vector<AttValPair>& v, AttValPair av);
bool GTEmailCount(const EmailCount& lhs, const EmailCount& rhs);
bool EQEmailCount(const EmailCount& lhs, const EmailCount& rhs);
void AddUpdate(std::vector<EmailCount>& v, std::string email);
void AddUpdateMap(std::map<std::string,int>& v, std::string email);
void swapEmailCount(EmailCount& lhs, EmailCount& rhs);

#endif
