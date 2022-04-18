#include "AttributeTranslator.h"

#include <fstream>
#include <sstream>

AttributeTranslator::AttributeTranslator() {}

AttributeTranslator::~AttributeTranslator() {}

void AttributeTranslator::addNew(std::string s, AttValPair& av) {
vector<AttValPair> v;
vector<AttValPair>* avvec = rTrans.search(s);
if (avvec) {
avvec->push_back(av); // even allow duplicates
} else {
// insert since not found
v.push_back(av);
rTrans.insert(s,v);
}
}

bool AttributeTranslator::Load(std::string filename) {
//read each line, assume each line has exactly three commas
//split string around seconds comma, add # at end of right half and use addNew
ifstream trfile(filename);

std::string line, line_t, line_s, attval1, attval2, att, val;
AttValPair av;
size_t len, count, k;
size_t pos;
//cerr << "Created filestream" << endl;
if (!trfile) {cerr << "Could not open Attribute Translator file, exiting ..." << endl; return false;}
if (trfile.eof() != 0) {cerr << "Translator file is empty, exiting ..." << endl; return false;}
while (!trfile.eof()) { // idea is to get one translator pair at a time

 getline(trfile, line);
   for (k = 0; k < line.length(); k++) if (line[k] <= 32) line[k] = '#';
   istringstream ss(line);
   ss >> line_t;
   
   k = line_t.length();
   if (line_t[k-1] == '#') k--;
   for (size_t i = 0; i < k; i++) if (line_t[i] == '#') line_t[i] = ' ';;
   line_s = line_t.substr(0, k);

   len = line_s.length();
   if (len == 0) continue; // to cater to last blank line
   count = 0;
   for (size_t i = 0; i < len; i++) if (line_s[i] == ',') count++;
   if (count != 3) {cerr << "Line not properly formatted" << endl; return false;}
   //look for second comma
   pos = line_s.find(',', 0);
   pos = line_s.find(',', pos+1);
   attval1 = line_s.substr(0, pos);
   attval2 = line_s.substr(pos+1, len-pos-1);
// parse aatval2 and create AttValPair to add
   pos = attval2.find(',',0);
   len = attval2.length();
   att = attval2.substr(0, pos);
   val = attval2.substr(pos+1, len-pos-1);
   av.attribute = att;
   av.value = val;
   addNew(attval1, av);
}
//cerr << "Translator loaded" << endl;
return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
std::vector<AttValPair> v; // create empty vector

//have to read the compatible string for the source value if any and convert to vector of AttVal pairs
std::string s, c, s1, s2, c1, c2;
//AttValPair av;
std::vector<AttValPair>* vp;
std::vector<AttValPair>::iterator it;
s1 = source.attribute;
s2 = source.value;
s = s1 + "," + s2;
vp = rTrans.search(s);

if (vp != nullptr) //add attvalpairs to vector
   for (it = vp->begin(); it < vp->end(); it++) {
      //cerr << (*it).attribute << " " << (*it).value << endl;
      v.push_back(*it);
   }
else {cerr << "Source attvalpair not found " << s << endl;}
return v; // empty if no compatible pairs found
}

