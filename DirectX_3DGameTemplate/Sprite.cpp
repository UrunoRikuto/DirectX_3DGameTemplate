/**********************************************************************************//*
    @file		| Sprite.cpp
    @brief		| スプライト描画
*//***********************************************************************************/
#include "Sprite.h"

//--- 静的メンバ変数の実体定義
Sprite::Data Sprite::m_data;
std::shared_ptr<VertexShader> Sprite::m_defVS;
std::shared_ptr<PixelShader> Sprite::m_defPS;

/*************************//*
@brief  | 初期化
*//*************************/
void Sprite::Init()
{
	struct Vertex
	{
		float pos[3];
		float uv[2];
	} vtx[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {1.0f, 1.0f}},
	};

	// メッシュ
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxSize = sizeof(Vertex);
	desc.vtxCount = _countof(vtx);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_data.mesh = std::make_shared<MeshBuffer>();
	m_data.mesh->Create(desc);

	// パラメーター
	m_data.param[0] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_data.param[1] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_data.param[2] = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	DirectX::XMStoreFloat4x4(&m_data.matrix[0], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_data.matrix[1], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_data.matrix[2], DirectX::XMMatrixIdentity());

	// シェーダー
	m_defVS = std::make_shared<VertexShader>();
    HRESULT hr = m_defVS->Load("Assets/Shader/VS_Sprite.cso");
    if (FAILED(hr)) MessageBox(NULL, "LoadFailed:VS_Sprite", "Error:Sprite.cpp", MB_OK);
	m_data.vs = m_defVS.get();
	m_defPS = std::make_shared <PixelShader>();
	hr = m_defPS->Load("Assets/Shader/PS_Sprite.cso");
    if (FAILED(hr)) MessageBox(NULL, "LoadFailed:PS_Sprite", "Error:Sprite.cpp", MB_OK);
	m_data.ps = m_defPS.get();
}

/*************************//*
@brief  | 終了
*//*************************/
void Sprite::Uninit()
{

}

/*************************//*
@brief  | 描画
*//*************************/
void Sprite::Draw()
{
	m_data.vs->WriteBuffer(0, m_data.matrix);
	m_data.vs->WriteBuffer(1, m_data.param);
	m_data.vs->Bind();
	m_data.ps->SetTexture(0, m_data.texture);
	m_data.ps->Bind();
	m_data.mesh->Draw();
}

/*************************//*
@brief      | オフセット設定
@param[in]  | offset：オフセット値
*//*************************/
void Sprite::SetOffset(DirectX::XMFLOAT2 offset)
{
	m_data.param[0].x = offset.x;
	m_data.param[0].y = offset.y;
}

/*************************//*
@brief      | サイズ設定
@param[in]  | size：サイズ値
*//*************************/
void Sprite::SetSize(DirectX::XMFLOAT2 size)
{
	m_data.param[0].z = size.x;
	m_data.param[0].w = size.y;
}

/*************************//*
@brief      | UV座標設定
@param[in]  | pos：UV座標
*//*************************/
void Sprite::SetUVPos(DirectX::XMFLOAT2 pos)
{
	m_data.param[1].x = pos.x;
	m_data.param[1].y = pos.y;
}

/*************************//*
@brief      | UVスケール設定
@param[in]  | scale：UVスケール
*//*************************/
void Sprite::SetUVScale(DirectX::XMFLOAT2 scale)
{
	m_data.param[1].z = scale.x;
	m_data.param[1].w = scale.y;
}

/*************************//*
@brief      | カラー設定
@param[in]  | color：カラー値
*//*************************/
void Sprite::SetColor(DirectX::XMFLOAT4 color)
{
	m_data.param[2] = color;
}

/*************************//*
@brief      | テクスチャ設定
@param[in]  | tex：テクスチャポインタ
*//*************************/
void Sprite::SetTexture(Texture* tex)
{
	m_data.texture = tex;
}

/*************************//*
@brief      | ワールド行列設定
@param[in]  | world：ワールド行列
*//*************************/
void Sprite::SetWorld(DirectX::XMFLOAT4X4 world)
{
	m_data.matrix[0] = world;
}

/*************************//*
@brief      | ビュー行列設定
@param[in]  | view：ビュー行列
*//*************************/
void Sprite::SetView(DirectX::XMFLOAT4X4 view)
{
	m_data.matrix[1] = view;
}

/*************************//*
@brief      | プロジェクション行列設定
@param[in]  | proj：プロジェクション行列
*//*************************/
void Sprite::SetProjection(DirectX::XMFLOAT4X4 proj)
{
	m_data.matrix[2] = proj;
}

/*************************//*
@brief      | 頂点シェーダー設定
@param[in]  | vs：頂点シェーダーポインタ
*//*************************/
void Sprite::SetVertexShader(Shader* vs)
{
	if (vs && typeid(VertexShader) == typeid(*vs))
		m_data.vs = vs;
	else
		m_data.vs = m_defVS.get();
}

/*************************//*
@brief      | ピクセルシェーダー設定
@param[in]  | ps：ピクセルシェーダーポインタ
*//*************************/
void Sprite::SetPixelShader(Shader* ps)
{
	if (ps && typeid(PixelShader) == typeid(*ps))
		m_data.ps = ps;
	else
		m_data.ps = m_defPS.get();
}
