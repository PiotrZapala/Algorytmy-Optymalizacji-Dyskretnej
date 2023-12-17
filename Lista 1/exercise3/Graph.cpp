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

Graph Graph::transpose() {
    Graph transposed_graph(flag, n, m);
    transposed_graph.nodes.resize(n);

    for (int i = 0; i < n; i++) {
        Node* current_node = &nodes[i];
        for (const auto& neighbor : current_node->get_neighbors()) {
            Node* transposed_node = &transposed_graph.nodes[neighbor->get_id() - 1];
            transposed_node->add_neighbor(&transposed_graph.nodes[i]);
            transposed_node->set_id(neighbor->get_id());
        }
    }

    return transposed_graph;
}


void Graph::dfs1(Node* node, stack<Node*>& node_stack, vector<bool>& visited) {
    visited[node->get_id()] = true;
    for (Node* neighbor : node->get_neighbors()) {
        if (!visited[neighbor->get_id()]) {
            dfs1(neighbor, node_stack, visited);
        }
    }
    node_stack.push(node);
}

void Graph::dfs2(Node* node, vector<Node*>& scc, vector<bool>& visited) {
    visited[node->get_id()] = true;
    scc.push_back(node);
    for (Node* neighbor : node->get_neighbors()) {
        if (!visited[neighbor->get_id()]) {
            dfs2(neighbor, scc, visited);
        }
    }
}

void Graph::strongly_connected_components(Graph& graph) {
    vector<Node>& nodes = graph.get_nodes();
    int n = graph.get_n();

    vector<bool> visited(n, false);
    stack<Node*> node_stack;
    for (Node& node : nodes) {
        if (!visited[node.get_id()]) {
            dfs1(&node, node_stack, visited);
        }
    }

    Graph transposed_graph = graph.transpose();
    vector<Node>& transposed_nodes = transposed_graph.get_nodes();
    visited = vector<bool>(n, false);
    while (!node_stack.empty()) {
        Node* curr_node = node_stack.top();
        node_stack.pop();
        if (!visited[curr_node->get_id()]) {
            vector<Node*> scc;
            dfs2(&transposed_nodes[curr_node->get_id()-1], scc, visited);
            cout << "Silnie spójna składowa o liczności " << scc.size() << ": ";
            if (graph.get_n() <= 200) {
                for (Node* node : scc) {
                    cout << node->get_id() << " ";
                }
            }
            cout << endl;
        }
    }
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