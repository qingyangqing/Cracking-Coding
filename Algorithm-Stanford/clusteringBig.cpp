// Qing

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

void printNodes (vector<vector<int>>& nodes) {
    for(auto& n:nodes) {
        for(int i:n) cout << i << ' ';
        cout << endl;
    }
    cout << endl;
}

inline bool canMerge (vector<int>& a, vector<int>& b) {
    int dist = 0;
    for(int i=0; i<a.size(); i++) {
        dist += (a[i]!=b[i]);
        if(dist>=3) return false;
    }
    return true;
}

inline int find (int index, vector<int>& ptrs) {
    if(ptrs[index]!=index) ptrs[index] = find(ptrs[index], ptrs);
    return ptrs[index];
}

int main () {
    //ifstream infile ("/home/qing/Cracking-Coding/testCases/course3/assignment2Clustering/question2/input_random_1_4_14.txt");
    //ifstream infile ("/home/qing/Cracking-Coding/testCases/course3/assignment2Clustering/question2/input_random_81_131072_24.txt");
    ifstream infile ("clustering_big.txt");
    string line;
    getline(infile, line);

    stringstream ss (line);
    int nodeNum;
    int dim;
    ss >> nodeNum >> dim;

    vector<vector<int>> nodes;
    while(getline(infile, line)) {
        stringstream ss (line);
        int val;
        vector<int> vec;
        while(ss>>val) vec.push_back(val);
        nodes.push_back(vec);
    }

    //printNodes(nodes);

    vector<int> ptrs;
    for(int i=0; i<nodeNum; i++) ptrs.push_back(i);
    
    int clusterNum = nodeNum;
    for(int i=0; i<nodeNum-1; i++) {
        if(i%1000==0) cout << i << endl;

        for(int j=i+1; j<nodeNum; j++) {
            int p1 = find(i, ptrs);
            int p2 = find(j, ptrs);
            if(p1!=p2 && canMerge(nodes[i], nodes[j])) {
                clusterNum --;
                ptrs[p1] = p2;
            }
        }
    }
    cout << clusterNum << endl;

    return 0;
}

