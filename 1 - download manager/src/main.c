#include <windows.h>
#include <wininet.h>
#include <curl/curl.h>
#include <stdlib.h>	
#include <string.h> 

int ch = 1;
char o[200];
int len, i, index, cont;
char *add[3];
char command[500];
int parse_dir;
char *inc_dir[2];
FILE * pFile;

const char g_szClassName[] = "myWindowClass";

#define ID_FILE_EXIT 9001
#define ID_STUFF_GO 9002
#define ID_TEXT 9003
#define ID_PROG 9004
#define ID_FILE_URL 9005
#define ID_FILE_FTP 9006
#define ID_BOX 9007
#define ID_BUTONE 9008
#define ID_BUTSEND 9011
#define ID_DIR 9012
#define ID_FNAME 9013
#define ID_DIRONE 9014
#define ID_DIRTWO 9015

struct FtpFile {
  char *filename;
  FILE *stream;
};

struct FtpFile ftpfile = {
			"on.jpg", /* name to store the file as if successful */
			NULL
			};

  CURL *curl;
  CURLcode res;

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct FtpFile *out = (struct FtpFile *)stream;
  if(!out->stream) {
    out->stream = fopen(out->filename, "wb");
    if(!out->stream)
      return -1;
  }
  return fwrite(buffer, size, nmemb, out->stream);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	HWND progBox, hListBox, buttons[10], editBox, dirBox[2], textBoxes[10];
	HMENU hMenu, hSubMenu[4], hSearchMenu;
    HICON hIcon, hIconSm;
	HWND hList;
	
	int count = SendMessage(hList, LB_GETSELCOUNT, 2, 3);
	int *buf;
	int index;
	
	static HBITMAP hBitmap;
    HDC hdc;
    PAINTSTRUCT ps;
    BITMAP bitmap;
    HDC hdcMem;
    HGDIOBJ oldBitmap;
	
    switch(msg)
    {
		case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC) wParam;
        SetTextColor(hdcStatic, RGB(0,0,0));
        SetBkColor(hdcStatic, RGB(0,0,0));
        return (INT_PTR)progBox;
    }
	break;
		
		case WM_CREATE:
    {
		hBitmap = (HBITMAP) LoadImageW(NULL, L"solve.bmp", 
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (hBitmap == NULL) {
    }
       
		hListBox = CreateWindowExW(WS_EX_CLIENTEDGE
        , L"LISTBOX", NULL
        , WS_CHILD | WS_VISIBLE | SBS_VERT | ES_AUTOVSCROLL
        , 0, 40, 300, 170
        , hwnd, (HMENU)ID_TEXT, GetModuleHandle(NULL), NULL);
		
		progBox = CreateWindowExW(WS_EX_CLIENTEDGE
        , L"static",L""
        , WS_CHILD | WS_VISIBLE
        , 0, 205, 300, 80
        , hwnd, (HMENU)ID_PROG, GetModuleHandle(NULL), NULL);
		
		buttons[3] = CreateWindowExW(WS_EX_CLIENTEDGE
        , L"BUTTON", L"Download"
        , WS_CHILD | WS_VISIBLE 
        , 220, 0, 80,20
        , hwnd, (HMENU)ID_BUTSEND, GetModuleHandle(NULL), NULL);
		
		editBox = CreateWindowExW(WS_EX_CLIENTEDGE
        , L"EDIT", NULL
        , BS_BITMAP | WS_CHILD | WS_VISIBLE 
        , 0, 0, 220,20
        , hwnd, (HMENU)ID_BOX, GetModuleHandle(NULL), NULL);
		
		textBoxes[2] = CreateWindowExW(NULL
        , L"static", L"fname"
        , WS_CHILD | WS_VISIBLE | SBS_VERT | ES_AUTOVSCROLL
        , 2, 21, 38, 18
        , hwnd, (HMENU)ID_DIRTWO, GetModuleHandle(NULL), NULL);
		
		dirBox[2] = CreateWindowExW(WS_EX_CLIENTEDGE
        , L"EDIT", NULL
        , BS_BITMAP | WS_CHILD | WS_VISIBLE 
        , 45, 20, 255, 20
        , hwnd, (HMENU)ID_FNAME, GetModuleHandle(NULL), NULL);
		
		hMenu = CreateMenu();
		
		hSearchMenu = CreateMenu();
		
        hSubMenu[1] = CreatePopupMenu();
		hSubMenu[2] = CreatePopupMenu();
		hSubMenu[3] = CreatePopupMenu();
		hSubMenu[4] = CreatePopupMenu();

        SetMenu(hwnd, hMenu);
		
		hIcon = LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
        if(hIcon)
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        else
            MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);

        hIconSm = LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
        if(hIconSm)
            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
        else
            MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);
		
		SetDlgItemText(hwnd, ID_PROG, "Welcome to the Download Manager.");
		
    }
    break;
	
		case WM_COMMAND:
		switch(LOWORD(wParam)) {
			case ID_FILE_EXIT: 
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
			case ID_BUTONE:
				
			break;
			case ID_BUTSEND:
			
			free(ftpfile.filename);
			
			// Pass URL to Curl from a control function with ID "ID_BOX" //
			len = GetWindowTextLength(GetDlgItem(hwnd, ID_BOX));
			add[1] = (char*)GlobalAlloc(GPTR,len + 1);
			GetDlgItemText(hwnd, ID_BOX, add[1], len + 1);
			
			// Pass file output directory to Curl from a control function with ID "ID_FNAME" //
			len = GetWindowTextLength(GetDlgItem(hwnd, ID_FNAME)) + GetWindowTextLength(GetDlgItem(hwnd, ID_DIR));
			add[2] = (char*)GlobalAlloc(GPTR,len + 1);
			GetDlgItemText(hwnd, ID_FNAME, add[2], len + 1);
			
			// Current status //
			SetDlgItemText(hwnd, ID_PROG, "Downloading...");
			
			// Call the "ftpget.exe" curl executable and pass command line arguments to the program to retrieve a file add[2] from a webserver add[1] //
			sprintf(command, "ftpget.exe %s %s", add[1], add[2]);
			WinExec(command, SW_HIDE);
			// //
			SetDlgItemText(hwnd, ID_PROG, add[2]);
			// Check for the temp file indicating whether or not the program succeeded //
			pFile = fopen ("DM_tempx001","r");
			cont = fgetc(pFile);
			if (cont != 't')
			{
			SetDlgItemText(hwnd, ID_PROG, "File failed to download.");
			remove("DM_tempx001");
			}
			else 
			{
			SetDlgItemText(hwnd, ID_PROG, "File downloaded successfully");
			index = SendDlgItemMessage(hwnd, ID_TEXT, LB_ADDSTRING, 0, (LPARAM)add[1]);
			remove("DM_tempx001");
			}
			break;
		}

		case WM_PAINT:
        
             hdc = BeginPaint(hwnd, &ps);

             hdcMem = CreateCompatibleDC(hdc);
             oldBitmap = SelectObject(hdcMem, hBitmap);

             GetObject(hBitmap, sizeof(bitmap), &bitmap);
             BitBlt(hdc, 5, 5, bitmap.bmWidth, bitmap.bmHeight, 
                 hdcMem, 0, 0, SRCCOPY);

             SelectObject(hdcMem, oldBitmap);
             
			 
			 SendMessage(buttons[2], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

			 DeleteDC(hdcMem);
             EndPaint(hwnd, &ps);

             break;
		break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
	
	CURL *curl;
	CURLcode res;
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 1;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
	
	 CreateWindow(wc.lpszClassName, "Download Manager",
                WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
                100, 100, 306, 310, NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}