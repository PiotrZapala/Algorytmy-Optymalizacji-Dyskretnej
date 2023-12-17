#include "Node.hpp"

using namespace std;

Node::Node(int id) {
    this->id = id;
    this->color = 'W';
}

int Node::get_id() const {
    return id;
}

void Node::set_id(int new_id) {
    this->id = new_id;
}

vector<Node*>& Node::get_neighbors() {
    return neighbors;
}

void Node::add_neighbor(Node* neighbor) {
    this->neighbors.push_back(neighbor);
}

void Node::set_color(char new_color) {
    this->color = new_color;
}

char Node::get_color() const {
    return color;
}
