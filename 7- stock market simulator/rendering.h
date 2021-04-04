void rend_asc(int starty, int startx,int width, int height, char *asc) {
	
	int width_inc, height_inc = 0;
	for (int x = 0; x!= (strlen(asc)); x++)
	{
		switch (asc[x])
		{
		  case '*':
		    SDL_SetRenderDrawColor( RENDERING, 0xFF, 0xFF, 0xFF, 0xFF );
		    SDL_RenderDrawPoint( RENDERING, /* y */ width_inc+starty,/* x */  height_inc+startx);
		  break;
		  case '.':
		  break;
		}
		width_inc++;
		if (width_inc == width)
		{
			height_inc++;
			width_inc = 0;
		}
	}
}

// draw a number from a bitewise macro (doesn't work yet) //
void rend_number (int starty, int startx, int number) {
	
	switch (number)
	{
		case 0:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,ZERO_MACRO);
		break;
		case 1:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,ONE_MACRO);
		break;
		case 2:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,TWO_MACRO);
		break;
		case 3:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,THREE_MACRO);
		break;
		case 4:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,FOUR_MACRO);
		break;
		case 5:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,FIVE_MACRO);
		break;
		case 6:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,SIX_MACRO);
		break;
		case 7:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,SEVEN_MACRO);
		break;
		case 8:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,EIGHT_MACRO);
		break;
		case 9:
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,NINE_MACRO);
		break;
		default:
		break;
	}
	SDL_RenderPresent( RENDERING );
}

void render_chart(char *date_1, char *date_3) {
	SDL_SetRenderDrawColor( RENDERING, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( RENDERING );

	SDL_Rect outlineRect = { 2, 12, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 24 };
	SDL_SetRenderDrawColor( RENDERING, 0xFF, 0xFF, 0xFF, 0xFF );		
	SDL_RenderDrawRect( RENDERING, &outlineRect );
	
	rend_asc((SCREEN_WIDTH/2)-(32/2), 2, 32, 8, stockstring);
	
	int starty = 0;

    for (int yu = 0; yu != strlen(date_1); yu++)
	{
	
	starty = starty + (WIDTH_NUMBER+1);
	int startx = SCREEN_HEIGHT - 10;
	char number = date_1[yu];
	
    switch (number)
	{
		case '0':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,ZERO_MACRO);
		break;
		case '1':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,ONE_MACRO);
		break;
		case '2':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,TWO_MACRO);
		break;
		case '3':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,THREE_MACRO);
		break;
		case '4':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,FOUR_MACRO);
		break;
		case '5':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,FIVE_MACRO);
		break;
		case '6':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,SIX_MACRO);
		break;
		case '7':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,SEVEN_MACRO);
		break;
		case '8':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,EIGHT_MACRO);
		break;
		case '9':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,NINE_MACRO);
		break;
		case '/':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,SLASH_MACRO);
		break;
		default:
		break;
	  }
	}
	
	starty = SCREEN_WIDTH-((strlen(date_3)*WIDTH_NUMBER)+(strlen(date_3)*WIDTH_NUMBER)/2);
	
    for (int yu = 0; yu != strlen(date_3); yu++)
	{
	
	starty = starty + (WIDTH_NUMBER+1);
	int startx = SCREEN_HEIGHT - 10;
	char number = date_3[yu];
	
    switch (number)
	{
		case '0':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,ZERO_MACRO);
		break;
		case '1':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,ONE_MACRO);
		break;
		case '2':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,TWO_MACRO);
		break;
		case '3':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,THREE_MACRO);
		break;
		case '4':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,FOUR_MACRO);
		break;
		case '5':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,FIVE_MACRO);
		break;
		case '6':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,SIX_MACRO);
		break;
		case '7':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,SEVEN_MACRO);
		break;
		case '8':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,EIGHT_MACRO);
		break;
		case '9':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,NINE_MACRO);
		break;
		case '/':
		  rend_asc(starty,startx,WIDTH_NUMBER,HEIGHT_NUMBER,SLASH_MACRO);
		break;
		default:
		break;
	  }
	}
	//Update screen
	SDL_RenderPresent( RENDERING );
}

int y_atoi1, y_atoi2;
int screen_points = 14;

void render_graph(int offset_before) {
	
	for (int i = 1; i != 7; i++)
	{
		y_atoi1 = ((stock_inf[(offset_before+(i*6))+1])*1000);
		y_atoi2 = ((stock_inf[(offset_before+(i*6))+7])*1000);
		
		
		SDL_RenderDrawLine(RENDERING, ((SCREEN_WIDTH-4)/6)*(i-1)+2 , y_atoi1, (((SCREEN_WIDTH-4)/6)*i)+2, y_atoi2 );
	}
	
}

void rendering(char *date_1, char *date_3, int offset_before) {
	
	render_chart( date_1, date_3);
	render_graph(offset_before);
	SDL_RenderPresent( RENDERING );
	
}