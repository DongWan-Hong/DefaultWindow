// DefaultWindow.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "HongWindow.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);   // 창의 외형적인 스타일을 지정하는 옵션 함수
BOOL                InitInstance(HINSTANCE, int);           // 창 초기화 함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);    // 윈도우 메시지 처리기 함수
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 현재 프로그램의 고유 식별 번호
                     _In_opt_ HINSTANCE hPrevInstance,  // 전에 실행되었던 인스턴스의 핸들(없을 경우 NULL)
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)           // 창의 스타일(모양 / 최소화 또는 최대한 모양)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            // 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 하는 함수
            TranslateMessage(&msg);

            // 시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리기에게 전달하는 함수
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // WNDCLASSEXW : 창의 여러 특성을 정의하기 위한 구조체
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    // 자기 자신의 사이즈를 저장

    // 초기화 되는 값은 윈도우 창의 수직, 수평의 크기가 변할 경우 다시 그리겠다는 의미
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    // CS_HREDRAW : 가로를 다시 그림
    // CS_VREDRAW : 세로를 다시 그림

    // 저장해둔 함수가 호출되어 메세지를 처리
    wcex.lpfnWndProc    = WndProc;

    // 윈도우가 특수한 목적으로 사용하는 여분의 공간(일종의 예약 영역, 사용하지 않을 경우 0)
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;

    // 이 윈도우를 사용하는 프로그램의 번호를 설정
    wcex.hInstance      = hInstance;

    // 윈도우가 사용할 아이콘 지정
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));

    // 마우스 커서 지정
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    
    // 배경 색을 설정
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNSHADOW +1);

    // 창의 메뉴바
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_DEFAULTWINDOW);
   
    // 실행 파일의 이름(프로젝트 이름과 일치시켜 작성)
    wcex.lpszClassName  = szWindowClass;

    // 윈도우 상단에 있는 아이콘 모양
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // CreateWindowW : 등록해 놓은 정보들을 토대로 윈도우를 생성

   HWND hWnd = CreateWindowW(szWindowClass,         // 정의한 윈도우 클래스의 전달할 클래스 이름
                             szTitle,               // 창 타이틀 문자열
                             WS_OVERLAPPEDWINDOW,   // 만들고자 하는 윈도우의 형태(스타일)지정, 기본 값으로 흔히 접하는 모양
                             CW_USEDEFAULT, 0,      // 창을 생성하는 X,Y 좌표
                             800, 600,              // 생성할 창의 가로, 세로 사이즈
                             nullptr,               // 부모 윈도우의 핸들을 지정, 없으면 null
                             nullptr,               // 윈도우에서 사용할 메뉴의 핸들
                             hInstance,             // 윈도우를 만드는 주체, 프로그램의 핸들 지정
                             nullptr);              // 운영체제가 특수한 목적으로 사용

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// 함수 호출 규약  : 함수의 실행이 종료되면 할당되었던 스택 메모리를 반환해야하는데 함수를 호출한 호출원(caller)에서 정리할 것인가
// 아니면 호출 받은 피호출자(callee)에서 할 것인가에 대한 약속 또는 규약

// __cdecl : c / c++ 기본 호출 규약, 호출원이 stack을 정리, 대표적인 예로 printf 함수를 생각하면 된다(가변인자 함수)
// __stdcall : win api 기본 호출 규약, 피호출자가 stack을 정리 (고정인자 함수)
// __fastcall : 함수 호출을 빠르게 처리하기 위한 호출 규약
// __thiscall : this 포인터를 매개 변수로 전달 받았을 경우 사용되는 규약


// 라이브러리 : 바이너리로 번역(컴파일)된 함수들을 모아놓은 파일

// - 코드 재사용을 위한 초창기 방법 중 하나이며 다른 프로그램에서 사용할 수 있도록 운영체제나 소프트웨어 개발자에 의해 제공
// - 라이브러리의 대다수 함수들은 함수의 정의 및 선언을 필요로하기 때문에 링크되기 전 전처리기에 의해 해당 헤더파일을 원시 프로그램에 포함
// - 라이브러리들은 사용자의 프로그램과 링크되어 실행이 가능한 완전한 프로그램을 이루게 됨

// 윈도우 구성 라이브러리

// 1. KERNEL : 메모리를 관리하고 프로그램을 실행
// 2. USER : 유저 인터페이스와 윈도우(창)을 관리
// 3. GDI : 화면 처리와 그래픽을 담당

// 레프트 탑 라이트 바텀
RECT  el{ 20,50,70,100 }; // 원, 몸체
RECT  rc{ 50,50,100,100 }; // 사각형,포대

RECT _Score{ 290, 490, 490, 515 }; // 점수
RECT _Exp{ 240, 520, 540, 550 }; // 경험치바

RECT  _MiniMap{ 400,730,1100,780 }; // 미니맵




list<RECT>  Bullet_1_List;
list<RECT>  Bullet_2_List;
list<RECT>  Bullet_3_List;
list<RECT>  Bullet_4_List;
list<RECT>  Bullet_5_List;
list<RECT>  Bullet_6_List;
list<RECT>  Bullet_7_List;
list<RECT>  Bullet_8_List;
list<RECT>  Bullet_9_List;

bool bUp = true; 
bool bDown = true;
bool bRight = true;
bool bLeft = true;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:

        SetTimer(hWnd, 0, 0, 0);

        // 타이머 설치 함수
        // 1인자 : 윈도우 핸들
        // 2인자 : 타이머의 ID
        // 3인자 : 타이머 주기, 기본값으로 1 / 1000초
        // 4인자 : NULL일 경우 설정한 주기대로 WM_TIMER 메세지를 발생시킴
        break;

    case WM_TIMER:
        InvalidateRect(hWnd, 0, TRUE);

        // InvalidateRect : 윈도우 화면 갱신 함수, 이 함수 호출 시, WM_PAINT 메세지 발생

        // 1인자 : 갱신할 윈도우 핸들
        // 2인자 : 윈도우에서 갱신할 범위 지정, RECT 구조체 주소를 넣어주며 NULL일 경우 윈도우 전체 영역에 적용
        // 3인자 : TRUE일 경우 그려져 있지 않는 부분도 갱신
        //        FALSE 일 경우 그린 부분만 갱신
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hWnd, &ps);

            // MoveToEx : 커서를 이동 시키는 함수
            // nullptr : 커서를 이동하기 전 위치를 output으로 반환
            // MoveToEx(hdc, 100, 100, nullptr);
            // LineTo(hdc, 200, 200);
            // LineTo(hdc, 100, 200);
            // LineTo(hdc, 100, 100);
            // LineTo(hdc, 200, 200);
            // 
            // MoveToEx(hdc, 200, 100, nullptr);
            // LineTo(hdc, 100, 200);

           //// 선 그리기 함수
           //LineTo(hdc, 200, 200);
           //LineTo(hdc, 200, 300);

            // 사각형 그리기 함수
            // Rectangle(hdc, 100, 100, 200, 200);

            //원 그리기 함수
            // Ellipse(hdc, 300, 300, 400, 400);
            HBRUSH GrayBrush = CreateSolidBrush(RGB(176, 224, 230));

            HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GrayBrush); // 셀렉트 오브젝트로 블루브러쉬 쓸꺼다 함수 선언해주고, 기존에 있던 흰색 브러쉬 반환

            Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

            HBRUSH BlueBrush = CreateSolidBrush(RGB(0, 255, 255));  //RGB를 이용해 파랑 브러쉬를 생성해준다

            OldBrush = (HBRUSH)SelectObject(hdc, BlueBrush); // 셀렉트 오브젝트로 블루브러쉬 쓸꺼다 함수 선언해주고, 기존에 있던 흰색 브러쉬 반환

            Ellipse(hdc, el.left, el.top, el.right, el.bottom);


            HBRUSH GreenBrush = CreateSolidBrush(RGB(127, 255, 212));  // 연두색

            OldBrush = (HBRUSH)SelectObject(hdc, GreenBrush); // 셀렉트 오브젝트로 블루브러쉬 쓸꺼다 함수 선언해주고, 기존에 있던 흰색 브러쉬 반환
              
            HPEN GreenPen =CreatePen(PS_SOLID,2, RGB(127, 255, 212));
            HPEN OldPen = (HPEN)SelectObject(hdc, GreenPen);
            
            Ellipse(hdc, _Score.right-10, _Score.top, _Score.right + 10, _Score.bottom); // 오른쪽 원

            Ellipse(hdc, _Score.left +10, _Score.top, _Score.left-10, _Score.bottom); // 왼쪽 원

            Rectangle(hdc, _Score.left, _Score.top, _Score.right, _Score.bottom); // 점수바

            HBRUSH YellowBrush = CreateSolidBrush(RGB(255, 255, 0));  // 노랑색

            OldBrush = (HBRUSH)SelectObject(hdc, YellowBrush); // 셀렉트 오브젝트로 블루브러쉬 쓸꺼다 함수 선언해주고, 기존에 있던 흰색 브러쉬 반환

            HPEN YellowPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
            (HPEN)SelectObject(hdc, YellowPen);

            Ellipse(hdc, _Exp.right-10, _Exp.top, _Exp.right + 10, _Exp.bottom); // 오른쪽 원

            Ellipse(hdc, _Exp.left+10, _Exp.top, _Exp.left-10, _Exp.bottom); // 왼쪽 원

            Rectangle(hdc, _Exp.left, _Exp.top, _Exp.right, _Exp.bottom); // 경험치바
    

            SelectObject(hdc, OldPen);

            BlueBrush = CreateSolidBrush(RGB(0, 255, 255));  

            OldBrush = (HBRUSH)SelectObject(hdc, BlueBrush); // 셀렉트 오브젝트로 블루브러쉬 쓸꺼다 함수 선언해주고, 기존에 있던 흰색 브러쉬 반환



           

            for (auto& iter : Bullet_1_List) // 왼쪽 위 대각선
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

                iter.right -= 10;
                iter.left -= 10;
                iter.bottom -= 10;
                iter.top -= 10;
            }
            for (auto& iter : Bullet_2_List) // 위 정면으로
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

                iter.top -= 13;
                iter.bottom -= 13;
            } 
          
            for (auto& iter : Bullet_3_List)  // 오른쪽 위 대각선
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

                iter.right += 10;
                iter.left += 10;
                iter.bottom -= 10;
                iter.top -= 10;
            }
            for (auto& iter : Bullet_4_List)  // 오른쪽 정면으로
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

                iter.left += 13;
                iter.right += 13;

            }
            for (auto& iter : Bullet_5_List)  // 오른쪽 아래 대각선
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);
                iter.left += 10;
                iter.right += 10;
                iter.top += 10;
                iter.bottom += 10;

            }
            for (auto& iter : Bullet_6_List)  // 아래 정면
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

                iter.top += 13;
                iter.bottom += 13;

            }
            for (auto& iter : Bullet_7_List)  // 왼쪽 아래 대각선
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);
                iter.left -= 10;
                iter.right -= 10;
                iter.top += 10;
                iter.bottom += 10;

            }
            for (auto& iter : Bullet_8_List)  // 왼쪽 정면
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

                iter.left -= 13;
                iter.right -= 13;

            }
            for (auto& iter : Bullet_9_List)  // 왼쪽 위 대각선
            {
                Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

                iter.left -= 10;
                iter.right -= 10;
                iter.top -= 10;
                iter.bottom -= 10;
            }
            HPEN TextPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // 검은색 펜
            OldPen = (HPEN)SelectObject(hdc, TextPen);

         

            SelectObject(hdc, OldPen);
            DeleteObject(TextPen);
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
        el.top = rc.top; // 원 크기 맞춰주기
        el.bottom = rc.bottom;
        el.left = rc.left;
        el.right = rc.right;

        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;

        case VK_RIGHT:

            rc.left += 30;
            rc.right += 30;
            bUp     = true;
            bDown   = true;
            bRight  = false;
            bLeft   = true;
            
            break;

        case VK_LEFT:

          
            rc.left -= 30;
            rc.right -= 30;

            bUp = true;
            bDown = true;
            bRight = true;
            bLeft = false;

            break;
        case VK_UP:
         
            rc.top -= 30;
            rc.bottom -= 30;


            bUp = false;
            bDown = true;
            bRight = true;
            bLeft = true;

            break;

        case VK_DOWN:
        
            rc.top += 30;
            rc.bottom += 30;

            bUp = true;
            bDown = false;
            bRight = true;
            bLeft = true;

            break;
            
        case VK_SPACE:
        {
            if (bUp == false) 
            {
                Bullet_1_List.push_back(rc);
                Bullet_2_List.push_back(rc);
                Bullet_3_List.push_back(rc);
              
                el.top += 30;
                el.bottom += 30;
            }
            else if (bDown == false)
            {
                Bullet_5_List.push_back(rc);
                Bullet_6_List.push_back(rc);
                Bullet_7_List.push_back(rc);
                el.top -= 30;
                el.bottom -= 30;
            }
            else if (bRight == false)
            {
                Bullet_3_List.push_back(rc);
                Bullet_4_List.push_back(rc);
                Bullet_5_List.push_back(rc);
                el.left -= 30;
                el.right -= 30;
            }
            else if (bLeft == false)
            {
                Bullet_7_List.push_back(rc);
                Bullet_8_List.push_back(rc);
                Bullet_9_List.push_back(rc);
               
                el.left += 30;
                el.right += 30;
            }
        }
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 숙제 1. 그림을 그려와라.
// 숙제 2. 세 방향으로 총알을 쏘도록 만들어라.

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


