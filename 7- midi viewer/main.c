#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *stockdata_raw;
char *stockdata_parsed;

int leftmost_d, rightmost_d;

float *stock_inf;

#include "rend_macros.h"
#include "rendering.h"

int get_stockfile(char *fname) {

	FILE *fp;
    fp = fopen(fname, "r");
    fseek(fp, 0, SEEK_END);
    int filelen = ftell(fp);
	
    realloc(stockdata_raw,filelen + 1);
	stockdata_raw = malloc(filelen + 1);
    rewind(fp);
	
	int parse = 0;
	char c;
	int trig = 0;
	int nrows = 1;
	int parse_data_fdate;
	
	while (1) 
    {
      c = fgetc(fp);
      if (feof(fp)) {
       break;
        }
	    if (c == '\n')
	    {
		  trig = 1;
		  nrows++;
	    }
	    if (c == ',')
	    {
		  
	    }
        if (trig == 1) { 
		  stockdata_raw[parse] = c;
		  parse++;
	    }
    }
	
	realloc(stock_inf,7 * 6 * nrows);
	stock_inf = malloc(7 * 6 * nrows);
	
	FILE *fp_2;
    fp_2 = fopen(fname, "r");
    fseek(fp_2, 0, SEEK_END);
    filelen = ftell(fp_2);
	rewind(fp_2);
	
	char floatget[10];
	int inc = 0;
	int sinfpos = 0;
	char *pch;
	float fl_get;
	
	while (1) 
    {
      c = fgetc(fp_2);
      if (feof(fp_2)) {
       break;
      }
	  switch(c)
	  {
       case ',':
	    if (strstr(floatget,"-"))
		{
			floatget[0] = '\0';
			inc = 0;
		}
		else
	    {
		   floatget[0] = '0';
		   fl_get = atof(floatget);
		   if (stock_inf[sinfpos] < 2)
		   {
	        stock_inf[sinfpos] = atof(floatget);
			sinfpos++;
		   }
		   for (int i=0;i!=strlen(floatget);i++)
		   {
		      floatget[i] = '0';
		   }
		   floatget[0] = '\0';
	       inc = 0;
		}
	  break;
	  case '.':
	  case 48:
	  case 49:
	  case 50:
	  case 51:
	  case 52:
	  case 53:
	  case 54:
	  case 55:
	  case 56:
	  case 57:
		floatget[inc] = c;
		inc++;	
	  break;
	  default:
	
	  break;
    }
  }
  for (int i=0;i!=(6 * nrows);i++)
  {
    printf("\n%.7f [%d]",stock_inf[i], i);
  }
  leftmost_d = stock_inf[6];
  rightmost_d = stock_inf[36];
  
}


//blackbox'd.
int init()
{
	int success = 1;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = 0;
	}
	else
	{
		gWindow = SDL_CreateWindow( "stock market sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = 1;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}
	//Create renderer for window
			RENDERING = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( RENDERING == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = 0;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( RENDERING, 0xFF, 0xFF, 0xFF, 0xFF );

			}
	
	return success;
}

void close()
{
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	//last command to call
	SDL_Quit();
}

	char string_l[10], string_r[10];
	char *date_1 = "14/08/21";
	char date_2[10];
	char date_3[10];
	int offset_before, offset_after;
	int rightmost_inc = 36;
	
	int falsegraph[6];
	int going_into_falsegraph = 1;
	

int main( int argc, char* args[] )
{
	if( init() != 1 )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	  // displaying  it as an integer to compile in the c namespace.
		int quit = 0;
        SDL_Event e;
		int strlen_csv;
		
		char *fname = "csv/GBPEUR=X.csv";
		get_stockfile(fname);
		printf("\n%d\n",leftmost_d);
		
	    itoa(leftmost_d,string_l,10);	
		itoa(rightmost_d,string_r,10);
		strcpy(date_2,string_l);
		strcpy(date_3,string_r);
		
		
		
		rendering(date_2, date_3, offset_before);

		while( quit != 1 )
		{
	      while( SDL_PollEvent( &e ) != 0 )
			{
			  /* make a switch for the economy. */
				switch (e.type) 
				  {
			  /* sdl_quit is the quit macro defined as 0x100. */
				  case(0x100):
				  quit = 1;
				  break;
				  case SDL_KEYDOWN:
				  printf( "Key press detected\n" );
				  
				  if (stock_inf[rightmost_inc+36] != 0)
				  {
					offset_before = offset_before + 6;
					leftmost_d = rightmost_d;
					rightmost_inc = rightmost_inc + 36;
					rightmost_d = stock_inf[rightmost_inc];
					itoa(leftmost_d,string_l,10);	
					itoa(rightmost_d,string_r,10);
					strcpy(date_2,string_l);
					strcpy(date_3,string_r);
					rendering(date_2, date_3, offset_before);
				  }
				  else
				  {
					  if (going_into_falsegraph != 0)
					  {
						offset_before = 12;
						leftmost_d = stock_inf[6];
						rightmost_d = stock_inf[36];	
						rightmost_inc = 36;
						itoa(leftmost_d,string_l,10);	
						itoa(rightmost_d,string_r,10);
						strcpy(date_2,string_l);
						strcpy(date_3,string_r);
						rendering(date_2, date_3, offset_before);  
						  
						/* falsegraph[1] = stock_inf[(rightmost_inc-37)];
						falsegraph[2] = stock_inf[(rightmost_inc-37)+6];
						falsegraph[3] = stock_inf[(rightmost_inc-37)+12];
						falsegraph[4] = stock_inf[(rightmost_inc-37)+18];
						falsegraph[5] = stock_inf[(rightmost_inc-37)+24];
						falsegraph[6] = stock_inf[(rightmost_inc-37)+30];
						going_into_falsegraph = 0;
						*/ 
					  }
				  }
				  break;
				  }
				}
				SDL_RenderPresent( RENDERING );
			}
	    }
	//Free resources and close SDL
	close();

	return 0;
}
