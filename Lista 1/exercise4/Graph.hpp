#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include "Node.hpp"

using namespace std;

class Graph {
public:
    Graph() = default;
    Graph(char flag, int n, int m);

    static Graph create_graph(const string& filename);

    void is_bipartite();

    char get_flag() const;
    void set_flag(char new_flag);

    int get_n() const;
    void set_n(int new_n);

    int get_m() const;
    void set_m(int new_m);

    vector<Node>& get_nodes();

private:
    char flag;
    int n, m;
    vector<Node> nodes;
};

#endif // GRAPH_H
