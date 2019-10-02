#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool CheckPermutation(string& a, string& b) {
    if(a.size()!=b.size()) return false;
    
    // check the histgram of chars
    vector<int> hist_a(128, 0);
    vector<int> hist_b(128, 0);
    
    for(int i=0; i<a.size(); i++) {
        hist_a[a[i]] ++; hist_b[b[i]] ++;
    }
    
    if(hist_a==hist_b) return true;
    else return false;
};

// incremental histgram for string a, decremental for b
bool CheckPermutation_0(string& a, string& b) {
    if(a.size()!=b.size()) return false;
    int hist_a [128] = {0};
    for(int i=0; i<a.size(); i++) hist_a[a[i]] ++;
    for(int i=0; i<b.size(); i++) {
        hist_a[b[i]] --;
        if(hist_a[b[i]]<0) return false;
    }
    return true;
};

int main() {
    string a, b;
    cin >> a >> b;
    cout << "is permutation: " << CheckPermutation(a, b) << endl;
    cout << "is permutation: " << CheckPermutation_0(a, b) << endl;
    return 0;
}
