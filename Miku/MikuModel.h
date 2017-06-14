#pragma once

#include <string>
#include <vector>

#include "InputLayout.h"
#include "GpuBuffer.h"
#include "FileUtility.h"
#include "CommandContext.h"
#include "ConstantBuffer.h"
#include "Vmd.h"
#include "Pmd.h"
#include "KeyFrameAnimation.h"
#include "VectorMath.h"

#pragma comment(lib, "Miku.lib")

namespace Graphics
{
	using namespace Math;

	__declspec(align(16)) struct PSConstants
	{
		XMFLOAT4 Diffuse;
		XMFLOAT3 Specular;
		float SpecularPower;
		XMFLOAT3 Ambient;
	};

	struct Mesh 
	{
		PSConstants psConstants;
		uint32_t NumTexture;
		D3D11_SRV_HANDLE Texture[2];
		int32_t IndexOffset;
		uint32_t IndexCount;
	};

	struct SubmeshGeometry
	{
		uint32_t IndexCount;
		int32_t IndexOffset;
		int32_t VertexOffset;
	};

	struct Bone
	{
		std::wstring Name; 
		Vector3 Scale;
		Vector3 LocalPosision;
		Quaternion Rotation;
		Matrix4 mtxPose;
	};

	class MikuModel
	{
	public:
		std::vector<InputDesc> m_InputDesc;
		VertexBuffer m_VertexBuffer;
		IndexBuffer m_IndexBuffer;
		std::vector<Mesh> m_Mesh;
		std::vector<Bone> m_Bones;
		std::vector<Animation::MeshBone> m_MeshBone;
		std::vector<Matrix4> m_LocalPose;
		std::vector<Matrix4> m_Pose;
		std::vector<Matrix4> m_InitPose;
		std::vector<Matrix4> m_Sub;
		std::vector<int32_t> m_BoneParent;
		std::vector<std::vector<int32_t>> m_BoneChild;
		std::vector<Pmd::IK> m_IKs;
		std::vector<Pmd::Face> m_Skins;

		std::unique_ptr<Vmd::VmdMotion> m_Motion;
		std::map<std::wstring, uint16_t> m_BoneIndex;

		ConstantBuffer<PSConstants> m_MatConstants;

		MikuModel( bool bRightHand = true );
		void LoadModel( const std::wstring& model );
		void LoadMotion( const std::wstring& model );
		void LoadBone();
		void Clear();
		void Draw( GraphicsContext& gfxContext );
		void DrawBone( GraphicsContext& gfxContext );
		void Update( float dt );
		void UpdateBone( float dt );
		void UpdateChildPose( int32_t idx );
		void SetBoneNum( size_t numBones );

	private:
		void LoadPmd( const std::wstring& model, bool bRightHand );
		void LoadVmd( const std::wstring& vmd, bool bRightHand );

		bool m_bRightHand;
		std::vector<XMMATRIX> m_BoneAttribute;
		std::vector<XMMATRIX> m_ToRootTransforms;

		ConstantBuffer<XMMATRIX> m_BoneConstants;
		SubmeshGeometry m_BoneMesh;
		std::vector<InputDesc> m_BoneInputDesc;
		VertexBuffer m_BoneVertexBuffer;
		IndexBuffer m_BoneIndexBuffer;
		GraphicsPSO m_BonePSO;
	};
}