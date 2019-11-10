// Qing

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    ifstream infile("Median.txt");

    // min_half's element number is (num_elements/2) or (num_elements/2+1), 
    // and max_half stores the others
    vector<int> min_half; // max heap
    vector<int> max_half; // min heap

    int sum_medians;
    int val1, val2;
    infile >> val1 >> val2;
    if(val1<val2) {
        min_half.push_back(val1); max_half.push_back(val2);
        sum_medians = val1*2;
    } else {
        min_half.push_back(val2); max_half.push_back(val1);
        sum_medians = val1+val2;
    }

    int val;
    while(infile>>val) {
        // insert the val into heaps
        if(val<min_half[0]) {
            min_half.push_back(val);
            push_heap(min_half.begin(), min_half.end(), less<int>());
        } else {
            max_half.push_back(val);
            push_heap(max_half.begin(), max_half.end(), greater<int>());
        }
        // balance the two heaps
        if(min_half.size()<max_half.size()) { // if max_half has more elements
            pop_heap(max_half.begin(), max_half.end(), greater<int>());
            min_half.push_back(max_half.back());
            max_half.pop_back();
            push_heap(min_half.begin(), min_half.end(), less<int>());
        }
        if(min_half.size()>max_half.size()+1) { // if min_half has more elements
            pop_heap(min_half.begin(), min_half.end(), less<int>());
            max_half.push_back(min_half.back());
            min_half.pop_back();
            push_heap(max_half.begin(), max_half.end(), greater<int>());
        }

        sum_medians += min_half[0];
    }

    cout << sum_medians%10000 << endl;

    return 0;
}

