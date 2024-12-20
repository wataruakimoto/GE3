#pragma once

#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4x4.h"
#include <fstream>
#include <vector>
#include "base/DirectXCommon.h"
#include "Model.h"

/// === カメラ === ///
class Camera;

/// === モデル基盤 === ///
class ModelCommon;

/// === 3Dオブジェクト基盤 === ///
class Object3dCommon;

/// === 3Dオブジェクト === ///
class Object3d {

///=====================================================/// 
/// 構造体
///=====================================================///
public:

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

///=====================================================/// 
/// クラス内関数
///=====================================================///
private:

	/// <summary>
	/// 座標変換行列データ初期化
	/// </summary>
	void InitializeTransformationMatrixData();

	/// <summary>
	/// 平行光源データ初期化
	/// </summary>
	void InitializeDirectionalLightData();

///=====================================================/// 
/// セッター
///=====================================================///
public:

	/// <summary>
	/// 大きさのセッター
	/// </summary>
	/// <param name="scale">大きさ</param>
	void SetScale(const Vector3& scale) { this->transform.scale = scale; }

	/// <summary>
	/// 回転のセッター
	/// </summary>
	/// <param name="rotate">回転</param>
	void SetRotate(const Vector3& rotate) { this->transform.rotate = rotate; }

	/// <summary>
	/// 位置のセッター
	/// </summary>
	/// <param name="translate">位置</param>
	void SetTranslate(const Vector3& translate) { this->transform.translate = translate; }

	/// <summary>
	/// モデルのセッター
	/// </summary>
	/// <param name="model">モデル</param>
	void SetModel(Model* model) { this->model = model; }

	/// <summary>
	/// モデルのセッター
	/// </summary>
	/// <param name="filePath"></param>
	void SetModel(const std::string& filePath);

	/// <summary>
	/// カメラのセッター
	/// </summary>
	/// <param name="camera">カメラ</param>
	void SetCamera(Camera* camera) { this->camera = camera; }

///=====================================================/// 
/// ゲッター
///=====================================================///
public:

	/// <summary>
	/// 大きさのゲッター
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale() const { return transform.scale; }

	/// <summary>
	/// 回転のゲッター
	/// </summary>
	/// <returns></returns>
	const Vector3& GetRotate() const { return transform.rotate; }

	/// <summary>
	/// 位置のゲッター
	/// </summary>
	/// <returns></returns>
	const Vector3& GetTranslate() const { return transform.translate; }

///=====================================================/// 
/// メンバ変数
///=====================================================///
private:

	// 基盤のポインタ
	Object3dCommon* object3dCommon_ = nullptr;

	// 座標変換行列リソース
	Microsoft::WRL::ComPtr <ID3D12Resource> transformationMatrixResource;
	// 平行光源リソース
	Microsoft::WRL::ComPtr <ID3D12Resource> directionalLightResource;

	// 座標変換行列データ
	TransformationMatrix* transformationMatrixData = nullptr;
	// 平行光源データ
	DirectionalLight* directionalLightData = nullptr;

	Transform transform;

	// モデル基盤のポインタ
	ModelCommon* modelCommon_ = nullptr;

	// モデル
	Model* model = nullptr;

	// カメラ
	Camera* camera = nullptr;
};