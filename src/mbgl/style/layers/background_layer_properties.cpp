// clang-format off

// This file is generated. Edit scripts/generate-style-code.js, then run `make style-code`.

#include <mbgl/style/layers/background_layer_properties.hpp>

#include <mbgl/style/layers/background_layer_impl.hpp>

namespace mbgl {
namespace style {

BackgroundLayerProperties::BackgroundLayerProperties(
    Immutable<BackgroundLayer::Impl> impl_)
    : LayerProperties(std::move(impl_)) {}

BackgroundLayerProperties::BackgroundLayerProperties(
    Immutable<BackgroundLayer::Impl> impl_,
    CrossfadeParameters crossfade_,
    BackgroundPaintProperties::PossiblyEvaluated evaluated_)
  : LayerProperties(std::move(impl_)),
    crossfade(crossfade_),
    evaluated(std::move(evaluated_)) {}

BackgroundLayerProperties::~BackgroundLayerProperties() = default;

unsigned long BackgroundLayerProperties::constantsMask() const {
    return evaluated.constantsMask();
}

const BackgroundLayer::Impl& BackgroundLayerProperties::layerImpl() const noexcept {
    return static_cast<const BackgroundLayer::Impl&>(*baseImpl);
}

expression::Dependency BackgroundLayerProperties::getDependencies() const noexcept {
    return layerImpl().paint.getDependencies();
}

} // namespace style
} // namespace mbgl

// clang-format on
