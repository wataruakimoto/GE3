#pragma once

#include "DirectXCommon.h"

/// === SRV管理 === ///
class SRVManager {

///-------------------------------------------/// 
/// メンバ変数
///-------------------------------------------///
private:

	// DirectXCommonのポインタ
	DirectXCommon* dxCommon = nullptr;

	// SRV用デスクリプタサイズ
	uint32_t descriptorSize;

	// SRV用デスクリプタヒープ
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> descriptorHeap;

	// 次に使用するSRVインデックス
	uint32_t useIndex = 0;

///-------------------------------------------/// 
/// 定数
///-------------------------------------------///
public:

	// 最大SRV枚数(最大テクスチャ枚数)
	static const uint32_t kMaxCount;

///-------------------------------------------/// 
/// メンバ関数
///-------------------------------------------///
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon);

	/// <summary>
	/// メモリ確保
	/// </summary>
	/// <returns>uint32_t</returns>
	uint32_t Allocate();

	/// <summary>
	/// SRVのCPUのデスクリプタハンドルを取得
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);

	/// <summary>
	/// SRVのGPUのデスクリプタハンドルを取得
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);

	/// <summary>
	/// テクスチャ用のSRV生成
	/// </summary>
	/// <param name="srvIndex"></param>
	/// <param name="pResource"></param>
	/// <param name="Format"></param>
	/// <param name="MIpLevels"></param>
	void CreateSRVforTexture(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT Format, UINT MIpLevels);

	/// <summary>
	/// StructuredBuffer用のSRV作成
	/// </summary>
	/// <param name="srvIndex"></param>
	/// <param name="pResource"></param>
	/// <param name="numElements"></param>
	/// <param name="structureByteStride"></param>
	void CreateSRVforStructuredBuffer(uint32_t srvIndex, ID3D12Resource* pResource, UINT numElements, UINT structureByteStride);

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// SRVセットコマンド
	/// </summary>
	/// <param name="RootParameterIndex"></param>
	/// <param name="srvIndex"></param>
	void SetGraphicsRootDescriptorTable(UINT RootParameterIndex, uint32_t srvIndex);

	/// <summary>
	/// 確保可能かチェック
	/// </summary>
	/// <returns>bool</returns>
	bool CheckAllocatable();
};