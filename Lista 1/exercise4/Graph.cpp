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

void Graph::is_bipartite() {
    vector<int> color(n, -1);
    queue<int> q;

    color[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto& v : nodes[u].get_neighbors()) {
            if (color[v->get_id() - 1] == -1) {
                color[v->get_id() - 1] = 1 - color[u];
                q.push(v->get_id() - 1);
            }

            if (color[v->get_id() - 1] == color[u]) {
                cout << "Graf nie jest dwudzielny!" << endl;
                return;
            }
        }
    }

    vector<int> V0, V1;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            V0.push_back(i);
        } else {
            V1.push_back(i);
        }
    }

    cout << "Graf jest dwudzielny. Podział na zbiory V0 i V1:" << endl;
    if (nodes.size() <= 200) {
        cout << "V0 = { ";
        for (auto& v : V0) {
            cout << v+1 << " ";
        }
        cout << "}" << endl;
        cout << "V1 = { ";
        for (auto& v : V1) {
            cout << v+1 << " ";
        }
        cout << "}" << endl;
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