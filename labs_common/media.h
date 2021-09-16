#include <nlohmann/json.hpp>
#include <xtl/xbase64.hpp>

#include <string>

struct PngImage {
    std::string content;
};

nlohmann::json mime_bundle_repr(const PngImage& image)
{
    auto bundle = nlohmann::json::object();
    bundle["image/png"] = xtl::base64encode(image.content);
    return bundle;
}
