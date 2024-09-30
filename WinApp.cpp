#include "WinApp.h"
// int32_t���g������
#include <cstdint>
// ImGui���g������
#include "externals/imgui/imgui.h"

// extern�錾
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// ImGui���}�E�X����ł���悤�ɂ���
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	// ���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg) {
		// �E�B���h�E���j�����ꂽ
	case WM_DESTROY:
		// OS�ɑ΂��āA�A�v���̏I����`����
		PostQuitMessage(0);
		return 0;
	}

	// �W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::Initialize() {

	// ���C���X���b�h�ł�MTA��COM���p
	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	WNDCLASS wc{};
	// �E�B���h�E�v���V�[�W��
	wc.lpfnWndProc = WindowProc;
	// �E�B���h�E�N���X��(�Ȃ�ł��ǂ�)
	wc.lpszClassName = L"CG2WindowClass";
	// �C���X�^���X�n���h��
	wc.hInstance = GetModuleHandle(nullptr);
	// �J�[�\��
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// �E�B���h�E�N���X��o�^����
	RegisterClass(&wc);

	// �N���C�A���g�̗̈�̃T�C�Y
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	// �E�B���h�E�T�C�Y��\���\���̂ɃN���C�A���g�̈������
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	// �N���C�A���g�̈�����Ɏ��ۂ̃T�C�Y��wrc��ύX���Ă��炤
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̐���
	HWND hwnd = CreateWindow(
		wc.lpszClassName,	  // ���p����N���X��
		L"CG2",				  // �^�C�g���o�[�̕���(���ł��ǂ�)
		WS_OVERLAPPEDWINDOW,  // �悭����E�B���h�E�X�^�C��
		CW_USEDEFAULT,		  // �\��X���W(Windows�ɔC����)
		CW_USEDEFAULT,		  // �\��Y���W(WindowsOS�ɔC����)
		wrc.right - wrc.left, // �E�B���h�E����
		wrc.bottom - wrc.top, // �E�B���h�E�c��
		nullptr,			  // �e�E�B���h�E�n���h��
		nullptr,			  // ���j���[�n���h��
		wc.hInstance,		  // �C���X�^���X�n���h��
		nullptr				  // �I�v�V����
	);
}

void WinApp::Update() {

}