#pragma once

//=====================================================================
// Win32 ���ڼ�ͼ�λ��ƣ�Ϊ device �ṩһ�� DibSection �� FB
//=====================================================================

#include <windows.h>
#include <tchar.h>


int screen_w, //��Ļ��
	screen_h, //��Ļ��
	screen_exit = 0; //�˳�����
int screen_keys[512];	// ��ǰ���̰���״̬

static HWND screen_handle = NULL;		// ������ HWND
static HDC screen_dc = NULL;			// ���׵� HDC
static HBITMAP screen_hb = NULL;		// DIB
static HBITMAP screen_ob = NULL;		// �ϵ� BITMAP

unsigned char *screen_fb = NULL;		// frame buffer
long screen_pitch = 0;

int screen_init(int w, int h, const TCHAR *title);	// ��Ļ��ʼ��
int screen_close(void);								// �ر���Ļ
void screen_dispatch(void);							// ������Ϣ
void screen_update(void);							// ��ʾ FrameBuffer

// win32 event handler
static LRESULT screen_events(HWND, UINT, WPARAM, LPARAM);

// ��ʼ�����ڲ����ñ���
int screen_init(int w, int h, const TCHAR *title) {
	//https://baike.baidu.com/item/WNDCLASS/6488732?fr=aladdin
	//����ĳһ�ര�ڵ���Ϣ
	WNDCLASS wc = {
		CS_BYTEALIGNCLIENT, // ��������
		(WNDPROC)screen_events, //���ڴ����� lpfnWndProc
		0, //������չ cbClsExtra
		0, //����ʵ����չ cbWndExtra
		0, //ʵ����� hInstance
		NULL,//���ڵ���С��ͼ�� hIcon
		NULL, //��������� hCursor
		NULL, //���ڱ���ɫ hbrBackground
		NULL, //���ڲ˵� lpszMenuName
		_T("SCREEN3.1415926") //�������� lpszClassName 
	};
	// https://docs.microsoft.com/zh-cn/windows/desktop/api/wingdi/ns-wingdi-tagbitmapinfo
	// �豸�޹�λͼ�ļ�
	BITMAPINFO bi = {
		{ sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB, w * h * 4, 0, 0, 0, 0 }
		//https://docs.microsoft.com/zh-cn/windows/desktop/api/wingdi/ns-wingdi-bitmapinfoheader
	};
	RECT rect = { 0, 0, w, h };
	int wx, wy, sx, sy;
	LPVOID ptr;
	// https://baike.baidu.com/item/HDC/16710
	/* HDC�豸��������һ�ְ����й�ĳ���豸������ʾ�����ӡ�����Ļ���������Ϣ�� Windows ���ݽṹ��
	���л��Ƶ��ö�ͨ���豸�����Ķ�����У���Щ�����װ�����ڻ�����������״���ı��� Windows API */
	HDC hDC;

	screen_close();

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClass(&wc)) return -1;

	//https://baike.baidu.com/item/CreateWindow
	screen_handle = CreateWindow(
		_T("SCREEN3.1415926"), //LPCTSTR lpClassName ���ڵ�����
		title, //LPCTSTR lpWindowName ָ��һ��ָ���������Ŀս������ַ���ָ��
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //DWORD dwStyle ָ���������ڵķ��
		0, //int x ָ�����ڵĳ�ʼˮƽλ��
		0, //int y ָ�����ڵĳ�ʼ��ֱλ��
		0, //int nWidth ���豸��Ԫָ�����ڵĿ��
		0, //int nHeight ���豸��Ԫָ�����ڵĸ߶�
		NULL, //HWND hWndParent ָ�򱻴������ڵĸ����ڻ������ߴ��ڵľ��
		NULL, //HMENU hMenu �˵����
		wc.hInstance, //HANDLE hlnstance �봰���������ģ��ʵ���ľ��
		NULL //LPVOID lpParam ָ��һ��ֵ��ָ�룬��ֵ���ݸ�����WM_CREATE��Ϣ
	);
	if (screen_handle == NULL) return -2;

	screen_exit = 0;
	hDC = GetDC(screen_handle);
	screen_dc = CreateCompatibleDC(hDC);
	ReleaseDC(screen_handle, hDC);

	screen_hb = CreateDIBSection(screen_dc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (screen_hb == NULL) return -3;

	screen_ob = (HBITMAP)SelectObject(screen_dc, screen_hb);
	screen_fb = (unsigned char*)ptr;
	screen_w = w;
	screen_h = h;
	screen_pitch = w * 4;

	AdjustWindowRect(&rect, GetWindowLong(screen_handle, GWL_STYLE), 0);
	wx = rect.right - rect.left;
	wy = rect.bottom - rect.top;
	sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(screen_handle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(screen_handle);

	ShowWindow(screen_handle, SW_NORMAL);
	screen_dispatch();

	memset(screen_keys, 0, sizeof(int) * 512);
	memset(screen_fb, 0, w * h * 4);

	return 0;
}

int screen_close(void) {
	if (screen_dc) {
		if (screen_ob) {
			SelectObject(screen_dc, screen_ob);
			screen_ob = NULL;
		}
		DeleteDC(screen_dc);
		screen_dc = NULL;
	}
	if (screen_hb) {
		DeleteObject(screen_hb);
		screen_hb = NULL;
	}
	if (screen_handle) {
		CloseWindow(screen_handle);
		screen_handle = NULL;
	}
	return 0;
}

static LRESULT screen_events(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE: screen_exit = 1; break;
	case WM_KEYDOWN: screen_keys[wParam & 511] = 1; break;
	case WM_KEYUP: screen_keys[wParam & 511] = 0; break;
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

//�ַ���Ϣ
void screen_dispatch(void) 
{
	MSG msg;
	while (1) 
	{

		// �ú���Ϊһ����Ϣ����߳���Ϣ���У���������Ϣ��������ڣ�����ָ���Ľṹ
		if (!PeekMessage(&msg, //������Ϣ��Ϣ��MSG�ṹָ��
						NULL, //����Ϣ�����Ĵ��ھ��
						0, //ָ����������Ϣ��Χ��ĵ�һ����Ϣ
						0, //ָ����������Ϣ��Χ������һ����Ϣ
						PM_NOREMOVE //ȷ����Ϣ��α����� PM_NOREMOVE��PeekMessage�������Ϣ���Ӷ����������
						)
			) 
			break;

		// �ӵ����̵߳���Ϣ������ȡ��һ����Ϣ���������ָ���Ľṹ
		if (!GetMessage(&msg, //ָ��MSG�ṹ��ָ�룬�ýṹ���̵߳���Ϣ�����������Ϣ��Ϣ
						NULL, //ȡ������Ϣ�Ĵ��ڵľ��
						0, //ָ������������С��Ϣֵ������
						0 //ָ���������������Ϣֵ������
						)
			)
			break;
		// �ú����ַ�һ����Ϣ�����ڳ���
		DispatchMessage(&msg);
	}
}


void screen_update(void) {
	HDC hDC = GetDC(screen_handle);
	BitBlt(
		hDC, // hDestDC��ָ��Ŀ���豸�����ľ��
		0, // x��ָ��Ŀ������������Ͻǵ�X���߼�����
		0, // y��ָ��Ŀ������������Ͻǵ�Y���߼�����
		screen_w, // nWidth��ָ��Դ��Ŀ�����������߼����
		screen_h, // nHeight��ָ��Դ��Ŀ�����������߼��߶�
		screen_dc, // hSrcDC��ָ��Դ�豸�����ľ��
		0, // xSrc��ָ��Դ�����������Ͻǵ�X���߼�����
		0, // ySrc��ָ��Դ�����������Ͻǵ�Y���߼�����
		SRCCOPY // ָ����դ�������롣��Щ���뽫����Դ�����������ɫ���ݣ������Ŀ������������ɫ������������������ɫ��
				// SRCCOPY����Դ��������ֱ�ӿ�����Ŀ���������
	);
	ReleaseDC(screen_handle, hDC); //ReleaseDC�����ͷ��豸�����Ļ�����DC��������Ӧ�ó���ʹ��
	screen_dispatch();
}
