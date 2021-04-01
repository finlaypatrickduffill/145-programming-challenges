#define MIDI_TRACK "MTrk" /* header for MIDI file.*/
#define MIDI_HEADER "MThd"

#define NOTE_EFFECT  0x90
#define NOTE_ON      4
#define NOTE_OFF     5

#define MIDDLE_C_HEX 0x60

// #define COLOR_PAIR(n)		(((chtype)(n) << PDC_COLOR_SHIFT) & A_COLOR)
/* TITLE */
/* title of program */      	#define TITLE "LMidi"
/* title of subwin_1 */     	#define SWIN_1 "Enter name of file"
/* title of menu option 1*/ 	#define MENUOPTION1  " VIEW"
/* title of menu option 2*/ 	#define MENUOPTION2  " EDIT"
/* title of menu option 3*/ 	#define MENUOPTION3  " EXIT"
/* title of state_2 */ 			#define STATE_2TITLE "Enter filename. ESC key returns"
/* not in directory error */	#define ERR_NOTINDIR "file opening unsuccessful:-> not found in this directory? [%s]"

#define MENU_STATE 1
#define DIVIDSCREENHEIGHT (LINES-height)/2
#define DIVIDSCREENWIDTH (COLS-width)/2
#define maxcursor 3