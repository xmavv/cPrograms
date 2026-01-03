#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void KOPIUJ_DODATNIE(int* A, int rozmiar_A, int* B, int rozmiar_B) {
  printf("%s", "tablica b\n");

  for(int i=0; i<rozmiar_A; i++) {
    if(*A > 0) {
      *B = *A;
      printf("%i | ", *B);
      B++;
    }

    A++;
  }
}

void UTWORZ_TABLICE(int rozmiar_A) {
  int* buffer = malloc(sizeof(int) * rozmiar_A);
  int* zachowaj_buffer = buffer;
  int ilosc_dodatnich = 0;

  srand(time(NULL));
  printf("%s", "tablica a\n");

  for (int i=0; i<rozmiar_A; i++) {
    int randomowa = rand()%101 - 50;
    if(randomowa > 0) {
      ilosc_dodatnich++;
    }

    *buffer = randomowa;
    printf("%i | ", *buffer);
    buffer++;
  }

  int* tablica_b = malloc(sizeof(int) * ilosc_dodatnich);
  KOPIUJ_DODATNIE(zachowaj_buffer, rozmiar_A, tablica_b, ilosc_dodatnich);

  free(zachowaj_buffer);
}

int main() {
  int rozmiar_tablicy_a = 100;

  UTWORZ_TABLICE(rozmiar_tablicy_a);

  return 0;
}
