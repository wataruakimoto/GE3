#include "TextureManager.h"
#include "utility/StringUtility.h"

using namespace StringUtility;

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::GetInstance() {

	if (instance == nullptr) {
		instance = new TextureManager;
	}
	return instance;
}

void TextureManager::Initialize(DirectXCommon* dxCommon, SRVManager* srvManager) {

	// 引数をメンバ変数に代入
	dxCommon_ = dxCommon;
	srvManager_ = srvManager;

	// SRVの数と同数
	textureDatas.reserve(SRVManager::kMaxCount);
}

void TextureManager::Finalize() {
	delete instance;
	instance = nullptr;
}

uint32_t TextureManager::kSRVIndexTop = 1;

void TextureManager::LoadTexture(const std::string& filePath) {

	/// === ファイル読み込み === ///

	// 読み込み済みテクスチャを検索
	
	//auto it = std::find_if(
	//	textureDatas.begin(),
	//	textureDatas.end(),
	//	[&](TextureData& textureData) {return textureData.filePath == filePath; }
	//);
	//
	//if (it != textureDatas.end()) {
	//	// 読み込み済みなら早期return
	//	return;
	//}

	if (textureDatas.contains(filePath)) {
		// 見つかり次第return
		return;
	}

	// テクスチャ枚数上限チェック
	assert(srvManager_->CheckAllocatable());

	DirectX::ScratchImage image{};
	// テクスチャファイルを読んでプログラムで扱えるようにする
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	DirectX::ScratchImage mipImages{};
	// ミップマップの作成
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	/// === テクスチャデータ追加 === ///

	// 追加したテクスチャデータの参照を取得する
	//TextureData& textureData = textureDatas.back();
	
	// テクスチャデータを追加して書き込む
	TextureData& textureData = textureDatas[filePath];

	/// === テクスチャデータ書き込み === ///

	//textureData.filePath = filePath;
	textureData.metaData = mipImages.GetMetadata();
	textureData.resource = dxCommon_->CreateTextureResource(textureData.metaData);

	/// === テクスチャデータ送信 === ///

	dxCommon_->UploadTextureData(textureData.resource, mipImages);

	/// === デスクリプタハンドルの計算 === ///

	// テクスチャデータの要素数番号をSRVのインデックスとする
	//uint32_t srvIndex = static_cast<uint32_t>(textureDatas.size() - 1) + kSRVIndexTop;

	//textureData.srvHandleCPU = dxCommon_->GetSRVCPUDescriptorHandle(srvIndex);
	//textureData.srvHandleGPU = dxCommon_->GetSRVGPUDescriptorHandle(srvIndex);

	// SRV確保
	textureData.srvIndex = srvManager_->Allocate();
	textureData.srvHandleCPU = srvManager_->GetCPUDescriptorHandle(textureData.srvIndex);
	textureData.srvHandleGPU = srvManager_->GetGPUDescriptorHandle(textureData.srvIndex);
}

uint32_t TextureManager::GetTextureIndexByFilePath(const std::string& filePath) {

	// 読み込み済みテクスチャを検索

	//auto it = std::find_if(
	//	textureDatas.begin(),
	//	textureDatas.end(),
	//	[&](TextureData& textureData) {return textureData.filePath == filePath; }
	//);
	//
	//if (it != textureDatas.end()) {
	//	// 読み込み済みなら要素番号を返す
	//	uint32_t textureIndex = static_cast<uint32_t>(std::distance(textureDatas.begin(), it));
	//	return textureIndex;
	//}

	auto it = textureDatas.find(filePath);

	if (it != textureDatas.end()) {
		// 読み込み済みなら要素番号を返す
		return it->second.srvIndex;
	}

	assert(0);
	return 0;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetSRVGPUHandle(const std::string& filePath) {

	// 範囲外指定違反チェック
	assert(srvManager_->CheckAllocatable());

	TextureData& textureData = textureDatas[filePath];
	return textureData.srvHandleGPU;
}

const DirectX::TexMetadata& TextureManager::GetMetadata(const std::string& filePath) {

	// 範囲外指定違反チェック
	assert(srvManager_->CheckAllocatable());

	TextureData& textureData = textureDatas[filePath];
	return textureData.metaData;
}