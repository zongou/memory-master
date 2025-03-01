#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <unistd.h>

int period = 0;

void periodically_output(int period) {
  usleep(period); // Sleep for 1000 milliseconds (1 second)
  fflush(stdout);
}

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
      periodically_output(period);
      printf("\t");
    }
    printf("\n");
  }
  return 0;
}

// Function to shuffle the array of cards
void shuffle(char **array, size_t n) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + getRandom() % (n - i);
      char *t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int card_shuffle() {
  char *suits[] = {"♥️", "♦️", "♠️", "♣️"};
  char *ranks[] = {"1", "2", "3", "4", "5", "6", "7",
                   "8", "9", "0", "J", "Q", "K"};
  char *deck[52];
  int index = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      deck[index++] = (char *)malloc((strlen(suits[i]) + strlen(ranks[j]) + 1) *
                                     sizeof(char));
      strcpy(deck[index - 1], ranks[j]);
      strcat(deck[index - 1], suits[i]);
    }
  }

  // Shuffle the cards
  int totalCards = sizeof(deck) / sizeof(deck[0]);
  shuffle(deck, totalCards);

  // Print the shuffled cards
  for (int i = 0; i < totalCards; i++) {
    printf("%s \t", deck[i]);
    periodically_output(period);
    if ((i + 1) % 4 == 0) { // Print a newline every 4 cards
      printf("\n");
    }
    free(deck[i]); // Free allocated memory
  }
  return 0;
}

int main(int argc, char *argv[]) {
  char *help_info = "\
Memory Master\n\
\n\
Usage:\n\
  memory-master [COMMANDS]... [OPTION]...\n\
\n\
Commands:\n\
  n, numbers\n\
      print random numbers\n\
  c, cards\n\
      print shuffled cards\n\
Options:\n\
  -h, --help\n\
      display this help and exit\n\
  -p, --period=SECONDS\n\
      sleep for SECONDS milliseconds between each output\n\
\n\
Examples:\n\
 memory-master numbers cards\n\
";

  static struct option long_options[] = {
      {"help", no_argument, NULL, 'h'},
      {"period", required_argument, NULL, 'p'},
      {NULL, 0, NULL, 0}};

  int c;
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "hp:", long_options, &option_index)) !=
         -1) {
    switch (c) {
    case 0:
      break;
    case 'h':
      fputs(help_info, stderr);
      return EXIT_SUCCESS;
    case 'p':
      period = atoi(optarg) * 1000;
      break;
    default:
      abort();
    }
  }

  /* Print any remaining command line arguments (not options). */
  if (optind < argc) {
    while (optind < argc) {
      if (strcmp("n", argv[optind]) == 0 ||
          strcmp("numbers", argv[optind]) == 0) {
        printRandomDigitMatrix(4, 13, 2);
      }
      if (strcmp("c", argv[optind]) == 0 ||
          strcmp("cards", argv[optind]) == 0) {
        card_shuffle();
      }
      optind = optind + 1;
    }
  } else {
    printRandomDigitMatrix(4, 13, 2);
    card_shuffle();
  }

  return 0;
}
