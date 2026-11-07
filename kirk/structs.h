#pragma once
#include <cmath>

struct Vector2 {
	float x, y;

	Vector2() :
		x(0), y(0) {}

	Vector2(float x, float y) :
		x(x), y(y) {}

	Vector2(int x, int y) :
		x(static_cast<float>(x)), y(static_cast<float>(y)) {}
};

struct Vector3 {
	float x, y, z;

	Vector3() :
		x(0), y(0), z(0) {}

	Vector3(float x, float y, float z) :
		x(x), y(y), z(z) {}

	Vector3(int x, int y, int z) :
		x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {}

	inline float dot(const Vector3& o) const {
		return ((x * o.x) + (y * o.y) + (z * o.z));
	}

	inline Vector3 cross(const Vector3& o) const {
		return Vector3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
	}

	inline Vector3 abs() const {
		return Vector3(std::abs(x), std::abs(y), std::abs(z));
	}

	inline Vector3 normalize() const {
		float v = std::sqrt(x * x + y * y + z * z);
		return Vector3(x / v, y / v, z / v);
	}

	Vector3 operator-(const Vector3& o) const {
		return Vector3{ x - o.x, y - o.y, z - o.z };
	}

	Vector3 operator+(const Vector3& o) const {
		return Vector3{ x + o.x, y + o.y, z + o.z };
	}
};

struct Matrix3x3 {
	float R00, R01, R02;
	float R10, R11, R12;
	float R20, R21, R22;

	Matrix3x3() : 
		R00(0), R01(0), R02(0), R10(0), R11(0), R12(0), R20(0), R21(0), R22(0) {}

	inline Vector3 getRight() const {
		return Vector3{ R00, R10, R20 };
	}

	inline Vector3 getUp() const {
		return Vector3{ R01, R11, R21 };
	}

	inline Vector3 getBack() const {
		return Vector3{ R02, R12, R22 };
	}
};

struct Camera {
	Matrix3x3 rot;
	Vector3 right, up, back;
	Vector3 pos;
	Vector2 vps;
	float fov;

	Camera(const Matrix3x3& rot, const Vector3& pos, const Vector2& vps, float fov) :
		rot(rot), right(rot.getRight()), up(rot.getUp()), back(rot.getBack()), pos(pos), vps(vps), fov(fov) {}

	void update(const Matrix3x3& nrot, const Vector3& npos, const Vector2& nvps, float nfov) {
		rot = nrot;
		right = rot.getRight();
		up = rot.getUp();
		back = rot.getBack();
		pos = npos;
		fov = nfov;
	}
};