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
    registry.registerComponent("Position", {ComponentFunction("getPosition", {}, {"x", "y", "z"}, "Get the position"),
                                            ComponentFunction("setPosition", {"x", "y", "z"}, {}, "Set the position")});
    registry.registerComponent("Rotation", {ComponentFunction("getRotation", {}, {"angle"}, "Get the rotation"),
                                            ComponentFunction("setRotation", {"angle"}, {}, "Set the rotation")});
    registry.registerComponent("Scale", {ComponentFunction("getScale", {}, {"x", "y"}, "Get the scale"),
                                         ComponentFunction("setScale", {"x", "y"}, {}, "Set the scale (if scale is 0, the standard scale of the texture is used)")});
    registry.registerComponent(
        "Sprite",
        {ComponentFunction("getSprite", {}, {"textureID", "width", "height", "originX", "originY"}, "Get the sprite"),
         ComponentFunction("setSprite", {"textureID", "width", "height", "originX", "originY"}, {}, "Set the sprite")});
    registry.registerComponent("Input", {ComponentFunction("isInputActive", {"input"}, {"bool"}, "Check if an input is active and return true if it is")});

    registry.registerComponent("Script", {});

    registry.registerComponent("Area2D", {});

    registry.registerComponent("Animation", {ComponentFunction("playAnimation", {"animationId"}, {}, "Play an animation"),
                                           ComponentFunction("stopAnimation", {}, {}, "Stop the current animation")});

    EntityAnalyzer analyzer(registry);
    auto entityFunctions = analyzer.analyzeEntities(args[1]);

    DocumentationGenerator docGen;
    docGen.generate(entityFunctions, args.size() == 3 ? args[2] : "");

    return 0;
}
