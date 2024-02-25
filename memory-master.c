
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

/* Flag set by ‘--help’. */
char *program_name;

struct {
  int help_flag;
  int column;
  int row;
  int width;
} options;

double power(int x, unsigned n) {
  // Initialize result to 1
  double pow = 1;

  // Multiply x for n times
  for (int i = 0; i < n; i++) {
    pow = pow * x;
  }

  return pow;
}

int getRandomNumbers(int width) {
  unsigned int tmp;

  getrandom(&tmp, sizeof(unsigned int), GRND_NONBLOCK) == -1
      ? perror("getrandom")
      : "";

  do {
    tmp = tmp / 10;
  } while (tmp >= power(10, width));

  return tmp;
}

int getRandomNumbersMatrix(int column, int row, int width) {
  for (int j = row; j > 0; j = j - 1) {
    for (int i = column; i > 0; i = i - 1) {
      printf("%d\t", getRandomNumbers(width));
    }
    printf("\n");
  }
  return 0;
}

void show_help() {
  fprintf(stderr, "\
Memory master traning.\n\
Usage:\n\
  %s [options]\n\n",
          program_name);

  fprintf(stderr, "\
Options:\n\
  -c, --column [val]    \tlist display devices.\n\
  -r, --row [val]       \twatch brightness change and apply icc profile.\n\
  -w, --width [val]     \tapply brightness profile.\n\
\n\
  --help                \tshow this help.\n");
}

int main(int argc, char **argv) {
  program_name = argv[0];

  if (argc == 1) {
    show_help();
    exit(EXIT_FAILURE);
  }

  int c;

  while (1) {
    static struct option long_options[] = {
        /* These options set a flag. */
        {"help", no_argument, &options.help_flag, 1},
        /* These options don’t set a flag.
           We distinguish them by their indices. */
        {"column", required_argument, 0, 'c'},
        {"row", required_argument, 0, 'r'},
        {"width", required_argument, 0, 'd'},
        {0, 0, 0, 0}};
    /* getopt_long stores the option index here. */
    int option_index = 0;

    c = getopt_long(argc, argv, "c:r:w:", long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;

    switch (c) {
    case 0:
      /* If this option set a flag, do nothing else now. */
      if (long_options[option_index].flag != 0)
        break;
      printf("option %s", long_options[option_index].name);
      if (optarg)
        printf(" with arg %s", optarg);
      printf("\n");
      break;

    case 'c':
      options.column = atoi(optarg);
      break;

    case 'r':
      options.row = atoi(optarg);
      break;

    case 'w':
      options.width = atoi(optarg);
      break;

    case '?':
      /* getopt_long already printed an error message. */
      break;

    default:
      abort();
    }
  }
  if (options.help_flag)
    show_help();

  /* Print any remaining command line arguments (not options). */
  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    putchar('\n');
  }

  getRandomNumbersMatrix(options.column, options.row, options.width);

  exit(EXIT_SUCCESS);
}