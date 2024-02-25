#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

int main() {
  unsigned int tmp;

  getrandom(&tmp, sizeof(unsigned int), GRND_NONBLOCK) == -1
      ? perror("getrandom")
      : "";
  printf("%u\n", tmp);

  exit(EXIT_SUCCESS);
}