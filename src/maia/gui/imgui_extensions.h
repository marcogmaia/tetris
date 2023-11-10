// Copyright (c) Maia

#pragma once

#include <imgui.h>
#include <raylib.h>

namespace gui {

void ImGuiInit();
void ImGuiTerminate();

// Update and Render additional Platform Windows
// (Platform functions may change the current OpenGL context, so we save/restore
// it to make it easier to paste this code elsewhere.
//  For this specific demo app we could also call glfwMakeContextCurrent(window)
//  directly)
void ImGuiProcessViewports();

void ImGuiImage(const ::Texture& texture);

void ImGuiImageRect(const ::Texture& texture, ::Rectangle source_rect);

void ImGuiBeginFrame();

void ImGuiEndFrame();

}  // namespace gui
