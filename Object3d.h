#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include <fstream>
#include <vector>
#include "DirectXCommon.h"

/// === 3Dオブジェクト基盤 === ///
class Object3dCommon;

/// === 3Dオブジェクト === ///
class Object3d {

///=====================================================/// 
/// 構造体
///=====================================================///
public:

	// 頂点データ
	struct VertexData {
		Vector4 position;
		Vector2 texcoord;
		Vector3 normal;
	};

	// 座標変換行列
	struct TransformationMatrix {
		Matrix4x4 WVP;
		Matrix4x4 world;
	};

	// マテリアルデータ
	struct Material {
		Vector4 color;
		bool enableLighting;
		float padding[3];
		Matrix4x4 uvTransform;
	};

	// 平行光源データ
	struct DirectionalLight {
		Vector4 color; // !< ライトの色
		Vector3 direction; // !< ライトの向き
		float intensity; // !< 輝度
	};

	// マテリアルデータ
	struct MaterialData {
		std::string textureFilePath;
		uint32_t textureIndex = 0;
	};

	// モデルデータ
	struct ModelData {
		std::vector<VertexData> vertices;
		MaterialData material;
	};

	// 変換データ
	struct Transform {
		Vector3 scale;
		Vector3 rotate;
		Vector3 translate;
	};

///=====================================================/// 
/// メンバ関数
///=====================================================///
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Object3dCommon* object3dCommon);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// .mtlファイル読み込み
	/// </summary>
	/// <param name="directoryPath">ディレクトリーパス</param>
	/// <param name="filename">ファイル名</param>
	/// <returns></returns>
	static MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// .objファイル読み込み
	/// </summary>
	/// <param name="directoryPath">ディレクトリーパス</param>
	/// <param name="filename">ファイル名</param>
	/// <returns></returns>
	static ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

///=====================================================/// 
/// クラス内関数
///=====================================================///
private:

	/// <summary>
	/// 頂点データ初期化
	/// </summary>
	void InitializeVertexData();

	/// <summary>
	/// 座標変換行列データ初期化
	/// </summary>
	void InitializeTransformationMatrixData();

	/// <summary>
	/// マテリアルデータ初期化
	/// </summary>
	void InitializeMaterialData();

	/// <summary>
	/// 平行光源データ初期化
	/// </summary>
	void InitializeDirectionalLightData();

///=====================================================/// 
/// メンバ変数
///=====================================================///
private:

	// 基盤のポインタ
	Object3dCommon* object3dCommon_ = nullptr;

	// 頂点リソース
	Microsoft::WRL::ComPtr <ID3D12Resource> vertexResource;
	// 座標変換行列リソース
	Microsoft::WRL::ComPtr <ID3D12Resource> transformationMatrixResource;
	// マテリアルリソース
	Microsoft::WRL::ComPtr <ID3D12Resource> materialResource;
	// 平行光源リソース
	Microsoft::WRL::ComPtr <ID3D12Resource> directionalLightResource;

	// 頂点データ
	VertexData* vertexData = nullptr;
	// 座標変換行列データ
	TransformationMatrix* transformationMatrixData = nullptr;
	// マテリアルデータ
	Material* materialData = nullptr;
	// 平行光源データ
	DirectionalLight* directionalLightData = nullptr;

	// モデルデータ
	ModelData modelData;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Transform transform;

	Transform cameraTransform;
};