// Qing

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>
#include <ctime>
#include <cmath>

using namespace std;

void print_G (vector<vector<int>> G) {
    for(auto adja_list: G) {
        for(auto it: adja_list) cout << it << ' ';
        cout << endl;
    }
    cout << endl;
}

void print_vec (vector<int> vec) {
    for(auto it: vec) cout << it << ' ';
    cout << endl;
}

// the graph G is a list of adjacency list
int RandomContractionGraph (vector<vector<int>> G) {
    vector<int> id; // store the remaining nodes
    for(int i=0; i<G.size(); i++) id.push_back(i+1); // id number starts from 1
    while(id.size()>2) {
        // randomly choose an node and merge
        srand(time(nullptr));
        int id_removed_pos = rand()%id.size();
        int id_removed = id[id_removed_pos];
        id.erase(id.begin()+id_removed_pos); // remove the node
        // find the id_merged_to
        int id_merged_to = G[id_removed-1][0];
        // update graph, pay attention to avoid self-loop
        // look over the adjacent list of node id_removed
        for(auto adja_id_removed: G[id_removed-1]) {
            if(adja_id_removed==id_merged_to) { // remove self-loop in the node id_merged_to
                vector<int>& adja_list_id_merged_to = G[id_merged_to-1];
                for(int i=0; i<adja_list_id_merged_to.size(); i++) {
                    if(adja_list_id_merged_to[i]==id_removed) {
                        adja_list_id_merged_to.erase(adja_list_id_merged_to.begin()+i);
                        i--;
                    }
                }
            } else { // update graph
                // add edges that are originally for id_removed to id_merged_to
                G[id_merged_to-1].push_back(adja_id_removed);
                // redirect the edges related to id_removed in node adja_id_removed
                for(int i=0; i<G[adja_id_removed-1].size(); i++) {
                    if(G[adja_id_removed-1][i]==id_removed) G[adja_id_removed-1][i] = id_merged_to;
                }
            }
        }
        //print_vec(id);
        //cout << id_merged_to << endl;
        //print_G(G);
    }
    // check the left two nodes
    int num_edges = G[id[0]-1].size();
    return num_edges;
}

int main () {
    //ifstream infile("/home/qing/Downloads/stanford-algs/testCases/course1/assignment4MinCut/input_random_1_6.txt");
    //ifstream infile("/home/qing/Downloads/stanford-algs/testCases/course1/assignment4MinCut/input_random_16_50.txt");
    ifstream infile("kargerMinCut.txt");

    int N = 0;
    vector<vector<int>> Graph;
    string Line;
    while(getline(infile, Line)) {
        stringstream ss(Line);
        N++;
        int val;
        ss >> val;
        vector<int> adja_list;
        while(ss>>val) {
            adja_list.push_back(val);
        }
        Graph.push_back(adja_list);
    }

    //print_G(Graph);
    int minCuts = INT_MAX;
    for(int i=0; i<N*N*int(log(N)); i++) {
        if(i%1000==0) cout << i << ' ' << minCuts << endl;
        int counts = RandomContractionGraph(Graph);
        if(minCuts>counts) minCuts = counts;
    }

    cout << minCuts << endl;
    return 0;
}

