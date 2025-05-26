module;
#include <algorithm>
#include <cmath>
module EventHelpers;

namespace Blueprint::EventHelpers {
    // 滚轮事件处理函数
    void wheelEvent(double zoomStep,
                    double blurStep,
                    int rollerWheel,
                    double& targetZoomLevel,
                    double& targetBlurLevel,
                    double& zoomLevel,
                    double& blurLevel,
                    double& velocity) noexcept {
        // 定义缩放和模糊的边界值
        constexpr double kMaxZoom = 3.0;          // 最大缩放级别
        constexpr double kMinZoom = 0.5;          // 最小缩放级别
        constexpr double kMaxBlur = 15.0;         // 最大模糊级别
        constexpr double kMinBlur = 0.0;          // 最小模糊级别

        // 定义初始速度（正值为放大，负值为缩小）
        constexpr double kInitialVelocity = 0.45; // 初始速度大小

        constexpr double kZoomOutStep = 0.3;      // 向下滚动时的缩小步长

        // 判断滚轮方向并设置目标值和速度
        if (rollerWheel > 0) {  // 向上滚动 -> 放大
            targetZoomLevel = std::min(zoomLevel + zoomStep, kMaxZoom);  // 目标缩放值不超过最大值
            targetBlurLevel = std::min(blurLevel + blurStep, kMaxBlur);  // 目标模糊值不超过最大值
            velocity = kInitialVelocity;  // 设置正向初始速度
        } else {  // 向下滚动 -> 缩小
            targetZoomLevel = std::max(zoomLevel - kZoomOutStep, kMinZoom);

            targetBlurLevel = std::max(blurLevel - blurStep, kMinBlur);  // 目标模糊值不低于最小值
            velocity = -kInitialVelocity;  // 设置负向初始速度
        }
    }

    // 平滑缩放函数
    void smoothZoom(bool& isDashing,
                    double& velocity,
                    double& targetZoomLevel,
                    double& targetBlurLevel,
                    double& zoomLevel,
                    double& blurLevel) noexcept {
        // 定义缓动系数和阈值
        constexpr double kDampingFactor = 0.62;     // 速度衰减系数
        constexpr double kVelocityThreshold = 0.01; // 速度阈值（接近0时停止动画）
        constexpr double kLerpFactor = 0.1;         // 线性插值系数（0~1之间，越小越平滑）
        constexpr double kMinZoomLevel = 0.1;       // 最小允许缩放值（防止过小）
        constexpr double kMaxZoomLevel = 5.0;       // 最大允许缩放值（防止过大）

        // 检查是否正在执行缩放动画
        if (isDashing) {  // 如果正在动画中
            velocity *= kDampingFactor;  // 速度按系数衰减

            // 如果速度足够小，停止动画
            if (std::abs(velocity) < kVelocityThreshold) {
                isDashing = false;      // 停止动画标志
                targetBlurLevel = 0.0;  // 动画结束时模糊值归零
            }
        }

        // 平滑调整缩放级别（带速度修正）
        zoomLevel += (targetZoomLevel - zoomLevel) * kLerpFactor + velocity;
        zoomLevel = std::clamp(zoomLevel, kMinZoomLevel, kMaxZoomLevel);  // 限制在合理范围内

        // 检查缩放值是否有效（防止NaN或Inf）
        if (zoomLevel <= kMinZoomLevel || !std::isfinite(zoomLevel)) {
            zoomLevel = 1.0;      // 重置为默认值
            velocity = 0.0;       // 停止速度
            isDashing = false;    // 停止动画
        }

        // 平滑调整模糊级别
        blurLevel += (targetBlurLevel - blurLevel) * kLerpFactor;
    }
}