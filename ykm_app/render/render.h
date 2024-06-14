/*

base render hardware interface


phycics device
virtual device

command buffer

resoruces:
    vertex_layout
    indices
    vertex
    constant
    texture
    render_texture
    vertex_shader
    pixel_shader
    compute_shader
    view_port
    render_attribute


abstract:
    Graphics

        Texture
        RenderTexture
        ComputeShader
        EnvConstants            like camera matrix canvas matrix mouse times
        Mesh
        ObjectConstant          transform matrix, mvp, m, v, p, inverse_mvp, inverse_m, cam_pos...
        ShaderPass              control by env
        Shader
        Material_attribute      render queue, blend mode, cull mode....
        Material
        MaterialConstants       color, texture....(user defined)
        MaterialOWConstants

        Set()
        Bind()
        Draw()

*/

#ifndef YKM_RENDER_H
#define YKM_RENDER_H
#include <cstdint>
namespace ykm::render
{

using UUID = uint64_t;

struct UUID_s
{
    UUID_s(UUID uuid) : type(uuid >> 48), bucket((uuid >> 32) & 0xffff){};

    uint16_t type;
    uint16_t bucket;
    uint16_t valid;
    uint16_t id;
};

enum class RW_State
{
    CPU_Read,
    CPU_Write,
    GPU_Read,
    GPU_Write,
};

enum class PixelFormat : uint16_t
{
    R8,
    G8,
    B8,
    A8,
};

struct TextureDesc
{
    uint16_t width;
    uint16_t height;
    PixelFormat pixel_format;
};

struct RenderTexture
{
    TextureDesc desc;
    UUID uuid;
};

struct Texture
{
    TextureDesc desc;
    UUID uuid;
};

struct Mesh
{
    UUID layout;
    UUID indices;
    UUID vertices;
};

struct Shader
{
    UUID pixel_shader;
    UUID vertex_shader;
};

struct Material
{
    UUID vertex_shader;
    UUID pixel_shader;
    UUID constants;
    UUID attribute;
};

using result = int32_t;

template <typename T>
struct create
{
    result code;
    T t;
};

struct Graphics
{
    void* context;
    void* device;
    const char* LastError();

    result Bind(Material material);
    result Bind(Mesh mesh);
    result Bind(Texture texture, uint32_t id);
    result Bind(RenderTexture target);
    result Draw();
};

} // namespace ykm::render
#endif
