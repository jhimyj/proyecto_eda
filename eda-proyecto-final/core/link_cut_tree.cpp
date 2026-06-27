//
// Created by jhimy on 26/06/26.
//
#include "link_cut_tree.hpp"
#include <algorithm>

Node::Node(int id) : id(id), size(1), flip(false), left(nullptr), right(nullptr), parent(nullptr) {}

LinkCutTree::LinkCutTree(int n) {
    nodes.resize(n + 1, nullptr);
    for (int i = 1; i <= n; ++i) {
        nodes[i] = new Node(i);
    }
}

LinkCutTree::~LinkCutTree() {
    for (size_t i = 1; i < nodes.size(); ++i) {
        delete nodes[i];
    }
}

bool LinkCutTree::isRoot(Node* x) {
    return !x->parent || (x->parent->left != x && x->parent->right != x);
}

void LinkCutTree::push(Node* x) {
    if (x && x->flip) {
        std::swap(x->left, x->right);
        if (x->left) x->left->flip ^= 1;
        if (x->right) x->right->flip ^= 1;
        x->flip = false;
    }
}

void LinkCutTree::pull(Node* x) {
    if (x) {
        x->size = 1;
        if (x->left) x->size += x->left->size;
        if (x->right) x->size += x->right->size;
    }
}

void LinkCutTree::rotate(Node* x) {
    Node* p = x->parent;
    Node* g = p->parent;
    bool isLeft = (p->left == x);

    if (!isRoot(p)) {
        if (g->left == p) g->left = x;
        else g->right = x;
    }
    x->parent = g;

    if (isLeft) {
        p->left = x->right;
        if (x->right) x->right->parent = p;
        x->right = p;
    } else {
        p->right = x->left;
        if (x->left) x->left->parent = p;
        x->left = p;
    }
    p->parent = x;
    pull(p);
    pull(x);
}

void LinkCutTree::splay(Node* x) {
    std::vector<Node*> stack;
    Node* curr = x;
    stack.push_back(curr);

    while (!isRoot(curr)) {
        curr = curr->parent;
        stack.push_back(curr);
    }

    while (!stack.empty()) {
        push(stack.back());
        stack.pop_back();
    }

    while (!isRoot(x)) {
        Node* p = x->parent;
        Node* g = p->parent;
        if (!isRoot(p)) {
            if ((p->left == x) ^ (g->left == p)) rotate(x);
            else rotate(p);
        }
        rotate(x);
    }
}

Node* LinkCutTree::access(Node* x) {
    Node* last = nullptr;
    for (Node* curr = x; curr; curr = curr->parent) {
        splay(curr);
        curr->right = last;
        pull(curr);
        last = curr;
    }
    splay(x);
    return last;
}

void LinkCutTree::makeRoot(Node* x) {
    access(x);
    x->flip ^= 1;
    push(x);
}

Node* LinkCutTree::findRoot(Node* x) {
    access(x);
    while (x->left) {
        push(x);
        x = x->left;
    }
    splay(x);
    return x;
}

void LinkCutTree::link(int u, int v) {
    if (u >= nodes.size() || v >= nodes.size()) return;
    Node* nu = nodes[u];
    Node* nv = nodes[v];
    makeRoot(nu);
    if (findRoot(nv) != nu) {
        nu->parent = nv;
    }
}

void LinkCutTree::cut(int u, int v) {
    if (u >= nodes.size() || v >= nodes.size()) return;
    Node* nu = nodes[u];
    Node* nv = nodes[v];
    makeRoot(nu);
    access(nv);
    if (nv->left == nu && !nu->right) {
        nv->left = nullptr;
        nu->parent = nullptr;
        pull(nv);
    }
}

bool LinkCutTree::connected(int u, int v) {
    if (u >= nodes.size() || v >= nodes.size()) return false;
    Node* nu = nodes[u];
    Node* nv = nodes[v];
    if (nu == nv) return true;
    return findRoot(nu) == findRoot(nv);
}

int LinkCutTree::getComponentSize(int u) {
    if (u >= nodes.size()) return 0;
    Node* nu = nodes[u];
    makeRoot(nu);
    return nu->size;
}

double LinkCutTree::getBridgeScore(int u, int v) {
    if (connected(u, v)) return 0.0;
    int sizeU = getComponentSize(u);
    int sizeV = getComponentSize(v);
    return static_cast<double>(std::min(sizeU, sizeV));
}