workspace "Atom Simulation"
    architecture "x64"
    startproject "Atom Simulation"

    configurations {
        "Debug",
        "Release"
    }

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

    OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    include "Atom Simulation/premake5.lua"