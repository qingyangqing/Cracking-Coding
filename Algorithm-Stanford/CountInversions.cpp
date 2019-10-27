// Qing

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long CountInversions(vector<int>& num_list) {
    // if the list only has one number
    if(num_list.size()==1) return 0;
    // if the list has more than one number
    // count inversions for the left half
    auto front = num_list.begin();
    auto back = num_list.begin()+num_list.size()/2;
    vector<int> num_lh(front, back);
    long inversions_lh = CountInversions(num_lh);
    // count inversions for the right half
    front = num_list.begin()+num_list.size()/2;
    back = num_list.end();
    vector<int> num_rh(front, back);
    long inversions_rh = CountInversions(num_rh);

    // merge num_lh and num_rh, and count inversions
    long inversions_merge = 0;
    for(int i=0; i<num_lh.size(); i++) num_list[i] = num_lh[i];
    for(int i=0; i<num_rh.size(); i++) num_list[i+num_lh.size()] = num_rh[i];
    int lh_idx = 0;
    int rh_idx = 0;
    int k = 0;
    for(k=0; k<num_list.size();) {
        if(num_lh[lh_idx]<=num_rh[rh_idx]) {
            num_list[k] = num_lh[lh_idx];
            lh_idx ++;
            k ++;
        } else {
            num_list[k] = num_rh[rh_idx];
            rh_idx ++;
            k ++;
            inversions_merge += (num_lh.size()-lh_idx);
        }
        if(lh_idx==num_lh.size() || rh_idx==num_rh.size()) break;
    }
    // if it runs over num_rh firstly
    if(rh_idx==num_rh.size()) {
        for(;k<num_list.size();) {
            num_list[k] = num_lh[lh_idx];
            lh_idx ++;
            k ++;
        }
    }
    return inversions_lh+inversions_rh+inversions_merge;
}

int main() {
    // ifstream infile("in.txt");
    ifstream infile("IntegerArray.txt");
    vector<int> num_list;
    int number;
    while(infile>>number) {
        num_list.push_back(number);
    }

    long inversionsNum = CountInversions(num_list);
    cout << inversionsNum << endl;
    return 0;
}

