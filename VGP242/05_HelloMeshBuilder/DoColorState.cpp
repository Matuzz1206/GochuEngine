#include "DoColorState.h"

using namespace GochuEngine;
using namespace GochuEngine::Graphics;
using namespace GochuEngine::Input;

void DoColorState::Initialize()
{
    m_camera.SetPosition({ 0.0f, 1.0f, -5.0f });
    m_camera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    // 1 - Cube
    mMeshes.push_back(MeshBuilder::CreateCubePC(1.0f));

    // 2 - Box (Rectangle)
    mMeshes.push_back(MeshBuilder::CreateRectanglePC(2.0f, 1.0f, 1.5f));

    // 3 - Horizontal Plane
    mMeshes.push_back(MeshBuilder::CreatePlanePC(10, 10, 0.5f, true));

    // 4 - Vertical Plane
    mMeshes.push_back(MeshBuilder::CreatePlanePC(10, 10, 0.5f, false));

    // 5 - Cylinder
    mMeshes.push_back(MeshBuilder::CreateCylinderPC(30, 10));

    // 6 - Sphere
    mMeshes.push_back(MeshBuilder::CreateSpherePC(30, 20, 1.0f));

    m_meshBuffer.Initialize(mMeshes[mCurrentMesh]);

    std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTransform.fx";

    m_vertexShader.Initialize<VertexPC>(shaderPath);
    m_pixelShader.Initialize(shaderPath);

    m_transformBuffer.Initialize(sizeof(Math::Matrix4));
}

void DoColorState::Update(float deltaTime)
{
    InputSystem* input = InputSystem::Get();

    const float moveSpeed =
        input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;

    const float turnSpeed = 0.1f;

    if (input->IsKeyDown(KeyCode::W))
        m_camera.Walk(moveSpeed * deltaTime);
    else if (input->IsKeyDown(KeyCode::S))
        m_camera.Walk(-moveSpeed * deltaTime);

    if (input->IsKeyDown(KeyCode::D))
        m_camera.Strafe(moveSpeed * deltaTime);
    else if (input->IsKeyDown(KeyCode::A))
        m_camera.Strafe(-moveSpeed * deltaTime);

    if (input->IsKeyDown(KeyCode::Q))
        m_camera.Rise(moveSpeed * deltaTime);
    else if (input->IsKeyDown(KeyCode::E))
        m_camera.Rise(-moveSpeed * deltaTime);

    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        m_camera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
        m_camera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
    }

    // SPACE = Next Mesh
    if (input->IsKeyPressed(KeyCode::SPACE))
    {
        mCurrentMesh++;

        if (mCurrentMesh >= static_cast<int>(mMeshes.size()))
            mCurrentMesh = 0;

        m_meshBuffer.Terminate();
        m_meshBuffer.Initialize(mMeshes[mCurrentMesh]);
    }
}

void DoColorState::Render()
{
    m_vertexShader.Bind();
    m_pixelShader.Bind();

    m_transformBuffer.BindVS(0);

    Math::Matrix4 matWorld = Math::Matrix4::Identity;
    Math::Matrix4 matView = m_camera.GetViewMatrix();
    Math::Matrix4 matProj = m_camera.GetProjectionMatrix();

    Math::Matrix4 wvp =
        Math::Transpose(matWorld * matView * matProj);

    m_transformBuffer.Update(&wvp);

    m_meshBuffer.Render();
}

void DoColorState::Terminate()
{
    m_transformBuffer.Terminate();
    m_pixelShader.Terminate();
    m_vertexShader.Terminate();
    m_meshBuffer.Terminate();
}