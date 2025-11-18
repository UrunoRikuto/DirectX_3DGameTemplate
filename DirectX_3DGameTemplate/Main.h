/**********************************************************************************//*
    @file		|Main.h
    @brief		|メイン処理
*//***********************************************************************************/
#pragma once

#include <Windows.h>
#include <string>

// @brief 初期化
// @param[in]	hWnd	ウィンドウハンドル
// @param[in] 	width 画面幅
// @param[in] 	height 画面高さ
HRESULT Init(HWND hWnd, UINT width, UINT height);

// @brief 終了
void Uninit();

// @brief 更新
void Update();

// @brief 描画
void Draw();

// @brief アプリケーション終了処理
void AppEnd();

// @brief 自分のウインドウハンドル取得
HWND GetMyWindow();

// @brief フレームレート取得
int GetFPS();

// @brief デバッグモードかどうか取得
bool IsDebugMode();
