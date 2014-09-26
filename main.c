
#include "includes.h"
#include "resource.h"
#include "encrypt.h"
#include "decrypt.h"
   
/* Configurações da janela */
#define TITULO            L"CryptoX v2 - By Dennis Ansi C"
#define CLASS_NAME        L"CryptoXClassEx"
#define LARGURA           698
#define ALTURA            216

/* Configurações dos controles */
#define ID_BTN_ENCRYPT   1337
#define ID_BTN_DECRYPT   1338
#define ID_EDT_INPUT     1339
#define ID_EDT_OUTPUT    1340
#define ID_BTN_CLEAN     9383

HINSTANCE hInstance;
char *string;

LRESULT CALLBACK WindowCallback (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY
wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
   WNDCLASSEX  wndClass;
   MSG         mMsg;
   HWND        JanelaPrincipal;

   wndClass.cbSize          = sizeof(WNDCLASSEX);
   wndClass.style           = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc     = (WNDPROC)WindowCallback;
   wndClass.cbClsExtra      = 0;
   wndClass.cbWndExtra      = 0;
   wndClass.hInstance       = hInstance;
   wndClass.hIcon           = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_APP));
   wndClass.hIconSm         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_APP));
   wndClass.hCursor         = LoadCursor(nil, IDC_ARROW);
   wndClass.hbrBackground   = CreatePatternBrush(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND)));
   wndClass.lpszClassName   = CLASS_NAME;
   wndClass.lpszMenuName    = nil;

   if (!RegisterClassEx(&wndClass)) {
      MessageBox(0, L"Não foi possível registrar classe!", L"ERROR", MB_OK | MB_ICONERROR);
      return 1;
   }

   JanelaPrincipal = CreateWindowEx(0, CLASS_NAME, TITULO, WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
                     (GetSystemMetrics(SM_CXSCREEN) - LARGURA) / 2,(GetSystemMetrics(SM_CYSCREEN) - ALTURA) / 2,
                     LARGURA, ALTURA, HWND_DESKTOP, nil, hInstance, nil);
   
   if (!JanelaPrincipal) {
      MessageBox(0, L"Não foi possível criar janela principal!", L"ERROR", MB_OK | MB_ICONERROR);
      return 1;
   }

   ShowWindow(JanelaPrincipal, SW_SHOW);
   UpdateWindow(JanelaPrincipal);

   while (GetMessage(&mMsg, nil, 0, 0) > 0) {
      TranslateMessage(&mMsg);
      DispatchMessage(&mMsg);
   }

   return (int)mMsg.wParam;
}

LRESULT CALLBACK 
WindowCallback (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   int result, length;

   switch (uMsg) {
      case WM_CREATE :
         CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_MULTILINE,
            100, 95, 580, 20, hWnd, (HMENU)ID_EDT_INPUT, hInstance, nil);
         CreateWindow(L"Edit", nil, WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 123, 580, 20, hWnd, (HMENU)ID_EDT_OUTPUT, hInstance, nil);
         CreateWindow(L"button", L"Encrypt", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 465, 154, 65, 25, hWnd, (HMENU)ID_BTN_ENCRYPT, hInstance, nil);
         CreateWindow(L"button", L"Decrypt", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 540, 154, 65, 25, hWnd, (HMENU)ID_BTN_DECRYPT, hInstance, nil);
         CreateWindow(L"button", L"Clean", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 615, 154, 65, 25, hWnd, (HMENU)ID_BTN_CLEAN, hInstance, nil);
         
         SendMessage(GetDlgItem(hWnd, ID_EDT_INPUT), EM_SETLIMITTEXT, 100000000, 0); 
         SetFocus(GetDlgItem(hWnd, ID_EDT_INPUT));
         break;
      case WM_CLOSE : 
         DestroyWindow(hWnd);
         break;
      case WM_DESTROY :
         PostQuitMessage(WM_QUIT);
         break;
      case WM_COMMAND: 
         switch (LOWORD(wParam)) {
            case ID_BTN_ENCRYPT :
               length = 1024;
               string = (char *)malloc(length);
               memset(string, 0x00, length);
               GetDlgItemTextA(hWnd, ID_EDT_INPUT, string, 399);
               result = encrypt(string);
               if (result != CRYPTOX_ERROR) SetDlgItemTextA(hWnd, ID_EDT_OUTPUT, string);
               else  SetDlgItemTextA(hWnd, ID_EDT_OUTPUT, "Erro ao criptografar string.");
               free(string);
               SetFocus(GetDlgItem(hWnd, ID_EDT_OUTPUT));
               SendMessage(GetDlgItem(hWnd, ID_EDT_OUTPUT), EM_SETSEL, 0, -1);
               break;

            case ID_BTN_DECRYPT :
               length = 400;
               string = (char *)malloc(length);
               memset(string, 0x00, length);
               GetDlgItemTextA(hWnd, ID_EDT_INPUT, string, 399);
               result = decrypt(string);
               if (result != CRYPTOX_ERROR) SetDlgItemTextA(hWnd, ID_EDT_OUTPUT, string);
               else SetDlgItemTextA(hWnd, ID_EDT_OUTPUT, "Erro ao descriptografar string.");
               free(string);
               SetFocus(GetDlgItem(hWnd, ID_EDT_OUTPUT));
               SendMessage(GetDlgItem(hWnd, ID_EDT_OUTPUT), EM_SETSEL, 0, -1);
               break;

            case ID_BTN_CLEAN:
               SetDlgItemTextA(hWnd, ID_EDT_INPUT, "");
               SetDlgItemTextA(hWnd, ID_EDT_OUTPUT, "");
               break;
         }
         break;
   }

   return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
