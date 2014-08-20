#pragma once

#include <stdexcept>
#include <algorithm>

template <typename T>
class TreeNode {
 public:
     TreeNode();
     TreeNode(const T&);
     ~TreeNode();

     // parent
     TreeNode<T> *parent;
     // first, last child
     TreeNode<T> *first_child, *last_child;
     // brothers
     TreeNode<T> *prev_sibling, *next_sibling;

     // the data
     T data;
};

template <typename T>
TreeNode<T>::TreeNode() 
    : parent(0), first_child(0), 
    last_child(0), prev_sibling(0), 
    next_sibling(0) {}

template <typename T>
TreeNode<T>::TreeNode(const T& v) 
    : parent(0), first_child(0),
    last_child(0), prev_sibling(0),
    next_sibling(0), data(v) {
}

// tree
template <typename T, class tree_alloc = std::allocator<TreeNode<T>>>
class Tree {
 private:
    typedef TreeNode<T> TreeNode;

 public:
    Tree();
    ~Tree();

    // ops
    void insert(const T& data);
    void search(const T& data);
    void remove(const T& data);

 private:
    TreeNode *root;
    tree_alloc _alloc;
};

template <typename T, class tree_alloc>
Tree<T, tree_alloc>::Tree() {
    root = _alloc.allocate(1,0);
    root->parent = 0;
    root->first_child = 0;
    root->last_child = 0;
    root->prev_sibling = 0;
    root->next_sibling = 0;
}

template <typename T, class tree_alloc>
Tree<T, tree_alloc>::~Tree() {
    _alloc.destory(head);
    _alloc.deallocate(head,1);
}

template <typename T, class tree_alloc>
Tree<T, tree_alloc>::insert(const T& data) {
    TreeNode<T>* node = new TreeNode<T>(data);
    TreeNode<T>* tmp;
}

