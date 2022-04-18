//
//  main.cpp
//  CS32Project4-Unhinged
//
//  Created by Rohit Vivek Gore on 3/7/22.
//



#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
/*
const std::string MEMBERS_FILE    = "/Users/rohitgore/Documents/UCLA Classes/CS 32/CS32Project4-Unhinged/CS32Project4-Unhinged";
const std::string TRANSLATOR_FILE = "/Users/rohitgore/Documents/UCLA Classes/CS 32/CS32Project4-Unhinged";
*/

const std::string MEMBERS_FILE    = "/Users/rohitgore/Downloads/Unhinged/members.txt";
//const std::string MEMBERS_FILE = "/Users/rohitgore/Downloads/members_trunc.txt";
//const std::string TRANSLATOR_FILE = "translator.txt";

//const std::string MEMBERS_FILE = "members.txt";
const std::string TRANSLATOR_FILE = "/Users/rohitgore/Downloads/translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at));

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty()) return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}


/*
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
#include <fstream>
#include "RadixTree.h"
#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"


const std::string MEMBERS_FILE    = "/Users/rohitgore/Documents/UCLA Classes/CS 32/CS32Project4-Unhinged/CS32Project4-Unhinged/members.txt";
const std::string MEMBERS_FILEX    = "/Users/rohitgore/Downloads/members_trunc.txt";

const std::string TRANSLATOR_FILE = "/Users/rohitgore/Documents/UCLA Classes/CS 32/CS32Project4-Unhinged/translator.txt";
const std::string TRANSLATOR_FILEX = "/Users/rohitgore/Downloads/translator.txt";

int main()
{
//ofstream outf("error.txt");
    bool fload;

MemberDatabase mdb;
 fload = mdb.LoadDatabase(MEMBERS_FILEX);
if (fload) cerr << "Database Loaded" << endl;
else cerr << "Database load failed" << endl;
//mdb.printDB();
    AttributeTranslator atr;
    cerr << "Going to load translator" << endl;
    fload = atr.Load(TRANSLATOR_FILEX);
    if (fload) cerr <<"Translator Loaded" << endl;
    else cerr << "Translator load failed" << endl;

    
const PersonProfile* pp = mdb.GetMemberByEmail("MHa7@sky.com");

if (pp == nullptr) cerr << "Did not find" << endl;
else cerr << pp->GetName() << endl;

MatchMaker mm = MatchMaker(mdb, atr);

//cerr << "Got here" << endl;
std::vector<EmailCount> v = mm.IdentifyRankedMatches("LWall@sky.com", 2);

//cerr << "Also got here" << endl;

std::vector<EmailCount>::iterator it;

for (it = v.begin(); it < v.end(); it++)
cerr << (*it).email << " " << (*it).count << endl;


return 0;
}

*/
