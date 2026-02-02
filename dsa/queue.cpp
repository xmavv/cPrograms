#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
//malloc vs new
//malloc only allocates memory
//new is allocating memory and creating related object, thats why in other languages we use new operator!

template<typename T>
class AllocationStrategy {
  public:
    virtual bool enqueue(T*& arr, int& item_count, int& capacity, T item) = 0;
};

template<typename T>
class StaticAllocationStrategy : public AllocationStrategy<T> {
  public:
    bool enqueue(T*& arr, int& item_count, int& capacity, T item) {
      if(item_count >= capacity) return false;

      arr[item_count] = item;
      item_count++;
      return true;
    };
};

template<typename T>
class DynamicAllocationStrategy : public AllocationStrategy<T> {
  public:
    bool enqueue(T*& arr, int& item_count, int& capacity, T item) {
      //oczywiscie mozna by uzywac wskaznikow ale my jestesmy koty i piszemy sami
      T* newArr = new T[item_count+1];

      for(int i=0; i<item_count; i++) {
        newArr[i] = arr[i];
      }

      newArr[item_count] = item;

      delete[] arr;
      arr = newArr;

      item_count++;
      return true;
    };
};

template<typename T>
class Queue {
  private:
    T* arr;
    AllocationStrategy<T>* strategy;

  public:
    int capacity = 0;
    int item_count = 0;

    //if capacity == -1 then its dynamic
    Queue() {
      this->capacity = -1;
      this->strategy = new DynamicAllocationStrategy<T>();
    }

    Queue(int capacity) {
      this->capacity = capacity;

      if(capacity == -1) {
        this->arr = new T[0];
        this->strategy = new DynamicAllocationStrategy<T>();
      } 
      else {
        this->arr = new T[capacity];
        this->strategy = new StaticAllocationStrategy<T>();
      }
    }

    bool enqueue(T item) {
      return strategy->enqueue(this->arr, this->item_count, this->capacity, item);
    }

    T dequeue() {
      if(item_count > 0) this->item_count--;
      T saved_item = this->arr[0];

      for(int i=0; i<item_count; i++) {
        arr[i] = arr[i+1];
      }

      //for dynamic allocation we decrease the size of array
      if(capacity == -1) {
        T* newArr = new T[item_count]; 

        for(int i=0; i<item_count; i++) {
          newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
      }

      return saved_item;
    }

    T peek() {
      return this->arr[0];
    }

    bool is_empty() {
      return this->item_count == 0;
    }
};

int main() {
  Queue<int> queue(-1);
  int isEmpty = queue.is_empty();
  cout<<"empty: "<<isEmpty<<"\n";
  int dequeued = queue.dequeue();
  cout<<"dequeued: "<<dequeued<<"\n";

  bool queued = queue.enqueue(5);
  cout<<"queued: "<<queued<<"\n";
  bool queued2 = queue.enqueue(6);
  cout<<"queued2: "<<queued2<<"\n";
  bool queued3 = queue.enqueue(1);
  cout<<"queued3: "<<queued3<<"\n";

  int dequeue1 = queue.dequeue();
  cout<<"dequeue1: "<<dequeue1<<"\n";
  int dequeue2 = queue.dequeue();
  cout<<"dequeue2: "<<dequeue2<<"\n";
  int dequeue3 = queue.dequeue();
  cout<<"dequeue3: "<<dequeue3<<"\n";


  Queue<float> queueStatic(2);
  queueStatic.enqueue(55.5);
  queueStatic.enqueue(777.21);
  float dequeueek1 = queueStatic.dequeue();
  float dequeueek2 = queueStatic.dequeue();
  cout<<"dequeueek1: "<<dequeueek1<<"\n";
  cout<<"dequeueek2: "<<dequeueek2<<"\n";
}
