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

void Graph::dfs_util(Node* node, vector<bool>& visited, vector<Node*>& dfs_tree) {
    visited[node->get_id()] = true;
    dfs_tree.push_back(node);
    for (Node* neighbor : node->get_neighbors()) {
        if (!visited[neighbor->get_id()]) {
            dfs_util(neighbor, visited, dfs_tree);
        }
    }
}

vector<Node*> Graph::dfs() {
    vector<bool> visited(n, false);
    vector<Node*> dfs_tree;
    for (Node& node : nodes) {
        if (!visited[node.get_id()]) {
            dfs_util(&node, visited, dfs_tree);
        }
    }
    return dfs_tree;
}

void Graph::bfs_util(Node* node, vector<bool>& visited, vector<Node*>& bfs_tree) {
    queue<Node*> q;
    visited[node->get_id()] = true;
    q.push(node);
    bfs_tree.push_back(node);
    while (!q.empty()) {
        Node* curr_node = q.front();
        q.pop();
        for (Node* neighbor : curr_node->get_neighbors()) {
            if (!visited[neighbor->get_id()]) {
                visited[neighbor->get_id()] = true;
                bfs_tree.push_back(neighbor);
                q.push(neighbor);
            }
        }
    }
}

vector<Node*> Graph::bfs() {
    vector<bool> visited(n, false);
    vector<Node*> bfs_tree;
    for (Node& node : nodes) {
        if (!visited[node.get_id()]) {
            bfs_util(&node, visited, bfs_tree);
        }
    }
    return bfs_tree;
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