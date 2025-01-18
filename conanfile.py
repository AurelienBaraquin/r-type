from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CactusEngine(ConanFile):
    name = "CactusEngine"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = ["CMakeDeps", "CMakeToolchain"]
    default_options = {"*:shared": False}

    def requirements(self):
        self.requires("gtest/1.15.0")
        self.requires("raylib/5.5")
        self.requires("sol2/3.3.1")
        self.requires("lua/5.4.6")
        self.requires("chipmunk2d/7.0.3")
        self.requires("cista/0.15")
        self.requires("nlohmann_json/3.11.3")
        self.requires("flac/1.4.3", force=True)
        self.requires("asio/1.32.0")
        self.requires("cereal/1.3.2")

    def layout(self):
        self.folders.build = "build/Release"
        self.folders.generators = "build/Release/generators"
        self.folders.source = "src"
        cmake_layout(self)
