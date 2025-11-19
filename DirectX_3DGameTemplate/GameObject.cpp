/**************************************************//*
    @file	| GameObject.cpp
    @brief	| ゲームオブジェクト基底クラス
*//**************************************************/
#include "GameObject.h"
#include "imgui.h"
#include "Oparation.h"

/****************************************//*
	@brief　	| コンストラクタ
*//****************************************/
CGameObject::CGameObject()
    : m_bDestroy(false)
    , m_eTag(Tag::None)
    , m_tID{ "Object", 0 }
{
    // 汎用パラメータの初期化
    m_tParam.m_f3Pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_tParam.m_f3Size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    m_tParam.m_f3Rotate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_tParam.m_f4Color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_tParam.m_f2UVPos = DirectX::XMFLOAT2(0.0f, 0.0f);
    m_tParam.m_f2UVSize = DirectX::XMFLOAT2(1.0f, 1.0f);
    m_f3OldPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

/****************************************//*
    @brief　	| デストラクタ
*//****************************************/
CGameObject::~CGameObject()
{

}

/****************************************//*
    @brief　	| 初期化処理
*//****************************************/
void CGameObject::Init()
{

}

/****************************************//*
    @brief　	| 終了処理
*//****************************************/
void CGameObject::Uninit()
{
	// 紐付けている全てのコンポーネントの終了処理
	for (auto comp : m_pComponent_List)
	{
        if (!comp) continue;
		comp->Uninit();
		delete comp;
	}
	m_pComponent_List.clear();
}

/****************************************//*
    @brief　	| 更新処理
*//****************************************/
void CGameObject::Update()
{
	// 紐付けている全てのコンポーネントの更新処理
	for (auto comp : m_pComponent_List)
	{
        if (!comp) continue;
		comp->Update();
	}
}

/****************************************//*
    @brief　	| 描画処理
*//****************************************/
void CGameObject::Draw()
{
	// 紐付けている全てのコンポーネントの描画処理
    for (auto comp : m_pComponent_List)
	{
        if (!comp) continue;
        // 描画用コンポーネントを使用する場合、汎用パラメータをコンポーネントに渡す
		if (dynamic_cast<CRendererComponent*>(comp))dynamic_cast<CRendererComponent*>(comp)->SetRendererParam(m_tParam);
        // 当たり判定描画はSceneで行う
        if (dynamic_cast<CCollisionBase*>(comp)) continue;
		comp->Draw();
	}	
}

/****************************************//*
    @brief　	| 他のオブジェクトと衝突した時の処理
    @param      | other：衝突先のオブジェクト
    @param      | thisTag：衝突したオブジェクトのコリジョン識別用タグ
*//****************************************/
void CGameObject::OnColliderHit(CCollisionBase* other, std::string thisTag)
{

}

/****************************************//*
    @brief　	| オブジェクトが破棄された時の処理
*//****************************************/
void CGameObject::OnDestroy()
{

}

/****************************************//*
    @brief　	| オブジェクトを破棄する
*//****************************************/
void CGameObject::Destroy()
{
	m_bDestroy = true;
}

/****************************************//*
    @brief　	| オブジェクトが破棄予定かどうかを取得
    @return     | true:破棄予定 false:破棄されていない
*//****************************************/
bool CGameObject::IsDestroy()
{
	return m_bDestroy;
}

/****************************************//*
    @brief　	| オブジェクトの前方向ベクトルの取得
    @return     | (DirectX::XMFLOAT3)前方向単位ベクトル
*//****************************************/
DirectX::XMFLOAT3 CGameObject::GetForward()
{
    DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

    DirectX::XMFLOAT3 f3ForWard;
    DirectX::XMStoreFloat3(&f3ForWard, mRotate.r[2]);

    return f3ForWard;
}

/****************************************//*
    @brief　	| オブジェクトの右方向ベクトルの取得
    @return     | (DirectX::XMFLOAT3)右方向単位ベクトル
*//****************************************/
DirectX::XMFLOAT3 CGameObject::GetRight()
{
    DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

    DirectX::XMFLOAT3 f3Right;
    DirectX::XMStoreFloat3(&f3Right, mRotate.r[0]);

    return f3Right;
}

/****************************************//*
    @brief　	| オブジェクトの上方向ベクトルの取得
    @return     | (DirectX::XMFLOAT3)上方向単位ベクトル
*//****************************************/
DirectX::XMFLOAT3 CGameObject::GetUp()
{
    DirectX::XMMATRIX mRotate = DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z);

    DirectX::XMFLOAT3 f3Up;
    DirectX::XMStoreFloat3(&f3Up, mRotate.r[1]);

    return f3Up;
}

/****************************************//*
    @brief　	| ワールド行列の取得
    @return     | (DirectX::XMFLOAT4X4*)ワールド行列
*//****************************************/
DirectX::XMFLOAT4X4* CGameObject::GetWorld()
{
    DirectX::XMFLOAT4X4 world;

    DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixScaling(m_tParam.m_f3Size.x, m_tParam.m_f3Size.y, m_tParam.m_f3Size.z) *
        DirectX::XMMatrixRotationRollPitchYaw(m_tParam.m_f3Rotate.x, m_tParam.m_f3Rotate.y, m_tParam.m_f3Rotate.z) *
        DirectX::XMMatrixTranslation(m_tParam.m_f3Pos.x, m_tParam.m_f3Pos.y, m_tParam.m_f3Pos.z));

    return &world;
}

/****************************************//*
    @brief　	| オブジェクトを指定位置まで移動させる
    @param      | initPos：移動開始位置
    @param      | targetPos：移動目標位置
    @param      | time：経過時間
    @param      | duration：移動にかかる時間
    @param      | ease：イージングの種類
*//****************************************/
void CGameObject::MoveTo(DirectX::XMFLOAT3 initPos, DirectX::XMFLOAT3 targetPos, float time, float duration, int ease)
{
    if (time >= duration)
    {
        time = duration;
    }

    m_tParam.m_f3Pos = initPos + (targetPos - initPos) * (time / duration);
}

/****************************************//*
    @brief　	| オブジェクトを指定位置まで移動させる
    @param      | initPos：移動開始位置
    @param      | targetPos：移動目標位置
    @param      | moveObjectPos：移動させるオブジェクトの位置
    @param      | time：経過時間
    @param      | duration：移動にかかる時間
    @param      | ease：イージングの種類
*//****************************************/
void CGameObject::MoveTo(DirectX::XMFLOAT3 initPos, DirectX::XMFLOAT3 targetPos, DirectX::XMFLOAT3* moveObjectPos, float time, float duration, int ease)
{
    if (time >= duration)
    {
        time = duration;
    }

    *moveObjectPos = initPos + (targetPos - initPos) * (time / duration);
}
