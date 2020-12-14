#pragma once

#include "Structs.h"
#include "Camera.h"
#include "DDSTextureLoader.h"
#include <vector>
#include "OBJLoader.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11VertexShader*     _pVertexShader;
	ID3D11PixelShader*      _pPixelShader;
	ID3D11InputLayout*      _pVertexLayout;
	ID3D11Buffer*			_pConstantBuffer;
	ID3D11DepthStencilView* _depthStencilView;
	ID3D11Texture2D*		_depthStencilBuffer;
	ID3D11RasterizerState*	_wireFrame;
	ID3D11RasterizerState*	_solid;
	ConstantBuffer			_cb;
	ID3D11SamplerState*		_pSamplerLinear;

	Camera* camera;
	vector<IndexedMesh> _meshes;
	vector<IndexedTex> _textures;
	vector<IndexedMat> _materials;
	vector<WorldObject> _objects;

	XMFLOAT3 lightDirection;
	XMFLOAT4 diffuseLight;
	XMFLOAT4 ambientLight;
	XMFLOAT4 specularLight;
	float specularPower;
	XMFLOAT3 eyePosWorld;

	CameraMode cameraMode;
	bool isSolid;
	float walkSpeed;

	UINT _WindowHeight;
	UINT _WindowWidth;

private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT InitShadersAndInputLayout();
	HRESULT InitVertexBuffer();
	HRESULT InitIndexBuffer();
	void LoadObjectData();
	void PlayerTranslate(float dx, float dy, float dz);
	void PlayerRotate();

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	bool HandleKeyboard(MSG msg);
	void ConfineCursor();
	void FreeCursor();

	CameraMode GetCameraMode() { return cameraMode; }

	void Update();
	void Draw();

	int x;
	int y;
};