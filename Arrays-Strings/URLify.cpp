#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void URLify (string& s, int true_len) {
    // move the string to the backend
    int str_len = s.size();
    for(int i=0; i<true_len; i++) {
        s[str_len-1-i] = s[true_len-1-i];
    }
    // start to replace spaces
    int idx = 0;
    for(int i=0; i<true_len; i++) {
        if(s[str_len-true_len+i]==' ') {
            s[idx++] = '%'; s[idx++] = '2'; s[idx++] = '0';
        } else {
            s[idx++] = s[str_len-true_len+i];
        }
    }
    // remove the backend chars
    for(int i=idx; i<s.size(); i++) s[i] = ' ';
};

void URLify_0(string& s, int true_len) {
    // count the number of spaces
    int space_num = 0;
    for(int i=0; i<true_len; i++){
        if(s[i]==' ') space_num++;
    }
    // starting from the backend
    int tail_idx = true_len+3*space_num-1;
    for(int i=0; i<true_len; i++) {
        if(s[true_len-1-i]==' ') {
            s[tail_idx--] = '0'; s[tail_idx--] = '2'; s[tail_idx--] = '%';
        } else {
            s[tail_idx--] = s[true_len-1-i];
        }
    }
    // remove the frontend chars
    for(int i=tail_idx; i>=0; i--) s[i] = ' ';
};

int main() {
    string Line;
    getline(cin, Line); // no return value for getline()
    stringstream ss(Line);
    
    string in_string;
    int true_len;
    
    string token;
    getline(ss, token, ',');
    in_string = token.substr(1, token.size()-2);
    getline(ss, token, ',');
    true_len = stoi(token);
    
    // URLify(in_string, true_len);
    URLify_0(in_string, true_len);
    cout << in_string << endl;
    return 0;
}
