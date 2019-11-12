// Qing

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

struct Edge {
    int to_id;
    int dist;
};

void print_G (vector<vector<Edge>>& G) {
    for(auto adj_list: G) {
        for(auto edge: adj_list) {
            cout << '(' << edge.to_id << ' ' << edge.dist << ')';
        }
        cout << endl;
    }
}

long PrimMinSpanTree (vector<vector<Edge>>& G) {
    long dist_accum = 0;
    vector<int> explored(G.size(), 0);
    // do greedy spanning by finding the min edge at each time
    // start at id 1
    explored[0] = 1;
    int has_outreach = 1;
    while(has_outreach) {
        int explored_id = 0;
        int min_spanning = INT_MAX;
        has_outreach = 0;

        for(int i=0; i<G.size(); i++) {
            if(explored[i]==1) { // only check outreaches of explored nodes
                vector<Edge> adj_list_node = G[i];
                for(auto edge: adj_list_node) {
                    if(explored[edge.to_id-1]==0) { // check the outreaches pointing to unexplored nodes
                        has_outreach = 1;
                        if(edge.dist<min_spanning) {
                            explored_id = edge.to_id;
                            min_spanning = edge.dist;
                        }
                    }
                }
            }
        }
        // get the min spanning
        if(explored_id!=0) {
            explored[explored_id-1] = 1;
            dist_accum += min_spanning;
        }
    }
    return dist_accum;
}

int main () {
    //ifstream infile("/home/qing/Downloads/stanford-algs/testCases/course3/assignment1SchedulingAndMST/question3/input_random_32_800.txt");
    ifstream infile("edges.txt");
    string Line;
    getline(infile, Line);
    stringstream ss(Line);
    int num_nodes;
    ss >> num_nodes;

    // graph is stored using adjacency list
    vector<vector<Edge>> graph;
    for(int i=0; i<num_nodes; i++) {
        vector<Edge> adj_list_node;
        graph.push_back(adj_list_node);
    }

    while(getline(infile, Line)) {
        int s, t, dist;
        stringstream ss(Line);
        ss >> s >> t >> dist;
        // pay attention, this's an undirected graph
        Edge e;
        e.to_id = t;
        e.dist = dist;
        graph[s-1].push_back(e);
        // the other side of the edge
        e.to_id = s;
        graph[t-1].push_back(e);
    }

    //print_G(graph);

    long dist_accum = PrimMinSpanTree(graph);
    cout << dist_accum << endl;

    return 0;
}

