#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void funkcja(&int xd) {
  coud<<xd;
  //pokaze adres
}

//uzycie jest normalne, po prostu ta funkcja wowczas dziala na adresie nie na kopii tyle nic wiecej filozofii
int elo = 2;
funkcja(elo);

struct Node {
  int value;
  Node* next_node;
};

int main (int argc, char *argv[]) {
  //new alokuje pamiec i od razu tworzy obiekt (przypisuje adres to jest wazne daltego potrzebujemy new i dlatego tez uzywamy wskaznika bo to on przechowuje adres pamieci)
  //malloc np tylko alokowal pamiec, nie tworzyl zadnego obiektu
  Node* node1 = new Node();
  Node* node2 = new Node();
  node1->next_node = node2;
  node2->value = 2;

  cout<<node1->next_node->value<<" "<<node2->value<<"\n";
  //delete wsk;
  //Po wykonaniu tej instrukcji, wartość wskaźnika wsk pozostaje bez zmiany, ale nie można już robić niczego z pamięcią pod tym adresem 
  //- nie jest już nasza. Jak pewnie pamiętasz z lekcji o wskaźnikach, błędna niezerowa wartość wskaźnika jest nieodróżnialna od poprawnej, 
  //więc dobrą praktyką jest wyzerowanie wskaźnika po usunięciu pamięci:
  //delete wsk;
  //wsk = nullptr;
  delete node2;
  //node2 = nullptr;
  //node2->value = 5;







  int x = 232;
  int* px = &x;
  //px->cos to to samo co
  //(*px).cos
  //dereferencja z bomby
  int nums[] = {1, 2, 3, 4, 5};
  //*(nums + 1) to to samo cos
  //nums[1]
  //*nums = nums[0];
  //
  //to po prostu robi dereferencje
  //i dodaje wartosc w nawiasach kwadratowych
  //wiec w sumie mozna w petli robic cos takiego xd
  //nums[i] = i[nums] bo to zrobi
  //*(nums + i) = *(i + nums)
  //to to samo xd
  //
  //
  //
  //
  //
  //
  //malloc, free
  //new, delete
  //delete i free, dlatego powstal garbage collector :)
  //
  //
  //
  //
  //
  //
  //
  //
  //preprocessor is basically a text engine
  //that runs before your file is compiled
  //commonly used with # in .c
  //#include, or macro definition
  //
  #define FOO 123
  //then preprocessor goes over the file (scans)
  //and in the text he is gonna replace every keyword instance
  //FOO with 123
  //FOO = 123
  int e = FOO;

  #define MIN(a, b) ((a) < (b) ? (a) : (b));
  //this looks like a function
  //but this is only TEXT!
  //uzywamy nawiasow zeby matematycznie wszystko zostalo dobrze wywolane
  //i znowu on po prostu zamieni uzycie tego MIN na ten tekst no bo to sie ROZSZERZA (expands) do tego
  int min = MIN(1, 2);
  //int min = MIN(1, 2) ====> int min = 1 < 2 ? 1 : 2
  //czyli makro to nie jest zadna funkcjonalnosc to jest zawsze po prostu syntax sugar
  //taki zamiennik w texcie
  //to tak samo preprocessorem jest sass (scss)
  //on po prostu ladnie bral te klamry z textu i robil z tego fajny css
  //tak samo bral po prostu nazwy zmiennych itd to nie byla jakby zadna nowa funkcjonalnosc

  cout<<node1->next_node->value<<" "<<node2->value<<"\n";

  return 0;
}
