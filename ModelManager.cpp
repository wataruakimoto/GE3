#include "ModelManager.h"
#include "Model.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager* ModelManager::GetInstance() {

	if (instance == nullptr) {
		instance = new ModelManager;
	}
	return instance;
}

void ModelManager::Initialize(DirectXCommon* dxCommon) {

	// 3Dモデル共通部の生成・初期化
	modelCommon = new ModelCommon();
	modelCommon->Initialize(dxCommon);
}

void ModelManager::Finalize() {

	delete instance;
	instance = nullptr;
}

void ModelManager::LoadModel(const std::string& filePath) {

	// 読み込み済みモデルを検索
	if (models.contains(filePath)) {

		// 読み込み済みなら早期return
		return;
	}

	// モデルの生成とファイル読み込み、初期化
	std::unique_ptr<Model> model = std::make_unique<Model>();
	model->Initialize(modelCommon, "resources", filePath);

	// モデルをmapコンテナに格納する
	models.insert(std::make_pair(filePath, std::move(model)));
}

Model* ModelManager::FindModel(const std::string& filePath) {

	// 読み込み済みモデルを検索
	if (models.contains(filePath)) {

		// 読み込み済みなら早期return
		return models.at(filePath).get();
	}

	// ファイル名一致なし
	return nullptr;
}