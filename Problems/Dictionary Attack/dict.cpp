/*
    Author: William Sid (wilsi748)

    Problem solved: Problem B, Dictionary Attack
*/
#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 26;

class TrieNode {
public:
    map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

// Insert a word into the Trie
void insert_word(TrieNode* root, string& word) {
    TrieNode* current = root;
    for (char c : word) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->isEndOfWord = true;
}

// Check if a word exists in the Trie
bool find_word(string& word, TrieNode* root) {
    TrieNode* current = root;
    for(char c : word) {
        if (current->children.find(c) == current->children.end()) {
            return false;
        }
        current = current->children[c];
    }
    return current->isEndOfWord;
}

// Check if a password is not acceptable
bool check_password(string password, TrieNode* root, int changes = 0) {
    if (find_word(password, root)) return true;

    if (changes > 3) return false; 

    for(int i = 0; i < password.size(); i++) {
        // Replace digit with character 
        if (isdigit(password[i])) {
            for (char c = 'a'; c <= 'z'; c++) {
                string modified = password;
                modified[i] = c;
                if(check_password(modified, root, changes + 1)) {
                    return true;
                }
            }
            for (char c = 'A'; c <= 'Z'; c++) {
                string modified = password;
                modified[i] = c;
                if(check_password(modified, root, changes + 1)) {
                    return true;
                }
            }
        }

        // Transpose
        if (i + 1 < password.size()) {
            string modified = password;
            swap(modified[i], modified[i+1]);
            if(check_password(modified, root, changes + 1)) {
                return true;
            }
        }
    }
    
    return false;
}




/*
bool contains_string(string s, set<string>& passwords) {
    return passwords.find(s) != passwords.end();
}


void generatePasswords(string password, set<int>& passwords, int changes = 0) {
    passwords.insert(get_ascii(password));
    
    if(changes == 3) return;

    int n = password.size();

    // replace any one character with a digit
    for(int i = 0; i < n; i++) {
        for(char digit = '0'; digit <= '9'; digit++) {
            string newPassword = password;
            if (newPassword[i] != digit) {
                newPassword[i] = digit;
                generatePasswords(newPassword, passwords, changes + 1);
            }
        }
    }
    
    
    // transpose 
    for (int i = 0; i < n - 1; i++) {
        string newPassword = password;
        swap(newPassword[i], newPassword[i+1]);
        generatePasswords(newPassword, passwords, changes + 1);
    }
}
*/
bool too_many_digits(string s) {
    int count = 0;
    for(char c : s) {
        if(isdigit(c)) count++;
    }
    return count > 3;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    TrieNode* root = new TrieNode();

    //set<int>passwords;
    //set<string> dict;
    
    for(int i = 0; i < n; i++) {
        string word;
        cin >> word;
        //dict.insert(word);
        //generatePasswords(word, passwords);
        insert_word(root, word);
    }
    
    string pw;
    
    while(cin >> pw) {
        if(too_many_digits(pw)) {
            cout << pw << endl;
        } else if(!check_password(pw, root)) {
            cout << pw << endl;
        }
    }

    return 0;
}