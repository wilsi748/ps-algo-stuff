#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

bool isPlaceholder(string one) {
    if((one.find("<")!=std::string::npos) && (one.find(">")!=std::string::npos))
    {
        return true;
    }
    return false;
}

void checkForPlaceholders(vector<string> pattern1, vector<string> pattern2) 
{
    for (int i = 0; i < pattern1.size(); i++) 
    {
        if(isPlaceholder(pattern1[i]) && !isPlaceholder(pattern2[i]))
        {
            string word = pattern1[i];
            string sub = pattern2[i];
            for (int j = 0; j < pattern1.size(); j++) {
                if (pattern1[j] == word) {
                    pattern1[j] = sub;
                }
            }
            return checkForPlaceholders(pattern1, pattern2);
        }
        if(!isPlaceholder(pattern1[i]) && isPlaceholder(pattern2[i]))
        {
            string word = pattern2[i];
            string sub = pattern1[i];
            for (int j = 0; j < pattern2.size(); j++) {
                if (pattern2[j] == word) {
                    pattern2[j] = sub;
                }
            }
            return checkForPlaceholders(pattern1, pattern2);
        }
    }
    for (int i = 0; i < pattern1.size(); i++) 
    {
        if(isPlaceholder(pattern1[i]) && isPlaceholder(pattern2[i]))
        {
            
            for (int j = 0; j < pattern1.size(); j++) {
                if (pattern1[j] == pattern1[i]) {
                    pattern1[j] = "abc";
                }
            }
            
            for (int j = 0; j < pattern2.size(); j++) {
                if (pattern2[j] == pattern2[i]) {
                    pattern2[j] = "abc";
                }
            }
            return checkForPlaceholders(pattern1, pattern2);
        }
    }
    string output = "";
    string p1;
    string p2;
    
    for (int i = 0; i < pattern1.size(); i++) {
        p1 = p1 + pattern1[i] + " ";
        p2 = p2 + pattern2[i] + " ";
    }

    if(p1 == p2) {
        output = p1;
    }else{
        output = "- ";
    }
    output.pop_back();

    cout << output << endl;
}

int main(void) {
    string test_cases;
    int tests;
    string output;

    getline(cin, test_cases);
    tests = stoi(test_cases);

    for(int i = 0; i < tests; i++)
    {
        string line;
        getline(cin, line);
        
        string temp;
        stringstream str_strm(line);
    
        vector<string> pattern1;
        while(str_strm >> temp)
        {
            pattern1.push_back(temp);
        }
        
        string line2;
        getline(cin, line2);
        
        string temp2;
        stringstream str_strm1(line2);
    
        vector<string> pattern2;
        while(str_strm1 >> temp2)
        {
            pattern2.push_back(temp2);
        }
        
        if(pattern1.size() != pattern2.size())
        {
            cout << "-" << endl;
            continue;
        }
        checkForPlaceholders(pattern1, pattern2);
        
        }
    return 0;
}