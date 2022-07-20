#include "Engine.h"

DEFINITION_SINGLE(CEngine)

bool CEngine::m_Loop = true;

CEngine::CEngine()	:
	m_hInst(0),
	m_hWnd(0)
{
}

CEngine::~CEngine()
{
}

bool CEngine::Init(HINSTANCE hInst, const TCHAR* Title,
    const TCHAR* ClassName, int IconID, int SmallIconID,
    unsigned int WindowWidth, unsigned int WindowHeight,
	unsigned int DeviceWidth, unsigned int DeviceHeight, bool WindowMode)
{
	m_hInst = hInst;
	m_WindowRS.Width = WindowWidth;
	m_WindowRS.Height = WindowHeight;

	Register(ClassName, IconID, SmallIconID);

	Create(Title, ClassName);

	return true;
}

int CEngine::Run()
{
    // �ü���� ������� �޼����� ������ ���� ����ü�̴�.
    MSG msg;

    // GetMessage : �޼��� ť���� �޼����� �������� �Լ��̴�.
    // ��, �޼��� ť�� ������� ��� �޼����� ���ö����� �� �Լ��� �������� �� ����.
    // �̷��� ���缭 ����ϰ� �ִ� ���� ����ŷ ��� ��� �Ѵ�.
    // ť�� �� �����ִ� �ð��� �������� ����Ÿ���̶�� �θ���.
    while (m_Loop)
    {
        // PeekMessage : �� �Լ��� �޼��� ť���� �޼����� ��������
        // �Լ��̴�. ��, �� �Լ��� �޼��� ť�� ������� ��� false
        // �� ��ȯ�ϸ� �ٷ� ���������� �ȴ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // �޼���ť���� ������ �޼����� TranslateMessage �Լ��� �Ѱ��ָ� ���� Ű���� 
            // F1, ����Ű ���� Ű������ �Ǵ����ش�.
            // �̷��� Ű���� WM_KEYDOWN���� �޼����� �ν��� �ǰ�
            // ���� Ű�� WM_CHAR�� �ν��� �ȴ�.
            // Ű�� ������ ����Ű�� ��� WM_CHAR�� ����������ϱ� ������ WM_KEYDOWN
            // �� �Ͼ�� ����Ű�� ��� WM_CHAR�޼����� �߰��� ���� �޼��� ť��
            // �־��ش�.
            TranslateMessage(&msg);

            // DispatchMessage �Լ��� �޼���ť���� ������ �޼����� �޼��� ó�� �Լ���
            // �����ش�. WndProc�� �����ִ� ���̴�.
            DispatchMessage(&msg);
        }

        // �޼��� ť�� ������� ��� ���۵ȴ�. ��, �������� ����Ÿ�ӽ�
        // �� else ������ ���۵Ǳ� ������ ���⿡ ���� ���ӷ�����
        // �ۼ��ϸ� �ȴ�.
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CEngine::Logic()
{
}

void CEngine::Input(float DeltaTime)
{
}

bool CEngine::Update(float DeltaTime)
{
	return false;
}

bool CEngine::PostUpdate(float DeltaTime)
{
	return false;
}

void CEngine::Collision(float DeltaTime)
{
}

void CEngine::Render(float DeltaTime)
{
}

void CEngine::Register(const TCHAR* ClassName, int IconID, int SmallIconID)
{
    // �������Ϳ� ����� ������ Ŭ���� ����ü�� ������ش�.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;

    // �޼���ť���� ������ �޼����� ���ڷ� �����ϸ� ȣ���� �Լ��� �Լ� �ּҸ�
    // ����Ѵ�.
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    // ������ �ν��Ͻ��� ����Ѵ�.
    wcex.hInstance = m_hInst;

    // �������Ͽ� ����� �������� ����Ѵ�.
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IconID));

    // ���콺 Ŀ�� ����� �����Ѵ�.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // �޴��� ������� ������ �����Ѵ�.
    wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_MY220428);

    // ����� Ŭ������ �̸��� �����ڵ� ���ڿ��� ���� �����Ѵ�.
    // TEXT ��ũ�δ� ������Ʈ ������ �����ڵ�� �Ǿ����� ��� �����ڵ� ���ڿ��� ���������
    // ��Ƽ����Ʈ�� �Ǿ����� ��� ��Ƽ����Ʈ ���ڿ��� ��������� �ȴ�.
    wcex.lpszClassName = ClassName;

    // ������â �»�ܿ� ǥ���� ���� �������� ����Ѵ�.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(SmallIconID));

    RegisterClassExW(&wcex);
}

bool CEngine::Create(const TCHAR* Title, const TCHAR* ClassName)
{
    // ������ â�� �����Ѵ�.
    // 1�� ���ڴ� ������ Ŭ������ ����� �̸��̴�.
    // 2�� ���ڴ� Ÿ��Ʋ�ٿ� ǥ���� �̸��̴�.
    // 3�����ڴ� �� ������ â�� ��� ���������� �����ϴ� �ɼ��̴�.
    // 4, 5�� ���ڴ� �� ������ â�� ������ ȭ�鿡���� ��ġ�� �����Ѵ�.
    // �ȼ��� �����Ѵ�. ���� ��� 1920, 1080 �ػ󵵶�� �ű⿡�� ���ϴ� ���� �־��ָ�
    // �ش� ��ġ�� ������ �ȴ�.
    // 4���� ������ǥ, 5���� ������ǥ�� ����� �ȴ�.
    // 6��, 7�� ���ڴ� ������â�� ����, ������ ũ�⸦ �����Ѵ�.
    // �ȼ������� ������ ���ش�.
    // 8�� ���ڴ� �θ������찡 �ִٸ� �θ��������� �ڵ��� �����Ѵ�.
    // ������ nullptr�� �����Ѵ�.
    // 9�� ���ڴ� �޴��� �ִٸ� �޴� �ڵ��� �־��ְ� ������ nullptr�� �����Ѵ�.
    // 10�� ���ڴ� ������ �ν��Ͻ��� �����Ͽ� �� ������ �ν��Ͻ��� ���� ������ â��
    // ������ְ� �ȴ�.
    // ������ â�� ������ְ� ���������� ��������ٸ� ������ ������ â�� �ڵ���
    // ��ȯ���ش�.
    // HWND �� ������ �ڵ��� �ǹ��Ѵ�.
    // ���� ������ ����� �ȵǾ��ٸ� 0�� ��ȯ�Ѵ�.
    m_hWnd = CreateWindowW(ClassName, Title, WS_OVERLAPPEDWINDOW,
        100, 0, 0, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return false;
    }

    // RECT : �簢���� ǥ���ϱ� ���ؼ� �����ϴ� ����ü�̴�.
    // left, top, right, bottom ������ �̷���� �ִ�.
    // ������ ũ�⸦ ǥ���ϴ� Rect ����ü�� �ϳ� ������ش�.
    RECT    rc = { 0, 0, (LONG)m_WindowRS.Width, (LONG)m_WindowRS.Height };

    // ������ ������ ũ�⸸ŭ Ŭ���̾�Ʈ ������ ũ��� ��� ���ؼ�
    // �ʿ��� ���� �������� ũ�⸦ ���´�.
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // ������ ���� ũ��� ������ â�� ũ�⸦ �����Ѵ�.
    MoveWindow(m_hWnd, 50, 50, rc.right - rc.left,
        rc.bottom - rc.top, TRUE);

    // ������ â�� �����ش�. 1�����ڿ� �� �ڵ��� ������ â�� �������� ������
    // �������ش�.
    ShowWindow(m_hWnd, SW_SHOW);

    // �� �Լ��� ȣ���Ͽ� Ŭ���̾�Ʈ ������ ����� ���ŵǾ��ٸ� 0�� �ƴ� ���� ��ȯ�ϰ�
    // ������ �������� ��� 0�� ��ȯ�Ѵ�.
    UpdateWindow(m_hWnd);

    return true;
}

LRESULT CEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, 
    LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // �����찡 ����ɶ� ������ �޼����̴�.
        m_Loop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}