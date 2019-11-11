// Qing

#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

int main () {
    ifstream infile("algo1-programming_prob-2sum.txt");
    //ifstream infile("in.txt");
    vector<long> num_list;
    long val;
    while(infile>>val) {
        num_list.push_back(val);
    }
    sort(num_list.begin(), num_list.end());
    cout << num_list.size() << endl;

    vector<long> target_values;
    for(int i=0; i<num_list.size(); i++) {
        // find the lower and upper bound for elements 
        // that can make sums between [-10000, 10000]
        auto lower = lower_bound(num_list.begin(), num_list.end(), -10000-num_list[i]);
        auto upper = upper_bound(num_list.begin(), num_list.end(),  10000-num_list[i]);
        vector<long> sub_list(lower, upper);
        // get all possible target_values
        for(auto it: sub_list) {
            if(it!=num_list[i]) { // only count on distinct x,y
                target_values.push_back(it+num_list[i]);
            }
        }
    }

    sort(target_values.begin(), target_values.end());
    auto last = unique(target_values.begin(), target_values.end()); // unique() returns an iterator of the new end
    target_values.erase(last, target_values.end());

    cout << target_values.size() << endl;

    return 0;
}

