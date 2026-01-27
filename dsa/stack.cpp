#include <iostream>
using namespace std;
//malloc vs new
//malloc only allocates memory
//new is allocating memory and creating related object, thats why in other languages we use new operator!

template<typename T>
class Stack {
  private:
    T* arr;

  public:
    int capacity = 0;
    int item_count = 0;

    //if capacity == -1 then its dynamic
    //Stack() {}
    Stack(int capacity) {
      this->capacity = capacity;
      this->arr = new T[capacity];
    }

    bool push(T item) {
      if(this->item_count >= this->capacity) return false;

      this->arr[this->item_count] = item;
      this->item_count++;
      return true;
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
  Stack<int> stack(5);
  int poped = stack.pop();
  bool push1 = stack.push(2);
  int poped2 = stack.pop();
  bool push2 = stack.push(3);
  bool push3 = stack.push(45);
  bool push4 = stack.push(512);
  bool push5 = stack.push(241);
  bool push6 = stack.push(123);
  bool isEmpty1 = stack.is_empty();
  cout<<"isempty1"<<isEmpty1<<"\n";
  bool push7 = stack.push(555);
  bool push8 = stack.push(555);
  bool push9 = stack.push(555);
  int peeked1 = stack.peek();
  int poped3 = stack.pop();
  cout<<"peeked"<<peeked1<<"\n"<<"poped"<<poped3<<"\n";
  int poped4 = stack.pop();
  int poped5 = stack.pop();
  stack.pop();
  stack.pop();
  bool isEmpty2 = stack.is_empty();
  cout<<"isempty2"<<isEmpty2<<"\n";

  cout<<poped<<"\n"<<poped2<<"\n"<<poped3<<"\n"<<poped4<<"\n"<<poped5<<"\n\n\n\n";
  cout<<push1<<"\n"<<push2<<"\n"<<push3<<"\n"<<push4<<"\n"<<push5<<"\n"<<push6<<"\n"<<push7<<"\n"<<push8<<"\n"<<push9<<"\n";
}
