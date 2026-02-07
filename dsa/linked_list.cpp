//linked list allows efficient insertion and deletion operations compared to arrays
//it is a linear type of ds where individual items are not necessarily at contigous locations
//so in fact it is not an array(?) 
//individual items are called nodes and are connected with each other using links
//there are a few types or linked lists: 
//(V - value, L - link)
//singly linked {V, L}
//doubly linked {L, V, L}
//circular LAST_NODE{V, L} Link points to FIRST_NODE

//linked lists are also used to implement stacks and queues 
//(there wouldn't be a need to manually move array left or right every time there is a push, pop, queue, and dequeue)
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

template <typename T>
struct SingleNode {
  T value;
  SingleNode* next;
};

template <typename T>
struct DoubleNode {
  T value;
  DoubleNode* prev;
  DoubleNode* next;
};

template <typename T>
class Stack {
  private:
    SingleNode<T>* head;

  public:
    Stack() {
      head = NULL;
    }

    void push(T value) {
      //needs to be pointer to store address
      //new uzywamy bo to alokuje pamiec i jakby adres
      //wiec gdy chcemy wskaznik musimy uzyc new
      SingleNode<T>* next_node = new SingleNode<T>();
      next_node->value = value;
      next_node->next = head;
      
      head = next_node;
    }

    T pop() {
      SingleNode<T>* curr_node = head;

      T item = curr_node->value;
      head = head->next;

      delete curr_node;
      return item;
    }
};

template <typename T>
class Queue {
  private:
    SingleNode<T>* head;
    SingleNode<T>* tail;
  public:
    Queue() {
      head = NULL;
      tail = NULL;
    }

    void enqueue(T value) {
      SingleNode<T>* next_node = new SingleNode<T>();
      next_node->value = value;
      next_node->next = NULL;
      if(head == NULL) {
        head = next_node;
        tail = next_node;
      } else {
        tail->next = next_node;
        tail = next_node;
      }
    }

    T dequeue() {
      SingleNode<T> *temp = head;
      T ret_value = temp->value;

      if(head != NULL) {
        head = head->next;

        delete temp;
      } else {
        head = tail = NULL;
      }

      return ret_value;
    } 
};

int main() {
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.push(4);

  int pop1 = stack.pop();
  int pop2 = stack.pop();
  int pop3 = stack.pop();
  int pop4 = stack.pop();

  cout<<"pop1: "<<pop1<<"\n"<<"pop2: "<<pop2<<"\n"<<"pop3: "<<pop3<<"\n"<<"pop4: "<<pop4<<"\n";



  Queue<int> queue;
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.enqueue(4);

  int dequeue1 = queue.dequeue();
  int dequeue2 = queue.dequeue();
  int dequeue3 = queue.dequeue();
  int dequeue4 = queue.dequeue();

  cout<<"dequeue1: "<<dequeue1<<"\n"<<"dequeue2: "<<dequeue2<<"\n"<<"dequeue3: "<<dequeue3<<"\n"<<"dequeue4: "<<dequeue4<<"\n";
}
