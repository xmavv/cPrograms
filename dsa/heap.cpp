#include <stdio.h>
#include <vector>
#include <climits>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

//heap is a complete binary tree
//heap is good for storing arr values when we need to put or extract min or MaxHeapStrategy
//instead in classic array we would need to sort array each time
//this is more efficient


//safer enum class
//and then we have to use :: scope resolution operator
//operator zakresu
enum class HeapType {
  MAX,
  MIN
};

enum class SortType {
  ASC,
  DSC
};

template <typename T>
class Heap;

template <typename T>
class IHeapStrategy {
  protected:
    Heap<T>* heap;
  public:
    IHeapStrategy(Heap<T>* h) : heap(h) {}
    virtual bool compare(T parent, T child) = 0;
    virtual void change_key(unsigned int i, T value) = 0;
    virtual void delete_key(unsigned int i) = 0;
    virtual vector<T> sort(SortType sortType) = 0;
};

template <typename T>
class MinHeapStrategy: public IHeapStrategy<T> {
  public:
    //wywolanie konstruktora
    using IHeapStrategy<T>::IHeapStrategy;

    bool compare(T parent, T child) {
      return parent < child;
    }

    void change_key(unsigned int i, T value) {
      T prev_value = this->heap->get_value(i);
      this->heap->set_value(i, value);

      if(prev_value < value) {
        this->heap->heapify_down(i);
      } else {
        this->heap->heapify_top(i);
      }
    }

    void delete_key(unsigned int i) {
      change_key(i, INT_MIN);
    }

    vector<T> sort(SortType sortType) {
      vector<T> sorted_arr;
      int size = this->heap->get_size();
  
      for(int i=0; i<size; i++) {
        sorted_arr.push_back(this->heap->extract_root());
      }

      if(sortType == SortType::DSC) reverse(sorted_arr.begin(), sorted_arr.end());
      return sorted_arr;
    }
};

template <typename T>
class MaxHeapStrategy: public IHeapStrategy<T> {
  public:
    //wywolanie konstruktora
    using IHeapStrategy<T>::IHeapStrategy;

    bool compare(T parent, T child) {
      return parent > child;
    }

    void change_key(unsigned int i, T value) {
      T prev_value = this->heap->get_value(i);
      this->heap->set_value(i, value);

      if(prev_value > value) {
        this->heap->heapify_down(i);
      } else {
        this->heap->heapify_top(i);
      }
    }

    void delete_key(unsigned int i) {
      change_key(i, INT_MAX);
    }

    vector<T> sort(SortType sortType) {
      vector<T> sorted_arr;
      int size = this->heap->get_size();
  
      for(int i=0; i<size; i++) {
        sorted_arr.push_back(this->heap->extract_root());
      }

      if(sortType == SortType::ASC) reverse(sorted_arr.begin(), sorted_arr.end());
      return sorted_arr;
    }
};

template <typename T>
class Heap {
  private:
    vector<T> arr;
    int capacity;
    //this is not really necessary since we have hs, but its easier to code
    //not checking the type of hs;
    HeapType ht;
    IHeapStrategy<T>* hs;

  protected:
    static void swap(T& value1, T& value2) {
      value1 = value1 ^ value2;
      value2 = value2 ^ value1;
      value1 = value1 ^ value2;
    }
      public:
    Heap(int capacity, HeapType ht = HeapType::MAX) {
      //capacity == -1 means dynamic heap
      this->capacity = capacity;
      this->ht = ht;
      if(ht == HeapType::MAX) {
        this->hs = new MaxHeapStrategy<T>(this);
      } else {
        this->hs = new MinHeapStrategy<T>(this);
      }
    }

    void heapify_down(unsigned int i) {
      int left_child = get_left(i);
      int right_child = get_right(i);

      int min_or_max = i;
      if(left_child < arr.size() && hs->compare(arr[left_child], arr[i])) {
        min_or_max = left_child;
      } 
      if(right_child < arr.size() && hs->compare(arr[right_child], arr[min_or_max])) {
        min_or_max = right_child;
      }
      if(min_or_max != i) {
        swap(arr[i], arr[min_or_max]);
        heapify_down(min_or_max);
      }
    }

    //should be static but using this strategy, and cannot do it without creating new obj
    void heapify_down(unsigned int i, vector<T>& arr) {
      int left_child = get_left(i);
      int right_child = get_right(i);

      int min_or_max = i;
      if(left_child < arr.size() && hs->compare(arr[left_child], arr[i])) {
        min_or_max = left_child;
      } 
      if(right_child < arr.size() && hs->compare(arr[right_child], arr[min_or_max])) {
        min_or_max = right_child;
      }
      if(min_or_max != i) {
        swap(arr[i], arr[min_or_max]);
        heapify_down(min_or_max, arr);
      }
    }

    void heapify_top(unsigned int i) {
      //here we do not assure that values are equal
      while(i != 0 && !hs->compare(arr[get_parent(i)], arr[i])) {
        swap(arr[get_parent(i)], arr[i]);
        i = get_parent(i);
      }
    }

    int get_parent(unsigned int i) {
      unsigned int parent = (i-1)/2;
      return parent >= 0 ? parent : 0;
    }

    int get_left(unsigned int i) {
      int left = (i*2)+1;
      return left;
    }

    int get_right(unsigned int i) {
      int right = (i*2)+2;
      return right;
    }

    T get_value(unsigned int i) {
      return arr[i];
    }

    vector<T> get_arr() {
      return arr;
    }

    void set_value(unsigned int i, T value) {
      arr[i] = value;
    }

    bool is_min_heap() {
      return ht == HeapType::MIN;
    }

    void convert_to_min_heap() {
      if(is_min_heap()) return;
      ht = HeapType::MIN;
      delete hs;
      hs = new MinHeapStrategy<T>(this);

      floyd();
    }

    void convert_to_max_heap() {
      if(!is_min_heap()) return;
      ht = HeapType::MAX;
      delete hs;
      hs = new MaxHeapStrategy<T>(this);

      floyd();
    }

    bool is_full() {
      if(capacity == -1) return false;
      return capacity >= arr.size();
    }

    bool is_empty() {
      return !arr.size();
    }

    unsigned int get_size() {
      return arr.size();
    }

    unsigned int get_height() {
      return floor(log2(arr.size())) + 1;
    }

    T extract_root() {
      T root = arr[0];
      arr[0] = arr.back();
      arr.pop_back();

      heapify_down(0);
      return root;
    }

    int get_root() {
      return arr[0];
    }

    void print_arr() {
      for(T e: arr) {
        cout << e << " ,";
      }

      cout<<"\n\n";
    }


    static void print_arr(vector<T>& arr) {
      for(T e: arr) {
        cout << e << " ,";
      }

      cout<<"\n\n";
    }

    void insert(T value) {
      if(is_full()) return;

      arr.push_back(value);

      heapify_top(arr.size() - 1);
    }

    void change_key(unsigned int i, T value) {
      hs->change_key(i, value);
    }

    void delete_key(unsigned int i) {
      //we are doing both repair top and then repairing down
      //we can just change i element with last element and then do 
      //chhange_key(i, lastelement_value)
      //i wczesniej jak przeniesiemy ten element ktory chcemty usunac na koniec to
      //bierzemy jego wartoscsc i zmniejszamy vector
      T substitute = arr.back();
      arr.pop_back();
      hs->change_key(i, substitute);

      //OR

      //hs->delete_key(i, INT_MAX);
      //extract_root();
    }

    void floyd() {
      unsigned int last_child_index = arr.size() - 1;
      unsigned int last_parent_index = get_parent(last_child_index);

      for(int i=last_parent_index; i>=0; i--) {
        heapify_down(i);
      }
    }

    vector<T> floyd(vector<T> whole_arr) {
      //creating a heap from full array
      //floyd algorithm is better that primitive algorithm that uses O(nlogn)
      //when floyd just uses O(n)
      ////////////////czy to nie jest puszczenie heapify_top dla wszystkich dzieci na ostatnim poziomie? to sie da obliczyc bo mozna miec height
      
      //Proszę zauważyć, że ciąg wierzchołków do rozpatrzenia jest obszarem ciągłym w tablicy
      //(od ostatniego rodzica do elementu pierwszego)
      //ZAJEBISTE 
      
      unsigned int last_child_index = whole_arr.size() - 1;
      unsigned int last_parent_index = get_parent(last_child_index);

      for(int i=last_parent_index; i>=0; i--) {
        heapify_down(i, whole_arr);
      }

      return whole_arr;
    }

    vector<T> sort(SortType sortType = SortType::ASC) {
      vector<T> preserved_arr = arr;
      vector<T> sorted_arr = hs->sort(sortType);

      arr = preserved_arr;
      return sorted_arr;
    }
};

int mainxd (int argc, char *argv[]) {
  cout<<boolalpha;
  Heap<int> heap(-1, HeapType::MIN);
  bool is_full = heap.is_full();
  cout << "is_full: " << is_full << "\n";
  bool is_min = heap.is_min_heap();
  cout << "is_min: " << is_min << "\n";

  heap.insert(5);
  int value = heap.get_value(0);
  cout << "value: " <<value << "\n";

  int root = heap.get_root();
  cout << "root: " << root << "\n";
  bool is_empty = heap.is_empty();
  cout << "is_empty: " << is_empty << "\n";
  int extract = heap.extract_root();
  cout << "extract: " << extract << "\n";
  is_empty = heap.is_empty();
  cout << "is_empty: " << is_empty << "\n";

  //napisac po co w ogole jest ten heap
  //wyprobowac wszystkie funkcje
  heap.insert(5);
  heap.insert(1);
  heap.insert(7);
  heap.insert(2);
  heap.insert(3);
  heap.insert(11);
  //heap.insert(4);
  //heap.insert(6);
  heap.print_arr();

  int last_index = heap.get_size() - 1;
  heap.change_key(last_index, 10);
  heap.print_arr();

  heap.change_key(last_index, 8);
  heap.print_arr();

  heap.change_key(last_index, 0);
  heap.print_arr();

  heap.delete_key(last_index);
  heap.print_arr();

  heap.delete_key(2);
  heap.print_arr();


  vector<int> normal_arr = {7, 74, 421, 425, 65231, 632, 1, 6, 5, 24};
  heap.print_arr(normal_arr);
  vector<int> heap_arr = heap.floyd(normal_arr);
  heap.print_arr(heap_arr);

  heap.convert_to_max_heap();
  heap.delete_key(2);
  heap.print_arr();

  cout<<"height: "<<heap.get_height()<<"\n";
  heap.insert(9);
  heap.extract_root();
  heap.delete_key(3);
  heap.insert(25);
  heap.insert(7);
  cout<<"height: "<<heap.get_height()<<"\n";

  heap.convert_to_min_heap();
  heap.print_arr();

  cout<<"sorting: \n";
  heap.insert(35);
  heap.insert(2521);
  heap.insert(253421);
  heap.insert(232);
  heap.insert(123);
  heap.insert(521);

  vector<int> sorted_arr = heap.sort();
  heap.print_arr(sorted_arr);
  sorted_arr = heap.sort(SortType::DSC);
  heap.print_arr(sorted_arr);

  heap.print_arr();
  cout<<heap.is_empty()<<"\n";

  heap.convert_to_max_heap();
  heap.print_arr();
  return 0;
};

