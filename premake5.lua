workspace "Worm"   
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcgf}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder ( Solutino folder)
IncludeDirs = {}
IncludeDirs["GLFW"] = "Worm/vendor/GLFW/include"
IncludeDirs["Glad"] = "Worm/vendor/Glad/include"
IncludeDirs["ImGui"] = "Worm/vendor/imgui"
IncludeDirs["glm"] = "Worm/vendor/glm"
IncludeDirs["spirv_cross"] = "Worm/vendor/spirv-cross"

-- Include the IndluceDirs premake files
group "Dependencies"
    include "Worm/vendor/GLFW"
    include "Worm/vendor/Glad"
    include "Worm/vendor/imgui"
group ""


-- Worm Engine project file
project "Worm"
    location "Worm"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"


    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "wormpch.h"
    pchsource "Worm/src/wormpch.cpp"

    files
    {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
            "%{prj.name}/src",
            "%{prj.name}/vendor/spdlog/include",
            "%{IncludeDirs.GLFW}",
            "%{IncludeDirs.Glad}",
            "%{IncludeDirs.ImGui}",
            "%{IncludeDirs.glm}",
            "%{IncludeDirs.spirv_cross}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "WORM_PLATFORM_WINDOWS"
        }


    filter "configurations:Debug"
        defines "WORM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "WORM_RELEASE"
        runtime "Release"
        optimize "on"
       
    filter "configurations:Dist"
        defines "WORM_DIST"
        runtime "Release"
        optimize "on"


-- Sandbox for Worm Engine project file
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
            "Worm/vendor/spdlog/include",
            "Worm/src",
            "Worm/vendor",
            "%{IncludeDirs.glm}",
    }

    links
    {
        "Worm"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "WORM_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "WORM_DEBUG"          
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "WORM_RELEASE"        
        runtime "Release"
        optimize "on"
       
    filter "configurations:Dist"
        defines "WORM_DIST"
        runtime "Release"
        optimize "on"


-- Sandbox for Worm Engine project file
project "UnitTesting"
    location "UnitTesting"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
            "Worm/vendor/spdlog/include",
            "Worm/src",
            "Worm/vendor",
            "%{IncludeDirs.glm}",
    }

    links
    {
        "Worm"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "WORM_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "WORM_DEBUG"          
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "WORM_RELEASE"        
        runtime "Release"
        optimize "on"
       
    filter "configurations:Dist"
        defines "WORM_DIST"
        runtime "Release"
        optimize "on"
