project "Atom Simulation"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("../bin-int/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"Dependencies/**.h",
		"Dependencies/**.cpp",
		"Dependencies/**.c"
	}

	removefiles {
		"src/vendor/imgui/main.cpp"
	}

	includedirs
	{
		"src",
		"src/vendor",
		"Dependencies/glad/include",
		"Dependencies/GLFW/include"
	}

	libdirs 
	{ 
		"Dependencies/GLFW/lib"
	}

	links 
	{ 
		"glfw3.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"