#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

class ComponentFunction {
public:
    ComponentFunction(const std::string& name,
                      const std::vector<std::string>& params = {},
                      const std::vector<std::string>& returns = {})
        : name(name), parameters(params), returns(returns) {}

    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::string> returns;
};

class ComponentRegistry {
public:
    void registerComponent(const std::string& componentName, const std::vector<ComponentFunction>& functions) {
        componentFunctions[componentName] = functions;
    }

    const std::vector<ComponentFunction>& getFunctions(const std::string& componentName) const {
        if (componentFunctions.find(componentName) != componentFunctions.end()) {
            return componentFunctions.at(componentName);
        }
        static const std::vector<ComponentFunction> empty;
        return empty;
    }

private:
    std::map<std::string, std::vector<ComponentFunction>> componentFunctions;
};

class EntityAnalyzer {
public:
    EntityAnalyzer(const ComponentRegistry& registry) : registry(registry) {}

    std::map<std::string, std::vector<ComponentFunction>> analyzeEntities(const std::string& jsonFilePath) {
        std::ifstream file(jsonFilePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open JSON file: " + jsonFilePath);
        }

        nlohmann::json data;
        file >> data;

        std::map<std::string, std::vector<ComponentFunction>> entityFunctions;

        for (const auto& entity : data["entities"]) {
            std::vector<ComponentFunction> functions;

            std::string entityName = entity.value("_name_", "Unnamed Entity");

            for (const auto& component : entity["components"].items()) {
                const std::string& componentName = component.key();

                const auto& componentFunctions = registry.getFunctions(componentName);
                functions.insert(functions.end(), componentFunctions.begin(), componentFunctions.end());
            }

            entityFunctions[entityName] = functions;
        }

        return entityFunctions;
    }

private:
    const ComponentRegistry& registry;
};

class DocumentationGenerator {
public:
    void generate(const std::map<std::string, std::vector<ComponentFunction>>& entityFunctions,
                  const std::string& outputPath) {
        std::ostream* out;
        std::ofstream file;

        if (outputPath.empty()) {
            out = &std::cout;
        } else {
            file.open(outputPath);
            out = &file;
        }

        *out << "# Lua Functions and Variables by Entity\n\n";
        *out << "> **Note:** EVERY function is called with the entity \"e\" as the first parameter.\n\n";

        for (const auto& [entity, functions] : entityFunctions) {
            *out << "## Entity: " << entity << "\n";

            for (const auto& function : functions) {
                *out << "- `" << function.name << "`\n";

                if (!function.parameters.empty()) {
                    *out << "  - **Parameters:** ";
                    for (const auto& param : function.parameters) {
                        *out << "`" << param << "` ";
                    }
                    *out << "\n";
                }

                if (!function.returns.empty()) {
                    *out << "  - **Returns:** ";
                    for (const auto& ret : function.returns) {
                        *out << "`" << ret << "` ";
                    }
                    *out << "\n";
                }
            }

            *out << "\n";
        }

        if (!outputPath.empty()) {
            std::cout << "Documentation generated at: " << outputPath << "\n";
        }
    }
};
