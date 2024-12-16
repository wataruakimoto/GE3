#include "game/Framework.h"
#include "game/MyGame.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ゲームの生成
	Framework* game = new MyGame();

	// ゲーム実行
	game->Run();

	// ゲーム削除
	delete game;

	return 0;
}