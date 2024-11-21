#include "Inputs.hpp"

void Inputs::registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry)
{
    ScriptSystem.registerBinding(
        "Input",
        [&registry = registry](sol::state& luaState)
        {
            luaState["getInputConfig"] = [&registry, &luaState](Entity entity)
            {
                auto* input = registry.getComponent<Components::Input>(entity);
                if (!input) throw std::runtime_error("Input component not found");
                return luaState.create_table_with("inputConfigID", input->inputConfigID);
            };

            luaState["setInputConfig"] = [&registry, &luaState](Entity entity, sol::table data)
            {
                auto* input = registry.getComponent<Components::Input>(entity);
                if (!input) throw std::runtime_error("Input component not found");
                if (input)
                {
                    input->inputConfigID = data["inputConfigID"].get_or(input->inputConfigID);
                }
            };
        });
    
    ScriptSystem.registerBinding(
        "isInputActive",
        [this](sol::state& luaState)
        {
            luaState["isInputActive"] = [this](const std::string& action)
            {
                return _InputSystem.isInputActive(action);
            };
        });
}
