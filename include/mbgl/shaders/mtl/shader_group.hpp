#pragma once

#include <mbgl/gfx/shader_group.hpp>
#include <mbgl/programs/program_parameters.hpp>
#include <mbgl/shaders/mtl/background.hpp>
#include <mbgl/shaders/mtl/shader_program.hpp>
#include <mbgl/shaders/shader_source.hpp>
#include <mbgl/util/hash.hpp>
#include <mbgl/util/containers.hpp>

#include <numeric>
#include <string>
#include <type_traits>

namespace mbgl {
namespace mtl {

class ShaderGroupBase : public gfx::ShaderGroup {
public:
    using StringIDSet = mbgl::unordered_set<StringIdentity>;

protected:
    ShaderGroupBase(const ProgramParameters& parameters_)
        : programParameters(parameters_) {}

    using DefinesMap = mbgl::unordered_map<std::string, std::string>;
    void addAdditionalDefines(const StringIDSet& propertiesAsUniforms, DefinesMap& additionalDefines) {
        additionalDefines.reserve(propertiesAsUniforms.size() + 1);
        if (programParameters.getOverdrawInspectorEnabled()) {
            additionalDefines.insert(std::make_pair(overdrawName, std::string()));
        }
        for (const auto nameID : propertiesAsUniforms) {
            // We expect the names to be prefixed by "a_", but we need just the base here.
            const auto name = stringIndexer().get(nameID);
            const auto* base = (name[0] == 'a' && name[1] == '_') ? &name[2] : name.data();
            additionalDefines.insert(std::make_pair(std::string(uniformPrefix) + base, std::string()));
        }
    }

    ProgramParameters programParameters;

private:
    static constexpr auto uniformPrefix = "HAS_UNIFORM_u_";
    static constexpr auto overdrawName = "OVERDRAW_INSPECTOR";
};

template <shaders::BuiltIn ShaderID>
class ShaderGroup final : public ShaderGroupBase {
public:
    ShaderGroup(const ProgramParameters& programParameters_)
        : ShaderGroupBase(programParameters_) {}
    ~ShaderGroup() noexcept override = default;

    gfx::ShaderPtr getOrCreateShader(gfx::Context& gfxContext,
                                     const mbgl::unordered_set<StringIdentity>& propertiesAsUniforms,
                                     std::string_view /*firstAttribName*/) override {
        using ShaderSource = shaders::ShaderSource<ShaderID, gfx::Backend::Type::Metal>;
        constexpr auto& name = ShaderSource::name;
        constexpr auto& source = ShaderSource::source;
        constexpr auto& vertMain = ShaderSource::vertexMainFunction;
        constexpr auto& fragMain = ShaderSource::fragmentMainFunction;

        const std::string shaderName = getShaderName(name, propertyHash(propertiesAsUniforms));

        auto shader = get<mtl::ShaderProgram>(shaderName);
        if (!shader) {
            DefinesMap additionalDefines;
            addAdditionalDefines(propertiesAsUniforms, additionalDefines);

            auto& context = static_cast<Context&>(gfxContext);
            const auto shaderSource = std::string(shaders::prelude) + source;
            shader = context.createProgram(
                shaderName, shaderSource, vertMain, fragMain, programParameters, additionalDefines);
            assert(shader);
            if (!shader || !registerShader(shader, shaderName)) {
                assert(false);
                throw std::runtime_error("Failed to register " + shaderName + " with shader group!");
            }

            using ShaderClass = shaders::ShaderSource<ShaderID, gfx::Backend::Type::Metal>;
            for (const auto& attrib : ShaderClass::attributes) {
                if (!propertiesAsUniforms.count(attrib.nameID)) {
                    shader->initAttribute(attrib);
                }
            }
            for (const auto& uniform : ShaderClass::uniforms) {
                shader->initUniformBlock(uniform);
            }
            for (const auto& texture : ShaderClass::textures) {
                shader->initTexture(texture);
            }
        }
        return shader;
    }
};

} // namespace mtl
} // namespace mbgl
