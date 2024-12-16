#pragma once

#include "winApp/WinApp.h"

/// === フレームワーク === ///
class Framework {

///-------------------------------------------/// 
/// メンバ関数
///-------------------------------------------///
public:

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~Framework() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// 終了フラグのチェック
	/// </summary>
	/// <returns></returns>
	virtual bool IsEndRequest() { return endRequest_; }

	/// <summary>
	/// 実行
	/// </summary>
	void Run();

///-------------------------------------------/// 
/// メンバ変数
///-------------------------------------------///
protected:

	// ゲーム終了フラグ
	bool endRequest_ = false;

	// WindowsAPIのポインタ
	WinApp* winApp = nullptr;
};