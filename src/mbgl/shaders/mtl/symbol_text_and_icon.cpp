#include <mbgl/shaders/mtl/symbol_text_and_icon.hpp>

namespace mbgl {
namespace shaders {

const std::array<AttributeInfo, 9>
    ShaderSource<BuiltIn::SymbolTextAndIconShader, gfx::Backend::Type::Metal>::attributes = {
        // always attributes
        AttributeInfo{0, gfx::AttributeDataType::Short4, 1, "a_pos_offset"},
        AttributeInfo{1, gfx::AttributeDataType::UShort4, 1, "a_data"},
        AttributeInfo{2, gfx::AttributeDataType::Float3, 1, "a_projected_pos"},
        AttributeInfo{3, gfx::AttributeDataType::Float, 1, "a_fade_opacity"},

        // sometimes uniforms
        AttributeInfo{4, gfx::AttributeDataType::Float4, 1, "a_fill_color"},
        AttributeInfo{5, gfx::AttributeDataType::Float4, 1, "a_halo_color"},
        AttributeInfo{6, gfx::AttributeDataType::Float, 1, "a_opacity"},
        AttributeInfo{7, gfx::AttributeDataType::Float, 1, "a_halo_width"},
        AttributeInfo{8, gfx::AttributeDataType::Float, 1, "a_halo_blur"},
};
const std::array<UniformBlockInfo, 5>
    ShaderSource<BuiltIn::SymbolTextAndIconShader, gfx::Backend::Type::Metal>::uniforms = {
        UniformBlockInfo{9, true, true, sizeof(SymbolDrawableUBO), "SymbolDrawableUBO"},
        UniformBlockInfo{10, true, true, sizeof(SymbolDynamicUBO), "SymbolDynamicUBO"},
        UniformBlockInfo{11, true, true, sizeof(SymbolDrawablePaintUBO), "SymbolDrawablePaintUBO"},
        UniformBlockInfo{12, true, true, sizeof(SymbolDrawableTilePropsUBO), "SymbolDrawableTilePropsUBO"},
        UniformBlockInfo{13, true, false, sizeof(SymbolDrawableInterpolateUBO), "SymbolDrawableInterpolateUBO"},
};
const std::array<TextureInfo, 2> ShaderSource<BuiltIn::SymbolTextAndIconShader, gfx::Backend::Type::Metal>::textures = {
    TextureInfo{0, "u_texture"},
    TextureInfo{1, "u_texture_icon"},
};

} // namespace shaders
} // namespace mbgl
