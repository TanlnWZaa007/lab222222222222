#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
HWND hEdit1, hEdit2;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASS wc = {0};

    wc.hbrBackground = CreateSolidBrush(RGB(200, 10, 100));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "MyCalcClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) return -1;

   
    HWND hWnd = CreateWindow("MyCalcClass", "My Calculator",
                             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                             CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
                             NULL, NULL, hInst, NULL);

    ShowWindow(hWnd, ncmdshow);
    UpdateWindow(hWnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Please input two numbers",
                         WS_VISIBLE | WS_CHILD | SS_CENTER,
                         25, 20, 185, 20,
                         hWnd, NULL, NULL, NULL);

            hEdit1 = CreateWindow("EDIT", "",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                                  45, 50, 145, 20,
                                  hWnd, NULL, NULL, NULL);

            hEdit2 = CreateWindow("EDIT", "",
                                  WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                                  45, 80, 145, 20,
                                  hWnd, NULL, NULL, NULL);

            CreateWindow("BUTTON", "+",
                         WS_VISIBLE | WS_CHILD,
                         45, 110, 30, 25,
                         hWnd, (HMENU)1, NULL, NULL);
                         
            CreateWindow("BUTTON", "-",
                         WS_VISIBLE | WS_CHILD,
                         85, 110, 30, 25,
                         hWnd, (HMENU)2, NULL, NULL);
                         
            CreateWindow("BUTTON", "*",
                         WS_VISIBLE | WS_CHILD,
                         125, 110, 30, 25,
                         hWnd, (HMENU)3, NULL, NULL);
                         
            CreateWindow("BUTTON", "/",
                         WS_VISIBLE | WS_CHILD,
                         165, 110, 30, 25,
                         hWnd, (HMENU)4, NULL, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wp) >= 1 && LOWORD(wp) <= 4) {
                char buf1[100], buf2[100], out[100];
               
                GetWindowText(hEdit1, buf1, 100);
                GetWindowText(hEdit2, buf2, 100);

                double num1 = atof(buf1);
                double num2 = atof(buf2);
                double result = 0;

                switch (LOWORD(wp)) {
                    case 1: result = num1 + num2; break; // บวก
                    case 2: result = num1 - num2; break; // ลบ
                    case 3: result = num1 * num2; break; // คูณ
                    case 4:                              // หาร
                        if (num2 == 0) {
                            MessageBox(hWnd, "Cannot divide by zero", "Error", MB_OK | MB_ICONERROR);
                            return 0;
                        }
                        result = num1 / num2;
                        break;
                }

                sprintf(out, "%f", result);
               
                MessageBox(hWnd, out, "Result", MB_OK);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}
