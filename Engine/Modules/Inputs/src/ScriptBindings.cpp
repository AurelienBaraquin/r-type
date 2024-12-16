#include "Inputs.hpp"
#include "raylib.h"

void Inputs::registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry)
{
    ScriptSystem.registerBinding("Input", [&registry = registry](sol::state& luaState) {
        luaState["getInputConfig"] = [&registry, &luaState](Entity entity) {
            auto* input = registry.getComponent<Components::Input>(entity);
            if (!input) throw std::runtime_error("Input component not found");
            return luaState.create_table_with("inputConfigID", input->inputConfigID);
        };

        luaState["setInputConfig"] = [&registry, &luaState](Entity entity, sol::table data) {
            auto* input = registry.getComponent<Components::Input>(entity);
            if (!input) throw std::runtime_error("Input component not found");
            input->inputConfigID = data["inputConfigID"].get_or(input->inputConfigID);
        };
    });

    ScriptSystem.registerBinding(
        "isInputActive", [&registry = registry, this](sol::state& luaState) {
            luaState["isInputActive"] = [&registry, this](Entity entity, const std::string& action,
                                                          const sol::optional<bool>& allowHold) {
                auto* input = registry.getComponent<Components::Input>(entity);
                if (!input) throw std::runtime_error("Input component not found");
                return _InputSystem.isInputActive(input->inputConfigID, action,
                                                  allowHold.value_or(true));
            };
        });

    ScriptSystem.registerBinding("Mouse", [&registry = registry, this](sol::state& luaState) {
        luaState["getMousePosition"] = []() {
            Vector2 mousePosition = GetMousePosition();
            return sol::as_table(std::vector<float>{mousePosition.x, mousePosition.y});
        };

        luaState["isMouseButtonDown"] = [](int button) {
            return IsMouseButtonDown(button);
        };

        luaState["isMouseButtonPressed"] = [](int button) {
            return IsMouseButtonPressed(button);
        };

        luaState["isMouseButtonReleased"] = [](int button) {
            return IsMouseButtonReleased(button);
        };
    });

    ScriptSystem.registerBinding("Keyboard", [&registry = registry, this](sol::state& luaState) {
        luaState["isKeyDown"] = [](int key) {
            return IsKeyDown(key);
        };

        luaState["isKeyPressed"] = [](int key) {
            return IsKeyPressed(key);
        };

        luaState["isKeyReleased"] = [](int key) {
            return IsKeyReleased(key);
        };

        luaState["getKeyPressed"] = []() {
            return GetKeyPressed();
        };
    });

    ScriptSystem.registerBinding("Controller", [&registry = registry, this](sol::state& luaState) {
        luaState["isGamepadButtonDown"] = [](int gamepad, int button) {
            return IsGamepadButtonDown(gamepad, button);
        };

        luaState["isGamepadButtonPressed"] = [](int gamepad, int button) {
            return IsGamepadButtonPressed(gamepad, button);
        };

        luaState["isGamepadButtonReleased"] = [](int gamepad, int button) {
            return IsGamepadButtonReleased(gamepad, button);
        };

        luaState["getGamepadAxisMovement"] = [](int gamepad, int axis) {
            return GetGamepadAxisMovement(gamepad, axis);
        };
    });
}
