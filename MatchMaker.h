//
//  MatchMaker.h
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/7/22.
//

#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include "PersonProfile.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "provided.h"
#include "utility.h"

class MatchMaker {
public:
MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
~MatchMaker();
std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;

private:
const MemberDatabase* mdbptr;
const AttributeTranslator* atptr;
};


#endif
