#include <windows.h>
#include <stdio.h>
#include "extern.h"

#define ID_EDITCHILD 100

const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HMENU hMenu, hSubMenu[4], hSearchMenu;
	HBITMAP hBitmap;
	HICON hIcon, hIconSm;
	static HWND hwndEdit;
	
    switch(msg)
    {
		case WM_CREATE:
		hMenu = CreateMenu();
		hSubMenu[1] = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu[1], "&File");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu[2], "&Edit");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu[3], "&Macros");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu[4], "&Help");
		hwndEdit = CreateWindowEx(
        0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
		ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, 0, 0, hwnd,
		(HMENU) ID_EDITCHILD, (HINSTANCE) GetWindowLongPtr(hwnd,
		GWLP_HINSTANCE),NULL);  
		SetMenu(hwnd, hMenu);

        hIconSm = LoadImage(NULL, "bmp.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
        if(hIconSm)
            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
        else
            MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);
		
		break;
		case WM_SIZE: 
			//resize an edit control to the size of a parent window upon resizing "hwnd".
            MoveWindow(hwndEdit, 
                       0, 0,                
                       LOWORD(lParam),      
                       HIWORD(lParam),       
                       TRUE);               
        return 0; 
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
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Linkpad",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);

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