#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <wchar.h>

// Function to generate a random number
unsigned int getRandom() {
  unsigned int tmp;

  if (getrandom(&tmp, sizeof(unsigned int), 0) == -1) {
    perror("getrandom");
    exit(EXIT_FAILURE);
  }

  return tmp;
}

int printRandomDigitMatrix(int column, int row, int width) {
  for (int i = 0; i < row; i = i + 1) {
    for (int j = 0; j < column; j = j + 1) {
      for (int k = 0; k < width; k = k + 1) {
        printf("%d", getRandom() % 10);
      }
      printf("\t");
    }
    printf("\n");
  }
  return 0;
}

// Function to shuffle the array of cards
void shuffle(wchar_t **array, size_t n) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + getRandom() % (n - i);
      wchar_t *t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int card_shuffle() {
  // Set the locale to support wide characters
  setlocale(LC_ALL, "");

  // Define the array of cards
  // wchar_t cards[totalCards] = L"🂡🂢🂣🂤🂥🂦🂧🂨🂩🂪🂫🂭🂮"
  // L"🂱🂲🂳🂴🂵🂶🂷🂸🂹🂺🂻🂽🂾"
  // L"🃁🃂🃃🃄🃅🃆🃇🃈🃉🃊🃋🃍🃎"
  // L"🃑🃒🃓🃔🃕🃖🃗🃘🃙🃚🃛🃝🃞";

  wchar_t *deck[] = {L"♥️1",  L"♥️2",  L"♥️3", L"♥️4",  L"♥️5", L"♥️6", L"♥️7",  L"♥️8",
                     L"♥️9",  L"♥️10", L"♥️J", L"♥️Q",  L"♥️K", L"♦️1", L"♦️2",  L"♦️3",
                     L"♦️4",  L"♦️5",  L"♦️6", L"♦️7",  L"♦️8", L"♦️9", L"♦️10", L"♦️J",
                     L"♦️Q",  L"♦️K",  L"♠️1", L"♠️2",  L"♠️3", L"♠️4", L"♠️5",  L"♠️6",
                     L"♠️7",  L"♠️8",  L"♠️9", L"♠️10", L"♠️J", L"♠️Q", L"♠️K",  L"♣️1",
                     L"♣️2",  L"♣️3",  L"♣️4", L"♣️5",  L"♣️6", L"♣️7", L"♣️8",  L"♣️9",
                     L"♣️10", L"♣️J",  L"♣️Q", L"♣️K"};

  // Shuffle the cards
  int totalCards = sizeof(deck) / sizeof(deck[0]);
  shuffle(deck, totalCards);

  // Print the shuffled cards
  for (int i = 0; i < totalCards; i++) {
    wprintf(L"%ls \t", deck[i]);
    // if ((i + 1) % width == 0) {
    //   wprintf(L"\t");
    // }
    if ((i + 1) % 4 == 0) { // Print a newline every 13 cards
      wprintf(L"\n");
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  printRandomDigitMatrix(4, 13, 2);
  card_shuffle();
  return 0;
}