// Qing

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

int main () {
    //ifstream infile ("knapsack1.txt");
    ifstream infile ("knapsack_big.txt");
    string line;
    getline(infile, line);
    stringstream ss (line);
    int knapsackSize;
    int itemNum;
    ss >> knapsackSize >> itemNum;

    vector<pair<int, int>> items;
    while(getline(infile, line)) {
        int val, weight;
        stringstream ss (line);
        ss >> val >> weight;
        items.push_back({val, weight});
    }

    // dynamic programming
    // the length is knapsackSize+1 to contain the zero knapsack
    vector<int> hist (knapsackSize+1, 0);
    vector<int> curr (knapsackSize+1, 0);
    // initialize hist
    for(int i=0; i<knapsackSize+1; i++) {
        if(i>=items[0].second) hist[i] = items[0].first;
    }

    auto ptr_hist = &hist;
    auto ptr_curr = &curr;
    for(int i=1; i<itemNum; i++) {
        if(i%100==0) cout << i << endl;

        int val = items[i].first;
        int weight = items[i].second;
        for(int j=0; j<knapsackSize+1; j++) {
            int useIt = (j>=weight)? val + ptr_hist->at(j-weight) : 0;
            int loseIt = ptr_hist->at(j);
            (*ptr_curr)[j] = max(useIt, loseIt);
        }
        swap(ptr_hist, ptr_curr);
    }

    cout << (*ptr_hist).back() << endl;

    return 0;
}

