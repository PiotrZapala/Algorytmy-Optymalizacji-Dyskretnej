#ifndef NODE_H
#define NODE_H

using namespace std;

#include <vector>

class Node {
public:
    Node() = default;
    Node(int id);

    int get_id() const;
    void set_id(int new_id);

    char get_color() const;
    void set_color(char new_color);

    void add_neighbor(Node* neighbor);
    
    vector<Node*>& get_neighbors();

private:
    int id;
    char color;
    vector<Node*> neighbors;
};

#endif // NODE_H
