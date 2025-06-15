#!/usr/bin/zsh
set -euo pipefail

APP=Blueprint
VERSION=1.0.0

log() {
  echo -e "\033[1;34m[INFO]\033[0m $1"
}

error_exit() {
  echo -e "\033[1;31m[ERROR]\033[0m $1"
  exit 1
}

trap 'error_exit "打包失败，请检查上方输出."' ERR

log "清理旧目录..."
rm -rf build AppDir

log "创建构建目录..."
mkdir -p build && cd build

log "配置 CMake 项目 (使用 Ninja)..."
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../AppDir/usr || error_exit "CMake 配置失败"

log "编译项目..."
ninja || error_exit "编译失败"

log "安装到 AppDir..."
ninja install || error_exit "安装失败"

cd ..

log "准备 AppDir 元数据..."
mkdir -p AppDir/usr/share/applications
mkdir -p AppDir/usr/share/icons/hicolor/256x256/apps

cp demo.desktop AppDir/usr/share/applications/ || error_exit "找不到 demo.desktop"
cp desktop/blueprint.png AppDir/usr/share/icons/hicolor/256x256/apps/${APP}.png || error_exit "找不到 blueprint.png"

export NO_STRIP=1

log "生成 AppImage..."
~/linuxdeploy-x86_64.AppImage --appdir AppDir \
  --executable AppDir/usr/bin/${APP} \
  --output appimage

log "AppImage 打包成功：${APP}-${VERSION}-x86_64.AppImage"