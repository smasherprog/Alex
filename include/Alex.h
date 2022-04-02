// Alex.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include <stdio.h>          // printf, fprintf
#include <stdlib.h>         // abort
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <assimp/Importer.hpp>
#include <assimp/config.h>
#include "sail/src/bindings/c++/sail-c++.h"

#include <iostream>