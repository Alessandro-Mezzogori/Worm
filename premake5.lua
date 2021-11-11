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
MainProjectName = "Worm"

IncludeDirs = {}
IncludeDirs["spdlog"] = "%{prj.name}/vendor/spdlog/include"
IncludeDirs["GLFW"] =  "%{prj.name}/vendor/GLFW/include"
IncludeDirs["Glad"] =  "%{prj.name}/vendor/Glad/include"
IncludeDirs["ImGui"] =  "%{prj.name}/vendor/imgui"
IncludeDirs["glm"] =  "Worm/vendor/glm"
IncludeDirs["spirv_cross"] = "%{prj.name}/vendor/spirv-cross"
IncludeDirs["stb_image"] =  "%{prj.name}/vendor/stb_image"
IncludeDirs["vulkan"] = "$(VULKAN_SDK)/Include"

LibDirs = {}
--LibDirs["vulkan"] = "C:/VulkanSDK/1.2.170.0/Lib"
LibDirs["vulkan"] = "$(VULKAN_SDK)/Lib"

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
            "%{prj.name}/src/**.cpp",
            "%{IncludeDirs.stb_image}/stb_image.cpp" -- include stb_image.cpp
    }

    includedirs
    {
            "%{prj.name}/src",
            "%{IncludeDirs.spdlog}",
            "%{IncludeDirs.GLFW}",
            "%{IncludeDirs.Glad}",
            "%{IncludeDirs.ImGui}",
            "%{IncludeDirs.glm}",
            "%{IncludeDirs.spirv_cross}",
            "%{IncludeDirs.vulkan}",
            "%{IncludeDirs.stb_image}"
    }

    libdirs 
    {
            "%{LibDirs.vulkan}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib",
        "vulkan-1.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "WORM_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
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
            "%{IncludeDirs.glm}"
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
