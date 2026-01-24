#include <stdio.h>
#include <stdlib.h>

void odwroc_kolejnosc_trywialne(char* nazwa_pliku) {
  FILE* file;
  file = fopen(nazwa_pliku, "r");

  //nie ma potrzeby alokowania dynamicznej pamieci bo wiemy dokladnie ile chcemy miec
  //statycznie mozna tylko gdy w czasie compilacji gcc bedzie wiadomo ile mamy danych liczb
  //char* buffer2 = malloc(sizeof(char) * 3);

  //traz moge robic realloca, albo policzyc ile jest tych liczb
  //trzeba policzyc ilosc spacji + 1
  //glupota bo i tak trzeba to robic dynamicznie czytajac liczbe po prostu za kazdym razem z charow wiec nie mozna tak tego zrobic

  //tutaj licze ilosc spacji
  //fgets, freads, fscanf, getline z wszystkiego mozna skorzystac
  
  ///atoi przy za duzych liczbach gdy jest overflow po prostu obetnie te za duze czesci, weic liczby musza sie miesic faktycznie w 32b
  
  //wychodzi na to ze to nie jest zbyt dobre rozwiazanie xd, bo malloc tworzy stack i on jest bardzo zapelniony przy ciaglym reallocowaniu

  fseek(file, 0, SEEK_END);
  long rozmiar = ftell(file);
  char* buffer = malloc(sizeof(char) * rozmiar);
  fseek(file, 0, SEEK_SET);

  fread(buffer, 1, rozmiar, file);
  int liczba_spacji = 0;
  int dlugosc_liczby = 0;

  int* tablica_liczb;
  char* tymczasowa_liczba;

  for(int i=0; i<rozmiar; i++) {
    char character = buffer[i];

    if((int)character == 32) {
 //     free(tablica_liczb);
      tablica_liczb = realloc(tablica_liczb, sizeof(int) * liczba_spacji+1);
      tablica_liczb[liczba_spacji] = atoi(tymczasowa_liczba);

      dlugosc_liczby = 0;
    //  free(tymczasowa_liczba);
      tymczasowa_liczba = NULL;
      liczba_spacji++;
    } else {
      tymczasowa_liczba = realloc(tymczasowa_liczba, sizeof(char) * dlugosc_liczby+1);

      tymczasowa_liczba[dlugosc_liczby] = character;
      dlugosc_liczby++;
    }
  }

  tablica_liczb = realloc(tablica_liczb, sizeof(int) * liczba_spacji + 1);
  tablica_liczb[liczba_spacji] = atoi(tymczasowa_liczba);liczba_spacji++;
  free(tymczasowa_liczba);

  for(int i=0; i<liczba_spacji/2; i++) {
    tablica_liczb[i] = tablica_liczb[i] ^ tablica_liczb[liczba_spacji-i-1];
    tablica_liczb[liczba_spacji-i-1] = tablica_liczb[liczba_spacji-i-1] ^ tablica_liczb[i] ;
    tablica_liczb[i] = tablica_liczb[i] ^ tablica_liczb[liczba_spacji-i-1];
  }

  printf("%s", "reversed arr\n");
  for(int i=0; i<liczba_spacji; i++) {
   printf("%d\n", tablica_liczb[i]);
  }

  free(tablica_liczb);
  fclose(file);
}

void odwroc_kolejnosc_lepsze() {
  //tutaj chce zrobic ze bede na jednym loopie czytal ostatnia liczbe do spacji
  //potem bede ja zapisywal na poczatek pliku
  //i trzymal ten wskaznik z fseeka i ftella
}

int main() {
  char* nazwa = "liczby.bin";
  odwroc_kolejnosc_trywialne(nazwa);

  return 0;
}
