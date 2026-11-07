#pragma once
#include <optional>
#include <d2d1.h>
#include <dwmapi.h>
#include <dwrite.h>
#include <cmath>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dwmapi.lib")

#include "structs.h"

inline std::optional<D2D1_ELLIPSE> worldToScreen(const Camera& camera, const Vector2& screen, const Vector3& tpos, const Vector3& tsize) {
    Vector3 offset = tpos - camera.pos;
    float depth = -offset.dot(camera.back);

    if (depth <= 3.0f) return std::nullopt;

    float lx = offset.dot(camera.right);
    float ly = offset.dot(camera.up);

    float cx = camera.vps.x / 2.0f;
    float cy = camera.vps.y / 2.0f;

    float focal = cy / std::tan(camera.fov / 2.0f);

    float vx = cx + (lx * focal / depth);
    float vy = cy - (ly * focal / depth);

    float rpx = vx * screen.x / camera.vps.x;
    float rpy = vy * screen.y / camera.vps.y;

    float sX = screen.x / camera.vps.x;
    float sY = screen.y / camera.vps.y;

    float rsx = (focal * std::min(tsize.x, tsize.z) / 2 / depth) * sX;
    float rsy = (focal * tsize.y / 2 / depth) * sY;

    return D2D1::Ellipse(D2D1::Point2F(rpx, rpy), rsx, rsy);
}