//BFS VS DFS
//insertion, deletion, searching, traversal
//binary tree is more like a structure
//and its implementations like heap and binary tree resolves real problems
//values cannot be same inside bt
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.cpp"

using namespace std;


template <typename T>
struct Node {
  T value;
  Node* left_child;
  Node* right_child;
};

template <typename T>
class BinaryTree {
  private:
    Node<T>* root;

    void preorder(Node<T>* node) {
      if(node == NULL) return;
      cout<<node->value<<"\n";
      
      preorder(node->left_child);
      preorder(node->right_child);
    }

    Node<T>* recursive_deletion(Node<T>* node, T value) {
      if(node == NULL) return NULL;

      if(node->value == value) {
        if(node->left_child == NULL && node->right_child == NULL) {
          delete node;
          return NULL;
        }
        else if(node->left_child == NULL) {
          Node<T>* temp_node = node->right_child;
          delete node;
          return temp_node;
        }
        else if(node->right_child == NULL) {
          Node<T>* temp_node = node->left_child;
          delete node;
          return temp_node;
        }

        Node<T>* substitute = find_lowest(node->right_child);
        node->value = substitute->value;

        //needs to be like that cannot use substitute = recursive_deletion(substitute, substitute->value)
        //bo wowczas nie zmieni sie referencja w nodzie parencie na tego substitute, wiec musimy cale prawe drzewo przejsc
        node->right_child = recursive_deletion(node->right_child, substitute->value);
      } else {
        node->left_child = recursive_deletion(node->left_child, value);
        node->right_child = recursive_deletion(node->right_child, value);
      }
      
      return node;
    }
  public:
    BinaryTree() {
      root = NULL;
    }

    void insert(T value) {
      //add nodes as for balanced tree
      Node<T>* insert_node = new Node<T>();
      insert_node->value = value;

      if(root == NULL) {
        root = insert_node;
        return;
      }

      Queue<Node<T>*> queue;
      queue.enqueue(this->root);

      while(!queue.is_empty()) {
        Node<T>* curr_node = queue.dequeue();
        
        if(curr_node->left_child == NULL) {
          curr_node->left_child = insert_node;
          return;
        }
        queue.enqueue(curr_node->left_child);

        if(curr_node->right_child == NULL) {
          curr_node->right_child = insert_node;
          return;
        }
        queue.enqueue(curr_node->right_child);
      }
    }

    void delete_node(T value) {
      root = recursive_deletion(root, value);
    }

    Node<T>* find_lowest(Node<T>* node) {
      while(node->left_child != NULL) {
        node = node->left_child;
      };

      return node;
    }

    void traversal_preorder() {
      cout<<"preorder: "<<"\n";
      preorder(this->root);
      cout<<"\n";
    }

    void traversal_level() {
      //do it with openGL
      Queue<Node<T>*> queue;
      queue.enqueue(this->root);
      cout<<"level order: "<<"\n";

      while(!queue.is_empty()) {
        Node<T>* curr_node = queue.dequeue();
        cout<<curr_node->value<<"\n";

        if(curr_node->left_child != NULL) {
          queue.enqueue(curr_node->left_child);
        }
        if(curr_node->right_child != NULL) {
          queue.enqueue(curr_node->right_child);
        }
      }

      cout<<"\n";
    }
};

int main (int argc, char *argv[]) {
  BinaryTree<int> bt;
  bt.insert(1);
  bt.insert(2);
  bt.insert(3);
  bt.insert(4);
  bt.traversal_preorder();
  bt.traversal_level();

  bt.delete_node(1);
  bt.traversal_preorder();
  bt.traversal_level();
  return 0;
}
