#include "raylib.h"
#include <cmath>

#define WIDTH 900 
#define HEIGHT 600 
#define MAX_REC 10

void draw_line(Vector2 start, float length, float angle, int counter = 0) {
  if(counter == MAX_REC) return;

  float x_cor = sin(-angle) * length;
  float y_cor = cos(angle) * length;

  Vector2 end = {x: start.x + x_cor, y: start.y - y_cor};
  float thicness = length * 0.15;
  DrawLineEx(start, end, thicness, RAYWHITE);

  float scaled_length = length * 0.75;

  draw_line(end, scaled_length, angle + 2*M_PI/11, counter+1);
  draw_line(end, scaled_length, angle - 2*2*M_PI/11, counter+1);
}

int main(void)
{
    SetTargetFPS(1);
    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            //ClearBackground(RAYWHITE);
            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            draw_line({x: WIDTH/2, y: HEIGHT-20}, 130, 0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
