#include "PixelShader.h"

PixelShader::PixelShader()
{
    m_ps = nullptr;
}

void PixelShader::release()
{
    if (m_ps)
        m_ps->Release();
    delete this;

}

PixelShader::~PixelShader()
{
}

ID3D11PixelShader* PixelShader::getShader()
{
    return this->m_ps;
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
    HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps);
    if (FAILED(hr)) {
   
        return false;
    }
    return true;
}