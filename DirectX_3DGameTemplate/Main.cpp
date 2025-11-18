/**********************************************************************************//*
    @file		|Main.cpp
    @brief		|メイン処理
*//***********************************************************************************/
#include "Main.h"
#include "DirectX.h"

#include "Geometory.h"
#include "Sprite.h"

#include "Input.h"

/*************************//*
@brief		|初期化
@param[in]	|hWnd	ウィンドウハンドル
@param[in] 	|width 画面幅
@param[in] 	|height 画面高さ
*//*************************/
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// DirectX初期化
	hr = InitDirectX(hWnd, width, height, false);
	// 初期化の例
	if (FAILED(hr)) { return hr; }

    // ランダムの初期設定
    srand(timeGetTime());

	Geometory::Init();
	Sprite::Init();

	InitInput();

	return hr;
}

/*************************//*
@brief 	| 終了
*//*************************/
void Uninit()
{
	UninitInput();

	Sprite::Uninit();
	Geometory::Uninit();

	UninitDirectX();
}

/*************************//*
@brief 	| 更新
*//*************************/
void Update()
{

}

/*************************//*
@brief 	| 描画
*//*************************/
void Draw()
{
	BeginDrawDirectX();

	EndDrawDirectX();
}
