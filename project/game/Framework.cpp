#include "Framework.h"

void Framework::Initialize() {

	// WindowsAPIの生成・初期化
	winApp = new WinApp();
	winApp->Initialize();

	// ウィンドウを表示する
	ShowWindow(winApp->GetHwnd(), SW_SHOW);
}

void Framework::Update() {

}

void Framework::Draw() {

}

void Framework::Finalize() {

}

void Framework::Run() {

	// ゲームループ
	while (true) {

		// 更新
		Update();

		// 終了リクエストが来たら抜ける
		if (IsEndRequest()) {
			break;
		}

		// 描画
		Draw();
	}

	// 終了
	Finalize();
}