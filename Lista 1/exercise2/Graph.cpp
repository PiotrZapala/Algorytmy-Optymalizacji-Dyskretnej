#include <fstream>
#include <queue>
#include <stack>
#include "Graph.hpp"

using namespace std;

Graph::Graph(char flag, int n, int m) {
    this->flag = flag;
    this->n = n;
    this->m = m;
}

Graph Graph::create_graph(const string& filename) {
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Blad: Nie mozna otworzyc pliku " << filename << "\n";
        return Graph();
    }
    char flaga;
    int n, m;
    input >> flaga >> n >> m;
    Graph graph(flaga, n, m);
    graph.nodes.resize(n);
    int v, w;
    while (input >> v >> w) {
        Node* node_v = &graph.nodes[v-1];
        Node* node_w = &graph.nodes[w-1];
        node_v->add_neighbor(node_w);
        node_v->set_id(v);
        node_w->set_id(w);
        if (graph.flag == 'U') {
            node_w->add_neighbor(node_v);
            node_w->set_id(w);
        }
    }
    input.close();
    return graph;
}

vector<Node*> Graph::topological_sort() {
    vector<Node*> sorted_nodes;
    vector<int> in_degree(n, 0);
    queue<Node*> q;
    for (Node& node : nodes) {
        for (Node* neighbor : node.get_neighbors()) {
            in_degree[neighbor->get_id()]++;
        }
    }
    for (Node& node : nodes) {
        if (in_degree[node.get_id()] == 0) {
            q.push(&node);
        }
    }
    while (!q.empty()) {
        Node* curr_node = q.front();
        q.pop();
        sorted_nodes.push_back(curr_node);
        for (Node* neighbor : curr_node->get_neighbors()) {
            in_degree[neighbor->get_id()]--;
            if (in_degree[neighbor->get_id()] == 0) {
                q.push(neighbor);
            }
        }
    }
    if (sorted_nodes.size() != n) {
        cout << "Graf zawiera skierowany cykl.\n";
        sorted_nodes.clear();
    }
    return sorted_nodes;
}


char Graph::get_flag() const {
    return flag;
}

void Graph::set_flag(char new_flag) {
    this->flag = new_flag;
}

int Graph::get_n() const {
    return n;
}

void Graph::set_n(int new_n) {
    this->n = new_n;
}

int Graph::get_m() const {
    return m;
}

void Graph::set_m(int new_m) {
    this->m = new_m;
}

vector<Node>& Graph::get_nodes() {
    return nodes;
}