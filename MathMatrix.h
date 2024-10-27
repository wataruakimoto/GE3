#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"

class MathMatrix {

///=====================================================/// 
/// 静的メンバ関数
///=====================================================///
public:

	// 行列の加法
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

	// 行列の減法
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

	// 行列の積
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	// 逆行列
	static Matrix4x4 Inverse(const Matrix4x4& m);

	// 転置行列
	static Matrix4x4 Transpose(const Matrix4x4& m);

	// 単位行列の作成
	static Matrix4x4 MakeIdentity4x4();

	// 平行移動行列
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	// 拡大縮小行列
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	// 座標変換
	//static Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	// 3次元回転行列
	static Matrix4x4 MakeRotateMatrix(Vector3 radian);

	// 3次元アフィン変換行列
	static Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	// 透視投影行列
	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	// 正射影行列
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

///=====================================================/// 
/// オペレーター演算子
///=====================================================///
public:

	//static Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);

	//static Matrix4x4 operator+(const Matrix4x4& m);

	//static Matrix4x4& operator+=(Matrix4x4& m1, const Matrix4x4& m2);

	//static Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);

	//static Matrix4x4 operator-(const Matrix4x4& m);

	//static Matrix4x4& operator-=(Matrix4x4& m1, const Matrix4x4& m2);

	//static Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

	//static Matrix4x4 operator*(const Matrix4x4& m);

	//static Matrix4x4& operator*=(Matrix4x4& m1, const Matrix4x4& m2);
};