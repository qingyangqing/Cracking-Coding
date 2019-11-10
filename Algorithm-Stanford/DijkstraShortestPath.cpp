// Qing

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <climits>
#include <cstring> // used for string delimiter

using namespace std;

struct Vertex {
    int id;
    vector<int> point_to;
    vector<int> dist;
};

void printV (Vertex v) {
    cout << "id: " << v.id << endl;
    for(auto it: v.point_to) cout << it << ' ';
    cout << endl;
    for(auto it: v.dist) cout << it << ' ';
    cout << endl;
}

// find the shortest path for all reachable vertices starting from start_id
vector<int> DijkstraShortestPath (vector<Vertex>& G, int start_id) {
    vector<int> explored(G.size(), 0);
    vector<int> distance(G.size(), INT_MAX);

    // start from start_id
    explored[start_id-1] = 1;
    distance[start_id-1] = 0;
    // explore all the frontiers, find the shortest expanding step
    if(G[start_id-1].point_to.size()==0) return distance;

    int flag_has_outreach = 1;
    while(flag_has_outreach) {
        // revert the flag
        flag_has_outreach = 0;
        // look over all the frontiers
        int next_id = 0;
        int dist_next_id = INT_MAX;
        for(int i=0; i<explored.size(); i++) {
            // only check the outreaches of explored vertices
            if(explored[i]==1) {
                Vertex v = G[i];
                // find the shortest outreach
                for(int j=0; j<v.point_to.size(); j++) {
                    if(explored[v.point_to[j]-1]==0) {
                        flag_has_outreach = 1;
                        if(distance[i]+v.dist[j]<dist_next_id) {
                            next_id = v.point_to[j];
                            dist_next_id = distance[i]+v.dist[j];
                        }
                    }
                }
            }
        }
        // update explored history
        if(flag_has_outreach) {
            explored[next_id-1] = 1;
            distance[next_id-1] = dist_next_id;
        }
    }
    return distance;
}

int main () {
    //ifstream infile("/home/qing/Downloads/stanford-algs/testCases/course2/assignment2Dijkstra/input_random_28_256.txt");
    ifstream infile("dijkstraData.txt");
    string Line;
    // graph is stored as a vector of vertices
    vector<Vertex> G;
    while(getline(infile, Line)) {
        stringstream ss(Line);
        Vertex v;
        int id;
        ss >> id; v.id = id;
        string edge;
        while(ss>>edge) {
            char* edge_cstr = new char [edge.size()+1];
            strcpy(edge_cstr, edge.c_str());
            char* val = strtok(edge_cstr, ",");
            v.point_to.push_back(atoi(val));
            val = strtok(nullptr, ",");
            v.dist.push_back(atoi(val));
            delete edge_cstr;
        }
        G.push_back(v);
    }

    vector<int> distance = DijkstraShortestPath(G, 1);
    int v_list[10] = {7,37,59,82,99,115,133,165,188,197};
    for(int i=0; i<10; i++) cout << distance[v_list[i]-1] << ',';
    cout << endl;

    return 0;
}

