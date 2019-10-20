// Qing

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char toChar(int num) {
    return '0'+num;
}

int toDigit(char d) {
    return d-'0';
}

// To let this function work properly,
// the two inputs should have the same digit length,
// and the number of digits per input should be a power of 2.
string IntMultiply(string x, string y) {
    int len_x = x.length();
    int len_y = y.length();
    // recursive calls
    if(len_x>1) {
        string x1 = x.substr(0, len_x/2);
        string x0 = x.substr(len_x/2);
        string y1 = y.substr(0, len_y/2);
        string y0 = y.substr(len_y/2);
        // multiply
        string x1y1 = IntMultiply(x1, y1);
        string x1y0 = IntMultiply(x1, y0);
        string x0y1 = IntMultiply(x0, y1);
        string x0y0 = IntMultiply(x0, y0);
        // addition
        x1y1.append(len_x, '0');
        x1y0.append(len_x/2, '0'); x1y0.insert(0, x1y1.length()-x1y0.length(), '0');
        x0y1.append(len_y/2, '0'); x0y1.insert(0, x1y1.length()-x0y1.length(), '0');
        x0y0.insert(0, x1y1.length()-x0y0.length(), '0');
        int c = 0; // c is for carry
        string result;
        for(int i=x1y1.length()-1; i>=0; i--) {
            int temp = c + toDigit(x1y1[i])+toDigit(x1y0[i])+toDigit(x0y1[i])+toDigit(x0y0[i]);
            c = temp/10;
            result.insert(0, 1, toChar(temp%10));
        }
        if(c>0) result.insert(0, 1, toChar(c));
        return result;
    } else {
        string result;
        int temp = stoi(x)*stoi(y);
        result = to_string(temp);
        return result;
    }
}

int main() {
    ifstream infile("in.txt");
    string x, y;
    infile >> x >> y;

    // integer multiply
    string ans = IntMultiply(x, y);

    ofstream outfile("out.txt");
    outfile << ans;

    return 0;
}

