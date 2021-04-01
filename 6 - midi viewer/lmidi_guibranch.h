/* legend
	
	define draw_method as the corresponding macro based on the platform to build
	DRAW_NCONS: building to console with native libraries.
	DRAW_NCURS: building to console with ncurses libraries + native.
	DRAW_GRAPH: building to sdl (in progress).

*/

#define DRAW_NCONS 1
#define DRAW_NCURS 2
#define DRAW_GRAPH 3

int draw_method = DRAW_NCONS;

int strpos(char * hay, char * needle, int offset) {
  char haystack[strlen(hay)];
  strncpy(haystack, hay + offset, strlen(hay) - offset);
  char * p = strstr(haystack, needle);
  if (p)
    return p - haystack + offset;
  return -1;
}

typedef struct mid_file {
  //
  int nmtrk;
  // raw data of midi file
  char * string;
  int strlen;
  // mtrk data
  char * mtrk_n;
  char * mtrk_smpte;
  int * mtrk_dat;
  int mtrk_pos[100];
  // byte reading positions after smpte for every track chunk
  char * mtrk_brpos;
  // char at end of struct for return value(?)
  char nterm;

}
mid_file;

void feedback(char * string) {

  if (draw_method == DRAW_NCONS) {
    if (string == "fopen_success") {
      printf("file opened succesfully");
    }
    if (string == "fopen_fail") {
      printf("file couldn't be opened: erroneous filename.");
    }
  }
}

int * read_file2(char * string) {
  FILE * fp;
  char filename[20] = "example.mid";
  fp = fopen(filename, "rb");

  fseek(fp, 0, SEEK_END);
  int filelen = ftell(fp);
  rewind(fp);

  char charin[1];

  string = (char * ) malloc(filelen * sizeof(char) * 2);

  //check if file was opened successfully
  if (fp) {
    // if successful, parse the file data
    for (int i = 1; i != filelen + 1; i++) {
      charin[0] = fgetc(fp);
      charin[1] = ' ';
      if (charin[0] == 0) {
        string[i] = '.';
      } else if (string[i] == 6) {
        string[i] = '|';
      } else {
        string[i] = charin[0];
      }
    }
    // and return the parsed string
    mvprintw(2, 2, "%s", string);
  } else {
    // otherwise throw an error
    mvprintw(2, 2, "fopen fail");
  }
  fclose(fp);
}

mid_file * parsemid(mid_file * m_file) {

  m_file -> nmtrk = 0;
  int pos, i, n = 0;
  int len = strlen(m_file -> string);

  char * buffer = (char * ) malloc(len * sizeof(char) * 2);
  int * buffer2 = (int * ) malloc(len * sizeof(int) * 2);

  char * tmp = m_file -> string;
  char smpte_count[m_file -> nmtrk * 4];

  while (tmp = strstr(tmp, "MTrk")) {
    m_file -> nmtrk++;
    smpte_count[n] = malloc(4);
    pos = strpos(m_file -> string, "MTrk", pos + 1);

    printf("", m_file -> string[pos], m_file -> string[pos + 1], m_file -> string[pos + 2], m_file -> string[pos + 3]);

    buffer[n] = m_file -> string[pos + 4];
    buffer[n + 1] = m_file -> string[pos + 5];
    buffer[n + 2] = m_file -> string[pos + 6];
    buffer[n + 3] = m_file -> string[pos + 7];
    buffer[n + 4] = pos;

    m_file -> mtrk_pos[m_file -> nmtrk] = pos;

    buffer[n + 5] = '\n';
    buffer2[m_file -> nmtrk] = pos;

    tmp++;
    n = n + 6;
  }

  m_file -> mtrk_smpte = buffer;
  tmp = m_file -> string;

  return m_file;

}

FILE * o_file(char * string) {
  FILE * fp;
  if (fp = fopen(string, "rb")) {
    feedback("fopen_success");
  } else {
    feedback("fopen_fail");
  }
  return fp;
}

FILE * r_file(FILE * fp) {

}