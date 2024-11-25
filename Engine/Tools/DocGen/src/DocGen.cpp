#include "DocGen.hpp"

int main(int argc, char* argv[])
{
    std::vector<std::string> args(argv, argv + argc);

    if (args.size() != 2 && args.size() != 3) {
        std::cerr << "Usage: DocGen <entities.json>" << std::endl;
        return 1;
    }

    if (args[1].find(".json") == std::string::npos) {
        std::cerr << "Input file must be a json file" << std::endl;
        return 1;
    }

    if (args.size() == 3) {
        std::string output = args[2];
        if (output.find(".md") == std::string::npos) {
            std::cerr << "Output file must be a markdown file" << std::endl;
            return 1;
        }
    }

    ComponentRegistry registry;
    registry.registerComponent("Position", {ComponentFunction("getPosition", {}, {"x", "y", "z"}),
                                            ComponentFunction("setPosition", {"x", "y", "z"})});
    registry.registerComponent("Rotation", {ComponentFunction("getRotation", {}, {"angle"}),
                                            ComponentFunction("setRotation", {"angle"})});
    registry.registerComponent("Scale", {ComponentFunction("getScale", {}, {"x", "y"}),
                                         ComponentFunction("setScale", {"x", "y"})});
    registry.registerComponent(
        "Sprite",
        {ComponentFunction("getSprite", {}, {"textureID", "width", "height", "originX", "originY"}),
         ComponentFunction("setSprite", {"textureID", "width", "height", "originX", "originY"})});
    registry.registerComponent("Input", {ComponentFunction("isInputActive", {"input"}, {"bool"})});

    EntityAnalyzer analyzer(registry);
    auto entityFunctions = analyzer.analyzeEntities(args[1]);

    DocumentationGenerator docGen;
    docGen.generate(entityFunctions, args.size() == 3 ? args[2] : "");

    return 0;
}
