#pragma once

// WindowsAPI���g������
#include <Windows.h>

// WindowsAPI
class WinApp {

public: // �ÓI�����o�֐�
	/// <summary>
	/// �E�B���h�E�v���V�[�W��
	/// </summary>
	/// <param name="hwnd"></param>
	/// <param name="msg"></param>
	/// <param name="wparam"></param>
	/// <param name="lparam"></param>
	/// <returns></returns>
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
};