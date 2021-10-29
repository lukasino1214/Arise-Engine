set_allowedarchs("x64")
set_languages("c99", "c++20")
add_rules("mode.debug", "mode.release")

if is_mode("debug") then
    add_defines("DEBUG")
    set_optimize("none")
elseif is_mode("release") then
    add_defines("NDEBUG")
    set_optimize(fastest)
end

set_optimize("fastest")

packages = {"glad", "glfw", "glm", "spdlog", "yaml-cpp", "fmt", "vcpkg::assimp", "vulkan", "entt", "stb", "vcpkg::imgui", "imguizmo"}
--packages = {"assimp"}

add_requires(packages)

target("Arise")
    set_kind("static")
    add_files("Arise/*.cpp","Arise/*/*.cpp","Arise/*/*/*.cpp")
    add_headerfiles("Arise/*.h", "Arise/*/*.h","Arise/*/*/*.h")
    add_packages(packages)


target("Arise_engine")
    set_kind("binary")
    add_files("Engine/*.cpp", "Engine/*/*.cpp")
    add_headerfiles("Engine/*.h", "Engine/*/*.h")
    set_optimize("fastest")
    add_deps("Arise")
    add_packages(packages)

