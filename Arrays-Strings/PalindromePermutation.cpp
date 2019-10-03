#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool PalindromePermutation(string& s) {
    // input string s is a sequence of words with spaces
    string word;
    stringstream ss(s);
    int hist_char [128] = {0};
    while(getline(ss, word, ' ')) {
        for(int i=0; i<word.size(); i++) {
            hist_char[word[i]] ++;
        }
    }
    // check the hist_char
    int odd_counts = 0;
    for(int i=0; i<128; i++) {
        if(hist_char[i]%2!=0) odd_counts++;
        if(odd_counts>1) return false;
    }
    return true;
};

int main() {
    string Line;
    getline(cin, Line);
    
    cout << "is palindrome permutation: " << endl;
    cout << PalindromePermutation(Line) << endl;
    return 0;
}
