
/* legend
	
	define draw_method as the corresponding macro based on the platform to build
	DRAW_NCONS: building to console with native libraries.
	DRAW_NCURS: building to console with ncurses libraries + native.
	DRAW_GRAPH: building to sdl (in progress).

*/

FILE *fp_global;


#define DRAW_NCONS 1
#define DRAW_NCURS 2
#define DRAW_GRAPH 3

#define NOTE_EFFECT  0x90
#define NOTE_ON      4
#define NOTE_OFF     5

#define MIDDLE_C_HEX 0x60

int draw_method = DRAW_NCONS;

typedef struct midi_instruct{
  int noteon_messages; /* total number of note on messages in the file */
  int noteoff_messages; /* total number of note off messages in the file */
  int keypressure_messages; /* total number of notekeypressure messages in the file... */
  int controllerchange_messages; /* etc. */
  int programchange_messages;
  int channelchange_messages;
  int channelpressure_messages;
  int pitchbend_messages;
  
  // status bytes in 0xFx are individiually labelled.
  int sysexclusive_messages;
  int songposition_messages;
  int songselect_messages;
  int busselect_messages;
  int tunerequest_messages;
  int eos_messages;
  int timingtick_messages;
  int startsong_messages;
  int continuesong_messages;
  int stopsong_messages;
  int activesensing_messages;
  int sysreset_messages;
  
  char *message_inst[5]; /* messages can be up to 5 bytes long */
  
  char exitkey;
}mid_inf;


char *midi_trackdata;
char fname[5000];
int c, parse;

char putmid(FILE * fp, mid_inf * midi_info) {
  
  midi_info->noteon_messages = 0;
  midi_info->noteoff_messages = 0;
  midi_info->keypressure_messages = 0;
  
  //get name of file
  // no messages yet
  
  gets(fname);
  fp = fopen(fname, "r");
  fseek(fp, 0, SEEK_END);
  int filelen = ftell(fp);
  realloc(midi_trackdata,filelen + 1);
  midi_trackdata = malloc(filelen + 1);
  rewind(fp);
  
  while (1) 
  {
    c = fgetc(fp);
    if (feof(fp)) {
      break;
      }
      if (c != 7) {  
		switch (c) {
          case 0x00:
            midi_trackdata[parse] = 'S';
          break;
		  case 62:
            midi_trackdata[parse] = 'S';
          break;
		  case 182:
            midi_trackdata[parse] = 'S';
          break;
		  case 90:
		  case 0x90:
		  case 0x91:
	  	  case 0x92:
		  case 0x93:
		  case 0x94:
		  case 0x95:
		  case 0x96:
		  case 0x97:
		  case 0x98:
		  case 0x99:
		  case 0x9A:
		  case 0x9B:
		  case 0x9C:
		  case 0x9D:
		  case 0x9E:
		  case 0x9F:
		    midi_info->noteon_messages++;
            midi_trackdata[parse] = '9';
          break;
		  case 0x80:
		  case 0x81:
		  case 0x82:
		  case 0x83:
		  case 0x84:
		  case 0x85:
		  case 0x86:
		  case 0x87:
		  case 0x88:
		  case 0x89:
		  case 0x8A:
		  case 0x8B:
		  case 0x8C:
		  case 0x8D:
		  case 0x8E:
		  case 0x8F:
		    midi_info->noteoff_messages++;
            midi_trackdata[parse] = '8';
          break;
		  case 0xA0:
		  case 0xA1:
		  case 0xA2:
		  case 0xA3:
		  case 0xA4:
		  case 0xA5:
		  case 0xA6:
		  case 0xA7:
		  case 0xA8:
		  case 0xA9:
		  case 0xAA:
		  case 0xAB:
		  case 0xAC:
		  case 0xAD:
		  case 0xAE:
		  case 0xAF:
		    midi_info->keypressure_messages++;
            midi_trackdata[parse] = 'A';
          break;
		  default:
            midi_trackdata[parse] = c;
          break;
		}
      }
	  else {
        midi_trackdata[parse] = '_';
      }
	  parse++;
  }

  close(fp);
	
}

int strpos(char *hay, char *needle, int offset)
{
   char haystack[strlen(hay)];
   strncpy(haystack, hay+offset, strlen(hay)-offset);
   char *p = strstr(haystack, needle);
   if (p)
      return p - haystack+offset;
   return -1;
}

typedef struct mid_file{
	//
	int nmtrk;
	// raw data of midi file
	char *string;
	// mtrk data
	char *mtrk_n;
	char *mtrk_smpte;
	int *mtrk_dat;
	int mtrk_pos[100];
	// byte reading positions after smpte for every track chunk
	char *mtrk_brpos;
	// char at end of struct for return value(?)
	char nterm;
	
}mid_file;

void feedback(char *string) {
	
	if (draw_method == DRAW_NCONS)
	{
		if (string == "fopen_success")
		{
			printf("file opened succesfully");
		}
		if (string == "fopen_fail")
		{
			printf("file couldn't be opened: erroneous filename.");
		}
	}
}

char *read_file(char *string)
{
  FILE *fp;
  char filename[20];
  gets(filename);
  fp = fopen(filename, "rb");  
  
  fseek(fp, 0, SEEK_END);
  int filelen = ftell(fp);
  rewind(fp);
  
  char charin[1];
	
  string = (char *)malloc(filelen * sizeof(char) * 2);
  
	//check if file was opened successfully
  if (fp) 
  {
	// if successful, parse the file data
	for (int i=1;i!=filelen+1;i++)
	{
		charin[0] = fgetc(fp);
		charin[1] = ' ';
		if (charin[0] == 0)
		{
			string[i] = '.';
		}
		else if (string[i] == 6)
		{
			string[i] = '|';
		}
		else 
		{
			string[i] = charin[0];
		}
	}
	// and return the parsed string
	return string;
  }
  else 
  {
	// otherwise throw an error
    feedback("fopen_fail");
  }
  fclose(fp);
}

mid_file *parsemid(mid_file *m_file) {
	
	m_file->nmtrk = 0;
	int pos,i,n = 0;
	int len = strlen(m_file->string);
	
	char *buffer = (char *)malloc(len * sizeof(char) * 2);
	int *buffer2 = (int *)malloc(len * sizeof(int) * 2);
	
	char *tmp = m_file->string;
	char smpte_count[m_file->nmtrk*4];
	
	while(tmp = strstr(tmp, "MTrk"))
	{	
		m_file->nmtrk++;
		smpte_count[n] = malloc(4);
		pos = strpos(m_file->string,"MTrk",pos+1);
			
		printf("",m_file->string[pos],m_file->string[pos+1],m_file->string[pos+2],m_file->string[pos+3]);
		
		buffer[n] = m_file->string[pos+4];
		buffer[n+1] = m_file->string[pos+5];
		buffer[n+2] = m_file->string[pos+6];
		buffer[n+3] = m_file->string[pos+7];
		buffer[n+4] = pos;
		
		m_file->mtrk_pos[m_file->nmtrk] = pos;
		
		buffer[n+5] = '\n';
		buffer2[m_file->nmtrk] = pos;
		
		tmp++;
		n = n + 6;
	}
	
	m_file->mtrk_smpte = buffer;
	tmp = m_file->string;
	
	return m_file;
	
}

FILE *o_file(char *string) {
	FILE *fp;
	if (fp = fopen(string,"rb"))
	{
		feedback("fopen_success");
	}
	else
	{
		feedback("fopen_fail");
	}
	return fp;
}

FILE *r_file(FILE *fp) {
	
}