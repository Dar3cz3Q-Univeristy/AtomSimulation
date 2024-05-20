#pragma once
//
// Application 
//
auto constexpr WIDTH = 800;
auto constexpr HEIGHT = 800;
auto constexpr TITLE = "Symulacja atomu";
auto constexpr MSAA_LEVEL = 8;
//
// Atom layer
//
inline unsigned int SPHERE_INDICIES_COUNT = 0;
auto constexpr MAX_ELECTRON_COUNT = 100;	// Keep number of electrons up to date in default.frag.shader
auto constexpr ELEMENTS_COUNT = 4;