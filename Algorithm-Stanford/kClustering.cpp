// Qing

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <climits>

using namespace std;

struct customLess {
    bool operator () (const vector<int>& a, const vector<int>& b) const {
        if(a.back()<b.back()) return true;
        else return false;
    }
};

void printEdges (vector<vector<int>>& E) {
    for(auto& v:E) cout << v[0] << ' ' << v[1] << ' ' << v[2] << endl;
    cout << endl;
}

int find(int index, vector<int>& ptrs) {
    if(ptrs[index-1]!=index) ptrs[index-1] = find(ptrs[index-1], ptrs);
    return ptrs[index-1];
}

int main () {
    //ifstream infile ("/home/qing/Cracking-Coding/testCases/course3/assignment2Clustering/question1/input_completeRandom_1_8.txt");
    //ifstream infile ("/home/qing/Cracking-Coding/testCases/course3/assignment2Clustering/question1/input_completeRandom_32_1024.txt");
    ifstream infile ("clustering1.txt");
    string s;
    getline(infile, s);
    int nodeNum = atoi(s.c_str());

    vector<vector<int>> edges;
    while(getline(infile, s)) {
        stringstream ss (s);
        int tempVal;
        vector<int> tempVec;
        while(ss>>tempVal) tempVec.push_back(tempVal);
        edges.push_back(tempVec);
    }

    sort(edges.begin(), edges.end(), customLess());
    //printEdges(edges);

    // k clustering
    int k = 4;
    int clustering = nodeNum;
    vector<int> ptrs;
    for(int j=0; j<nodeNum; j++) ptrs.push_back(j+1);

    int i = 0;
    while(clustering>k) {
        int p1 = find(edges[i][0], ptrs);
        int p2 = find(edges[i][1], ptrs);
        //cout << edges[i][0] << ' ' << p1 << ';' << edges[i][1] << ' ' << p2 << endl;
        if(p1!=p2) { // union
            ptrs[p1-1] = p2; // pay attention to the union operation.
            clustering --;
        }
        i ++;
    }

    int maxDist = INT_MAX;
    for(; i<edges.size(); i++) {
        int p1 = find(edges[i][0], ptrs);
        int p2 = find(edges[i][1], ptrs);
        if(p1!=p2) maxDist = min(maxDist, edges[i][2]);
    }

    cout << maxDist << endl;

    return 0;
}

