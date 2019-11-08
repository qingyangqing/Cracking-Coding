// Qing

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <algorithm>

using namespace std;

struct Node {
    int id;
    vector<int> point_to;
};

void print_G (vector<Node> G) {
    for(auto node: G) {
        cout << node.id << ' ';
        for(auto it: node.point_to) cout << it << ' ';
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> getEdges (vector<Node>& G) {
    int max_id = G.back().id;
    vector<vector<int>> edges;
    for(int i=0; i<max_id; i++) {
        vector<int> edges_per_id;
        edges.push_back(edges_per_id);
    }
    for(auto node: G) {
        for(auto it: node.point_to) edges[node.id-1].push_back(it);
    }
    return edges;
}

vector<vector<int>> revertE (vector<vector<int>>& E) {
    // In my first solution, adjacency matrix is used to get reverse G.
    // However, it turns to be out of memory for large graph, 
    // because the matrix will extremely huge.

    // For the memory-efficient solution, iteratively look over all edges
    vector<vector<int>> Erev;
    // initialize Erev
    for(int i=0; i<E.size(); i++) {
        vector<int> edges_per_node;
        Erev.push_back(edges_per_node);
    }
    // get reverse edges
    for(int i=0; i<E.size(); i++) {
        for(auto j: E[i]) {
            Erev[j-1].push_back(i+1);
        }
    }
    return Erev;
}

// E are edges for nodes with id from 1 to max_id
// In explore_order and finish_order, a sequence of node IDs are recorded to stand for the ordering
vector<int> DFS_loop (vector<vector<int>>& E, vector<int> explore_order, vector<int>& finish_order) {
    vector<int> SCC_size;
    // use DFS to tranverse the graph
    vector<int> explored (E.size(), 0);
    stack<int> id_stack;
    for(auto id: explore_order) {
        // if not explored, pushed into stack for DFS routine
        if(explored[id-1]==0) {
            explored[id-1] = 1;
            id_stack.push(id);
            // DFS
            int size = 1;
            int id_stack_top;
            while(!id_stack.empty()) {
                id_stack_top = id_stack.top();
                // push the unexplored nodes that top_node points to
                vector<int> node_edges = E[id_stack_top-1];
                int flag_push_new_node = 0; // 0 for no new node, 1 for push a new node into stack
                for(auto id: node_edges) {
                    if(explored[id-1]==0) { // find one node unexplored, push it into stack
                        size ++;
                        explored[id-1] = 1;
                        id_stack.push(id);
                        flag_push_new_node = 1;
                        break;
                    }
                }
                if(flag_push_new_node==0) { // no new node found, top off the node at top
                    finish_order.push_back(id_stack_top);
                    id_stack.pop();
                }
            }
            SCC_size.push_back(size);
        }
    }
    return SCC_size;
}

int main () {
    //ifstream infile("/home/qing/Downloads/stanford-algs/testCases/course2/assignment1SCC/input_mostlyCycles_1_8.txt");
    //ifstream infile("/home/qing/Downloads/stanford-algs/testCases/course2/assignment1SCC/input_mostlyCycles_68_320000.txt");
    ifstream infile("SCC.txt");
    string Line;
    int id_now = 0;
    vector<Node> node_list;
    while(getline(infile, Line)) {
        stringstream ss(Line);
        int s, t;
        ss >> s >> t;
        if(s!=id_now) { // a new node appears
            id_now = s;
            Node n = {};
            n.id = s;
            node_list.push_back(n);
        }
        node_list.back().point_to.push_back(t);
    }

    //print_G(node_list);
    //print_G(Grev);
    vector<vector<int>> E = getEdges(node_list);
    vector<vector<int>> Erev = revertE(E);

    // on Grev
    vector<int> finish_order;
    vector<int> explore_order;
    for(int i=0; i<Erev.size(); i++) explore_order.push_back(i+1);
    DFS_loop(Erev, explore_order, finish_order);

    // on G
    for(int i=0; i<finish_order.size(); i++) explore_order[i] = finish_order[finish_order.size()-1-i];
    finish_order.clear();
    vector<int> SCC_size = DFS_loop(E, explore_order, finish_order);
    sort(SCC_size.begin(), SCC_size.end());

    for(int i=0; i<SCC_size.size(); i++) cout << SCC_size[SCC_size.size()-1-i] << ' ';
    cout << endl;

    return 0;
}

