#include <iostream>
#include "Graph.hpp"

using namespace std;

void test_topological_sorting(Graph graph){
    vector<Node*> sorted_nodes = graph.topological_sort();
    if (sorted_nodes.size() == graph.get_n() && graph.get_n() <= 200) {
        cout << "Posortowane wezly:\n";
        for (Node* node : sorted_nodes) {
            cout << node->get_id() << " ";
        }
        cout << "\n";
    }
}

void test() {
    string filename = "ex2/g2a-2.txt";
    Graph graph = Graph::create_graph(filename);

    cout << "\n" << "Graf o fladze: " << graph.get_flag() << ", liczbie wierzchołków: " << graph.get_n() << " i liczbie krawędzi: " << graph.get_m() << "\n" << "\n";

    if (graph.get_n() <= 200) {
        cout << "Wierzchołki: ";
        for (int i = 1; i <= graph.get_n(); i++) {
            cout << i << " ";
        }
        cout << "\n" << "\n";

        cout << "Krawędzie: \n";
        for (int i = 0; i < graph.get_n()-1; i++) {
            cout << i+1 << " : ";
            for (Node* neighbor : graph.get_nodes()[i].get_neighbors()) {
                cout << neighbor->get_id() << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    test_topological_sorting(graph);
}

int main() {
    test();
    return 0;
}