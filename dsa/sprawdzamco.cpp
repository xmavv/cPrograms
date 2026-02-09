#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

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
  //delete node2;
  //node2 = nullptr;
  node2 = new Node();
  node2->value = 5;

  cout<<node1->next_node->value<<" "<<node2->value<<"\n";

  return 0;
}
