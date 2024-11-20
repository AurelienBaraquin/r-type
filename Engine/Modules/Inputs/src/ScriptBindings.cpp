#include "Inputs.hpp"

void Inputs::registerScriptBindings(ScriptSystem& ScriptSystem, Registry& registry)
{
    ScriptSystem.registerBinding(
        "Input",
        [&registry = registry](sol::state& luaState)
        {
            luaState["getInput"] = [&registry, &luaState](Entity entity)
            {
                auto* input = registry.getComponent<Components::Input>(entity);
                if (!input) throw std::runtime_error("Input component not found");
                return luaState.create_table_with("inputConfigID", input->inputConfigID);
            };

            luaState["setInput"] = [&registry, &luaState](Entity entity, sol::table data)
            {
                auto* input = registry.getComponent<Components::Input>(entity);
                if (!input) throw std::runtime_error("Input component not found");
                if (input)
                {
                    input->inputConfigID = data["inputConfigID"].get_or(input->inputConfigID);
                }
            };
        });
}
