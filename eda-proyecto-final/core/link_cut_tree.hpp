#ifndef LINK_CUT_TREE_HPP
#define LINK_CUT_TREE_HPP

#include <vector>

struct Node {
    int id;
    int size;
    bool flip;
    Node *left, *right, *parent;

    Node(int id);
};

class LinkCutTree {
private:
    std::vector<Node*> nodes;

    bool isRoot(Node* x);
    void push(Node* x);
    void pull(Node* x);
    void rotate(Node* x);
    void splay(Node* x);
    Node* access(Node* x);
    void makeRoot(Node* x);
    Node* findRoot(Node* x);

public:
    LinkCutTree(int n);
    ~LinkCutTree();

    void link(int u, int v);
    void cut(int u, int v);
    bool connected(int u, int v);
    int getComponentSize(int u);
    double getBridgeScore(int u, int v);
};

#endif