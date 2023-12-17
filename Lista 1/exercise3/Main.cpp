#include <iostream>
#include "Graph.hpp"

using namespace std;

void test() {
    string filename = "ex3/g3-5.txt";
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

    cout << "Silnie spójne składowe:" << "\n";
    graph.strongly_connected_components(graph);

}

int main() {
    test();
    return 0;
}