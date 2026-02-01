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
    virtual bool push(T*& arr, int& item_count, int& capacity, T item) = 0;
};

template<typename T>
class StaticAllocationStrategy : public AllocationStrategy<T> {
  public:
    bool push(T*& arr, int& item_count, int& capacity, T item) {
      if(item_count >= capacity) return false;

      arr[item_count] = item;
      item_count++;
      return true;
    };
};

template<typename T>
class DynamicAllocationStrategy : public AllocationStrategy<T> {
  public:
    bool push(T*& arr, int& item_count, int& capacity, T item) {
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
class Stack {
  private:
    T* arr;
    AllocationStrategy<T>* strategy;

  public:
    int capacity = 0;
    int item_count = 0;

    //if capacity == -1 then its dynamic
    Stack() {
      this->capacity = -1;
      this->strategy = new DynamicAllocationStrategy<T>();
    }

    Stack(int capacity) {
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

    bool push(T item) {
      return strategy->push(this->arr, this->item_count, this->capacity, item);
    }

    T pop() {
      if(item_count > 0) this->item_count--;
      return this->arr[this->item_count];
    }

    T peek() {
      return this->arr[this->item_count-1];
    }

    bool is_empty() {
      return this->item_count == 0;
    }
};

int main() {
  Stack<int> stack(-1);
  int isEmpty = stack.is_empty();
  cout<<"empty: "<<isEmpty<<"\n";
  int poped = stack.pop();
  cout<<"poped: "<<poped<<"\n";

  bool pushed = stack.push(5);
  cout<<"pushed: "<<pushed<<"\n";
  bool pushed2 = stack.push(6);
  cout<<"pushed2: "<<pushed2<<"\n";
  bool pushed3 = stack.push(1);
  cout<<"pushed3: "<<pushed3<<"\n";

  int pop1 = stack.pop();
  cout<<"pop1: "<<pop1<<"\n";
  int pop2 = stack.pop();
  cout<<"pop2: "<<pop2<<"\n";
  int pop3 = stack.pop();
  cout<<"pop3: "<<pop3<<"\n";


  Stack<float> stackStatic(2);
  stackStatic.push(55.5);
  stackStatic.push(777.21);
  float popek1 = stackStatic.pop();
  float popek2 = stackStatic.pop();
  cout<<"popek1: "<<popek1<<"\n";
  cout<<"popek2: "<<popek2<<"\n";
}
