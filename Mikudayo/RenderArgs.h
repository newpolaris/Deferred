#pragma once

struct D3D11_VIEWPORT;
namespace Math
{
    class Matrix4;
    class BaseCamera;
};

class RenderArgs
{
public:

    Math::Matrix4& m_ViewMatrix;
    Math::Matrix4& m_ProjMatrix;
    D3D11_VIEWPORT& m_MainViewport;
    const Math::BaseCamera& m_Camera;
};
