//
//  AttributeTranslator.h
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/7/22.
//
#ifndef ATT_TRANSLATOR_H
#define ATT_TRANSLATOR_H

#include <string>
#include <vector>
using namespace std;
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator {
public:
AttributeTranslator();
~AttributeTranslator();
bool Load(std::string filename);
std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
//compatible Att Val pairs to be stored in one string with separators
RadixTree<std::vector<AttValPair>> rTrans;
// may need a private function to add new compatible AttVal pair to a source AttVal pair
// that already has a few compatible AttVal pairs
void addNew(std::string s, AttValPair& av);
};


#endif
