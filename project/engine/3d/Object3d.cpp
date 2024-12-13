#include "Object3d.h"
#include "Object3dCommon.h"
#include <cassert>
#include <sstream>
#include "math/MathMatrix.h"
#include "winApp/WinApp.h"
#include "2d/TextureManager.h"
#include "ModelManager.h"
#include "Camera.h"

using namespace MathMatrix;

void Object3d::Initialize(Object3dCommon* object3dCommon){

	// 引数をメンバ変数に代入
	this->object3dCommon_ = object3dCommon;

	// デフォルトカメラをセット
	this->camera = object3dCommon->GetDefaultCamera();

	InitializeTransformationMatrixData();

	InitializeDirectionalLightData();

	InitializeCameraData();

	// Transform変数を作る
	transform = { {1.0f,1.0f,1.0f},{0.0f,3.14f,0.0f},{0.0f,0.0f,0.0f} };
}

void Object3d::Update(){

	/// === TransformからWorldMatrixを作る === ///
	Matrix4x4 worldMatrix = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);

	// WVP
	Matrix4x4 worldViewProjectionMatrix;

	// カメラがあればviewProjectionをもらってWVPの計算を行う
	if (camera) {

		const Matrix4x4& viewProjectionMatrix = camera->GetViewProjectionMatrix();
		worldViewProjectionMatrix = worldMatrix * viewProjectionMatrix;


	// カメラがなければworldMatrixを代入
	} else {

		worldViewProjectionMatrix = worldMatrix;
	}

	transformationMatrixData->WVP = worldViewProjectionMatrix;
	transformationMatrixData->world = worldMatrix;

	cameraData = camera->GetTranslate();
}

void Object3d::Draw(){

	/// === 座標変換行列CBufferの場所を設定 === ///
	object3dCommon_->GetDxCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResource->GetGPUVirtualAddress());

	/// === 平行光源CBufferの場所を設定=== ///
	object3dCommon_->GetDxCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());

	/// === カメラCBufferの場所を設定=== ///
	object3dCommon_->GetDxCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(4, cameraResource->GetGPUVirtualAddress());

	// 3Dモデルが割り当てられていれば描画する
	if (model) {
		model->Draw();
	}
}

void Object3d::InitializeTransformationMatrixData(){

	/// === TransformationMatrixResourceを作る === ///
	transformationMatrixResource = object3dCommon_->GetDxCommon()->CreateBufferResource(sizeof(TransformationMatrix));

	/// === TransformationMatrixResourceにデータを書き込むためのアドレスを取得してtransformationMatrixDataに割り当てる === ///
	transformationMatrixResource->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixData));

	/// === TransformationMatrixDataの初期値を書き込む === ///
	transformationMatrixData->WVP = MakeIdentity4x4(); // 単位行列を書き込む
	transformationMatrixData->world = MakeIdentity4x4(); // 単位行列を書き込む
}

void Object3d::InitializeDirectionalLightData() {

	/// === DirectionalLightResourceを作る === ///
	directionalLightResource = object3dCommon_->GetDxCommon()->CreateBufferResource(sizeof(DirectionalLight));

	/// === DirectionalLightResourceにデータを書き込むためのアドレスを取得してDirectionalLightDataに割り当てる === ///
	directionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));

	/// === DirectionalLightDataの初期値を書き込む === ///
	directionalLightData->color = { 1.0f, 1.0f, 1.0f, 1.0f }; // 白を書き込む
	directionalLightData->direction = { 0.0f, -1.0f, 0.0f }; // 向きは下から
	directionalLightData->intensity = 1.0f; // 輝度は最大
}

void Object3d::InitializeCameraData() {

	/// === CameraResource === ///
	cameraResource = object3dCommon_->GetDxCommon()->CreateBufferResource(sizeof(Vector3));

	/// === CameraResourceにデータを書き込むためのアドレスを取得してCameraDataに割り当てる === ///
	cameraResource->Map(0, nullptr, reinterpret_cast<void**>(&cameraData));

	/// === CameraDataの初期値を書き込む === ///
	cameraData = camera->GetTranslate();
}

void Object3d::SetModel(const std::string& filePath) {

	// モデルを検索してセットする
	model = ModelManager::GetInstance()->FindModel(filePath);
}