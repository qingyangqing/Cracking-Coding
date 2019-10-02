#include <iostream>
#include <string>

using namespace std;

// O(n^2)
bool isUnique (string& s) {
    // only 128 chars in ASCII
    if(s.size()>=128) {
        return false;
    }
    //
    for(int i=0; i<s.size()-1; i++) {
        for(int j=i+1; j<s.size(); j++) {
            if(s[j]==s[i]) {
                return false; break;
            }
        }
    }
    return true;
};

// O(n)
bool isUnique_0 (string& s) {
    // only 128 chars
    if(s.size()>=128) return false;
    //
    bool flags [128] = {false};
    for(int i=0; i<s.size(); i++) {
        if(flags[s[i]]==false) {
            flags[s[i]] = true;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    string input_s;
    cin >> input_s;
    cout << input_s << endl;
    cout << "is unique: " << isUnique(input_s) << endl;
    cout << "is unique: " << isUnique_0(input_s) << endl;
    return 0;
}
