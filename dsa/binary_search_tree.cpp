#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.cpp"

using namespace std;

template <typename T>
class BinarySearchTree: public BinaryTree<T> {
  private:
    //ITERATIVE
    Node<T>* iterative_insert(T value) {
      Node<T>* node = this->root;
      if(node == NULL) {
          node = new Node<T>();
          node->value = value;
          this->root = node;
          return node;
      }

      while(node != NULL) {
        if(value < node->value && node->left_child != NULL) {
          node = node->left_child;
        } else if(value >= node->value && node->right_child != NULL){
          node = node->right_child;
        } else break;
      }

      Node<T>* insert_node = new Node<T>();
      insert_node->value = value;

      if(value < node->value) {
        node->left_child = insert_node;
      } else {
        node->right_child = insert_node;
      }
      return insert_node;
    }

    Node<T>* iterative_search(T value) {
      Node<T>* node = this->root;
      if(node == NULL) return NULL;

      while(node != NULL) {
        if(node->value == value) return node;
        if(value < node->value) node = node->left_child;
        else node = node->right_child;
      }

      return NULL;
    }

    //RECURSIVE

    //this can be done in while loop
    //and also not sure if this function has to return anything, maybe not
    //does not have to, but its nice to get the reference of newly created node
    Node<T>* recursive_insert(Node<T>* node, T value) {
      if(node == NULL) {
        Node<T>* insert_node = new Node<T>();
        insert_node->value = value;

        return insert_node;
      }
      
      if(value < node->value) {
        node->left_child = recursive_insert(node->left_child, value);
      } else {
        node->right_child = recursive_insert(node->right_child, value);
      }

      return node;
    }

    //here the same -> does not have to return node,
    //can only return true or false
    Node<T>* recursive_search(Node<T>* node, T value) {
      if(node == NULL) return NULL;

      if(node->value == value) return node;

      if(value < node->value) return recursive_search(node->left_child, value);

      return recursive_search(node->right_child, value);
    }

    //here have to return to the previous node because
    //if we do not, then we will have stale reference (?)
    Node<T>* recursive_delete(Node<T>* node, T value) {
      if(node == NULL) return node;

      if(value < node->value) {
        node->left_child = recursive_delete(node->left_child, value);
      } 

      else if(value > node->value) {
        node->right_child = recursive_delete(node->right_child, value);
      }

      else {
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

        //find_lowest robi to ze znajdujemy kolejny node wiekszsy od targetu
        //i nie bedzie juz mniejszego node od tego przy porownaniu z targetem
        //to jest nastepnik
        //nie moge po prostu zmienic sobie subsitute = substitute->right_child;
        //jezeli ma prawe dziecko
        //bo chodzi tutaj o rodzica tego substitute, ono ma wiedziec o nowej referencji
        Node<T>* substitute = this->find_lowest(node->right_child);
        node->value = substitute->value;
        node->right_child = recursive_delete(node->right_child, substitute->value);
      }

      return node;
    }
  public:
    void insert(T value) {
      this->root = recursive_insert(this->root, value);
    }

    void insert_i(T value) {
      iterative_insert(value);
    }

    void search_i(T value) {
      Node<T>* search_node = iterative_search(value);
      if(search_node == NULL) {
        cout<<"not found"<<"\n";
        return;
      }

      cout<<"found: "<<search_node->value<<"\n";
    }

    void delete_r(T value) {
      this->root = recursive_delete(this->root, value);
    }

    void search_r(T value) {
      Node<T>* search_node = recursive_search(this->root, value);
      if(search_node == NULL) {
        cout<<"not found"<<"\n";
        return;
      }

      cout<<"found: "<<search_node->value<<"\n";
    }
};

int main (int argc, char *argv[]) {
  //recursive
  BinarySearchTree<int> bst;
  bst.insert(1);
  bst.search_r(1);
  bst.traversal_level();
  bst.delete_r(1);
  bst.search_r(1);
  bst.traversal_level();
  bst.insert(2);
  bst.insert(52);
  bst.insert(21);
  bst.insert(521);
  bst.insert(213);
  bst.insert(-421);
  bst.insert(421421);
  bst.insert(42112);
  bst.traversal_level();

  cout<<"\n";

  BinarySearchTree<int> bst2;
  //iterative
  bst2.insert_i(1);
  bst2.search_i(1);
  bst2.traversal_level();
  bst2.delete_r(1);
  bst2.search_i(1);
  bst2.traversal_level();
  bst2.insert_i(2);
  bst2.insert_i(52);
  bst2.insert_i(21);
  bst2.insert_i(521);
  bst2.insert_i(213);
  bst2.insert_i(-421);
  bst2.insert_i(421421);
  bst2.insert_i(42112);
  bst2.traversal_level();

  return 0;
}
