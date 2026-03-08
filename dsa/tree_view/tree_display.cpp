#include "raylib.h"
#include <cmath>
#include <string>
#include <vector>

#include "../heap.cpp"

using namespace std;

#define WIDTH 900 
#define HEIGHT 600 

template <typename T>
void draw_node(Vector2 cords, float factor, T value) {
  string s = to_string(value);
  const int len = s.length();
  const char* text = s.c_str();
  const int font_size = 20;
    
  DrawCircleLines(cords.x, cords.y, 30, RAYWHITE);
  DrawText(text, cords.x - font_size/2, cords.y - font_size/2, 20, RAYWHITE);
}

//array in level order
template <typename T>
void draw_tree(vector<T> arr) {
  if(arr.size() < 1) return;

  for(int i=1; i<arr.size(); i*=2) {
    float factor = log2(i) == 0 ? 1 : log2(i);
    for(int j=i-1; j<2*i-1; j++) {
      if(j >= arr.size()) return;
      draw_node({x: WIDTH/2 - i*2*50 + j*67, y: log2(i)*70 + 100}, 1/factor, arr[j]);
    }
  }
}

int main(void)
{
    SetTargetFPS(1);
    InitWindow(800, 450, "raylib [core] example - basic window");

    Heap<int> heap(-1);
    heap.insert(5612);
    heap.insert(21);
    heap.insert(621);
    heap.insert(123);
    heap.insert(854);
    heap.insert(743);
    heap.insert(1);
    heap.insert(555);
    heap.insert(552);
    heap.insert(553);
    heap.insert(554);

    vector<int> arr = heap.get_arr();

    while (!WindowShouldClose())
    {
        BeginDrawing();
            draw_tree(arr);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
