#include "SRVManager.h"

const uint32_t SRVManager::kMaxCount = 512;

void SRVManager::Initialize(DirectXCommon* dxCommon) {

	// 引数をメンバ変数にコピー
	this->dxCommon = dxCommon;

	// ----------SRV用のDescriptorHeap生成----------
	// SRV用のヒープでディスクリプタの数は128。SRVはShader内で触るものなので、ShaderVisibleはtrue
	descriptorHeap = dxCommon->CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kMaxCount, true);

	// ----------SRV用のDescriptorSizeを取得----------
	descriptorSize = dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

uint32_t SRVManager::Allocate() {

	// 上限に達していないかチェック
	assert(useIndex < kMaxCount);

	// returnする番号を一旦記録しておく
	int index = useIndex;

	// 次回のために番号を1つ進める
	useIndex++;

	// 上で記録した番号をreturn
	return index;
}

D3D12_CPU_DESCRIPTOR_HANDLE SRVManager::GetCPUDescriptorHandle(uint32_t index) {

	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE SRVManager::GetGPUDescriptorHandle(uint32_t index) {

	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize * index);
	return handleGPU;
}

void SRVManager::CreateSRVforTexture(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT Format, UINT MIpLevels) {

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};

	// SRVの設定を行う
	srvDesc.Format = Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = MIpLevels;

	// 設定を元にSRVの生成
	dxCommon->GetDevice()->CreateShaderResourceView(pResource, &srvDesc, GetCPUDescriptorHandle(srvIndex));
}

void SRVManager::PreDraw() {

	ID3D12DescriptorHeap* descriptorHeaps[] = { descriptorHeap.Get() };
	dxCommon->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps);
}

void SRVManager::SetGraphicsRootDescriptorTable(UINT RootParameterIndex, uint32_t srvIndex) {

	dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(RootParameterIndex, GetGPUDescriptorHandle(srvIndex));
}

bool SRVManager::CheckAllocatable() {

	// 上限に達していなかったら
	if (useIndex < kMaxCount) {

		return true;

	// そうでなければ
	} else {

		return false;
	}
}