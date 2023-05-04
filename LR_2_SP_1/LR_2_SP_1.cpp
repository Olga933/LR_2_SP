// LR_2_SP_1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "LR_2_SP_1.h"

#define MAX_LOADSTRING 100

#define IDI_Button1    1001
#define IDI_Button2    1002
#define IDI_Edit1      1003
#define IDI_Static1    1004
#define IDI_Static2    1005
#define IDI_hStaticLD  1006
#define IDI_hStaticLUP 1007
#define IDI_hStaticDC  1008
#define IDI_hStaticN   1009

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HWND hBut1;
HWND hBut2;
HWND hEdit1;
HWND hStatic1;
HWND hStatic2;
HWND hStaticLD;
HWND hStaticLDv;
HWND hStaticLUP;
HWND hStaticLUPv;
HWND hStaticDC;
HWND hStaticDCv;
HWND hStaticN;
HWND hStaticNv;

int LD = 0, LUP = 0, DC = 0, N = 0;

int left;
int top;
int width;
int heigth;
bool fl = false;
int x_get;
int y_get;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LR2SP1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR2SP1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR2SP1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR2SP1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   hBut1 = CreateWindow(TEXT("BUTTON"), TEXT("Кнопка 1"), WS_VISIBLE | WS_CHILD,
       50, 50, 100, 40, hWnd, (HMENU)IDI_Button1, hInstance, nullptr);

   hBut2 = CreateWindow(TEXT("BUTTON"), TEXT("Кнопка 2"), WS_VISIBLE | WS_CHILD,
       210, 50, 100, 40, hWnd, (HMENU)IDI_Button2, hInstance, nullptr);

   hEdit1 = CreateWindow(TEXT("EDIT"), TEXT("Ввод"), WS_VISIBLE | WS_CHILD,
       50, 110, 100, 40, hWnd, (HMENU)IDI_Edit1, hInstance, nullptr);

   hStatic1 = CreateWindow(TEXT("STATIC"), TEXT("Вывод"), WS_VISIBLE | WS_CHILD,
       210, 110, 100, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStatic2 = CreateWindow(TEXT("STATIC"), TEXT("Координаты курсора"), WS_VISIBLE | WS_CHILD,
       50, 180, 100, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStaticLD = CreateWindow(TEXT("STATIC"), TEXT("WM_LBUTTONDOWN"), WS_VISIBLE | WS_CHILD,
       370, 50, 190, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStaticLUP = CreateWindow(TEXT("STATIC"), TEXT("WM_LBUTTONUP"), WS_VISIBLE | WS_CHILD,
       370, 110, 190, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStaticDC = CreateWindow(TEXT("STATIC"), TEXT("WM_LBUTTONDBLCLK"), WS_VISIBLE | WS_CHILD,
       370, 170, 190, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStaticN = CreateWindow(TEXT("STATIC"), TEXT("WM_NCHITTEST"), WS_VISIBLE | WS_CHILD,
       370, 230, 190, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStaticLDv = CreateWindow(TEXT("STATIC"), TEXT(" "), WS_VISIBLE | WS_CHILD,
       590, 50, 100, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStaticLUPv = CreateWindow(TEXT("STATIC"), TEXT(" "), WS_VISIBLE | WS_CHILD,
       590, 110, 100, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStaticDCv = CreateWindow(TEXT("STATIC"), TEXT(" "), WS_VISIBLE | WS_CHILD,
       590, 170, 100, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   hStaticNv = CreateWindow(TEXT("STATIC"), TEXT(" "), WS_VISIBLE | WS_CHILD,
       590, 230, 100, 40, hWnd, (HMENU)IDI_Static1, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case IDI_Button1:
            {
                int x;
                TCHAR str[50];
                GetWindowText(hEdit1, str, 50);
                x = _wtoi(str);
                x = x * x;
                _itot_s(x, str, 10);
                SetWindowText(hStatic1, str);
            }
            break;

            case IDI_Button2:
            {
                //Нажать на кнопку 1 - первый метод
                SendMessage(hBut1, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(5, 5));
                SendMessage(hBut1, WM_LBUTTONUP, 0, MAKELONG(5, 5));
                //Второй метод
                /*SendMessage(hBut1, BM_CLICK, 0, 0);*/
            }
            break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_RBUTTONDOWN:
    {
        TCHAR X[50], Y[50];
        WORD x = LOWORD(lParam), y = HIWORD(lParam);
        _itot_s(x, X, 10);
        _itot_s(y, Y, 10);
        _tcscat_s(X, L"; ");
        _tcscat_s(X, Y);
        SetWindowText(hStatic2, X);
    }
    break;

    case WM_LBUTTONDBLCLK:
    {
        TCHAR X[50];
        DC++;
        _itot_s(DC, X, 10);
        SetWindowText(hStaticDCv, X);
    }
    break;

    case WM_LBUTTONDOWN:
    {
        TCHAR X[50];
        LD++;
        _itot_s(LD, X, 10);
        SetWindowText(hStaticLDv, X);
        fl = true;
        RECT client_rect;
        x_get = LOWORD(lParam);
        y_get = HIWORD(lParam);
        GetWindowRect(hWnd, &client_rect);
        left = client_rect.left;
        top = client_rect.top;
        width = client_rect.right - client_rect.left;
        heigth = client_rect.bottom - client_rect.top;

    }
    break;

    case WM_LBUTTONUP:
    {
        TCHAR X[50];
        LUP++;
        _itot_s(LUP, X, 10);
        SetWindowText(hStaticLUPv, X);
        fl = false;
    }
    break;

    case WM_NCHITTEST:
    {
        TCHAR X[50];
        N++;
        _itot_s(N, X, 10);
        SetWindowText(hStaticNv, X);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (fl)
        {
            WORD x = LOWORD(lParam), y = HIWORD(lParam);
            left += x - x_get;
            top += y - y_get;
            MoveWindow(hWnd, left, top, width, heigth, false);
            x_get = x;
            y_get = y;
        }
    }
    break;

    case WM_NCLBUTTONDOWN: // Не перемещать за заголовок
        if (wParam != HTCAPTION)
            return DefWindowProc(hWnd, message, wParam, lParam);
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_CLOSE:
    {}
    case WM_DESTROY:
        if (MessageBox(hWnd, L"Закрыть?", L"Сообщение", MB_OKCANCEL) == IDOK)
        {
            PostQuitMessage(0);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
