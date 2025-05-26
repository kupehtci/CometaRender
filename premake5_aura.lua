-- Include file that defines "clean" action for removing build files
include "clean.lua"

workspace "Aura"
	configurations { "Debug", "Release" }

    -- Compile for x64 format. For 32 bits set to x86
    architecture "x86_64"

-- Array of the include directories
IncludeDir = {}
IncludeDir["GLM"] = "vendor/glm/glm"
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["GLAD"] = "vendor/glad/include"
IncludeDir["STB_IMAGE"] = "vendor/stb_image"


-- Include other Premake5 files for:
--          * GLAD initialization

include "vendor/glad"

project "AuraGL"
	kind "ConsoleApp"  
	language "C++"
    cppdialect "C++17"
        
    includedirs {
        "src"
--             "src/debug",
--             "src/core",
--             "src/components",
--             "src/math",
--             "src/physics",
--             "src/render",
--             "src/ui"
    }
	files { 
            "src/**.h",
            "src/**.cpp",
            "src/**.vert",
            "src/**.frag"
    }


    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin/obj/%{cfg.buildcfg}")


    filter "system:macosx"

        includedirs{
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.GLM}",
            "%{IncludeDir.GLAD}",
            "%{IncludeDir.STB_IMAGE}"
        }

        libdirs{
            "vendor/glad/bin"
        }

        links{
            "glfw",
            "OpenGL.framework",
            "glad"
        }

        defines { "PLATFORM_MACOS" }
    filter "system:linux"


    -- WINDOWS Expecifications
    filter "system:windows"
        includedirs{
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.GLM}",
            "%{IncludeDir.GLAD}",
            "%{IncludeDir.STB_IMAGE}"
        }
        libdirs{
            "vendor/GLFW/lib"
        }
        links{
            "glfw3",
            "glad"
        }
        defines { "PLATFORM_WINDOWS" }


	filter { "configurations:Debug" }  
        defines { "DEBUG" }  
        symbols "On"  
	  
	filter { "configurations:Release" }  
        defines { "NDEBUG" }  
        optimize "On"