//
//  MemberDatabase.cpp
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/7/22.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "provided.h"
using namespace std;


MemberDatabase::MemberDatabase() {
num_mem = 0;
for (int i = 0; i < MAXMEM; i++) ppptr_arr[i] = nullptr;
}

MemberDatabase::~MemberDatabase() {}

void MemberDatabase::addNewEmail(std::string s, std::string em) {
std::vector<std::string> v;
std::vector<std::string>* vp;
std::vector<std::string>::iterator it;

bool found = false;
vp = attvalemailRT.search(s);

if (vp) {
   for (it = vp->begin(); it < vp->end(); it++)
      if (*it == em) {found = true; break;} // email already exists
   if (!found ) {vp->push_back(em);} //email does not exist, so add
} else { // insert new vector
   v.push_back(em);
   attvalemailRT.insert(s, v);
}
}

bool MemberDatabase::LoadDatabase(std::string filename)
// read data for each member, create person profile instance
// ignore duplicate AttVal pairs
// enter email address and person profile in emailppRT
// for each AttValPair encountered, build a string of email addresses separated by #
{

ifstream memfile(filename);
if (!memfile) {cerr << "Member file not found, exiting ..." << endl; return false;}

//char name[MAXL], email[MAXL], numtraits[MAXL], attval[MAXL], bline[MAXL];
std::string line, name, name_s, email_s, numtraits_s, attval, attval_s, bline_s, att, val;
size_t numt, len;
size_t pos;
AttValPair av;
size_t k;

int i_mem = 0; //index to track members as they are read
//memfile.open(filename);
// put some code for checking
//if (memfile.eof()) {cerr << "Member file is empty, exiting ..." << endl; return false;}
while (!memfile.eof()) { // idea is to get one member at a time
   getline(memfile, line);
   for (k = 0; k < line.length(); k++) if (line[k] <= 32) line[k] = '#'; //hack for windows .txt files
   istringstream ss1(line);
   ss1 >> name;
   
   k = name.length();
   if (name[k-1] == '#') k--;
   for (int i = 0; i < k; i++) if (name[i] == '#') name[i] = ' ';;
   name_s = name.substr(0, k);

   //cerr << name_s << " ";
   getline(memfile, line);
   stringstream ss2(line);
   ss2 >> email_s;
   getline(memfile, line);
   stringstream ss3(line);
   ss3 >> numtraits_s;

   numt = 0;
   for (int i = 0; i < numtraits_s.length(); i++)
      {numt = 10*numt + (numtraits_s[i] - '0');}

   num_mem++;
   ppptr_arr[i_mem] = new PersonProfile(name_s, email_s);


//   emailppRT.insert(email_s, i_mem); //store index in tree
     emailppRT.insert(email_s, ppptr_arr[i_mem]);

   for (int i = 0; i < numt; i++) { // read each trait one by one and insert in both trees
      getline(memfile, line);
      for (k = 0; k < line.length(); k++) if (line[k] <= 32) line[k] = '#'; //hack for windows .txt files
      istringstream ss4(line);
      ss4 >> attval;
   
      k = attval.length();
      if (attval[k-1] == '#') k--;
      for (int j = 0; j < k; j++) if (attval[j] == '#') attval[j] = ' ';;
      attval_s = attval.substr(0, k);

      len = attval_s.length();
      pos = attval_s.find(','); // find the comma in the pair
      if (pos != std::string::npos) {// comma found so break into individual

         addNewEmail(attval_s, email_s);// need to build string of emails separated by # not just insert
         att = attval_s.substr(0, pos);
         val = attval_s.substr(pos+1, len-pos-1);
         av.attribute = att;
         av.value = val;

         ppptr_arr[i_mem]->AddAttValPair(av); // add the attribute value pair to the person profile
      }
      else {cerr << "Found illegal AttVal Pair, exiting ..." << endl; return false;}
   }

   i_mem++; //increment index
//do an extra getline for the blank line
   getline(memfile, bline_s); // can put code in here to confirm it is a blank line
}
return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
std::vector<std::string> v;
std::string s1 = input.attribute;
std::string s2 = input.value;
std::vector<std::string>* vp = attvalemailRT.search(s1+","+s2); // search for comma separated att val pair
if (vp != nullptr) v = *vp;
return v;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const {

PersonProfile* *pp;
if ((pp = emailppRT.search(email)) == nullptr) return nullptr;


else return *pp;
}


