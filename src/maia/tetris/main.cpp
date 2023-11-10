// Copyright (c) Maia

#include <imgui.h>
#include <raylib.h>
#include <rlgl.h>

#include "maia/gui/imgui_extensions.h"

int main() {
  constexpr int kWindowWidth = 1024;
  constexpr int kWindowHeight = 768;

  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(kWindowWidth, kWindowHeight, "Tetris");
  gui::ImGuiInit();

  RenderTexture render_tex = LoadRenderTexture(kWindowWidth, kWindowHeight);

  while (!WindowShouldClose()) {
    BeginTextureMode(render_tex);
    ClearBackground(GRAY);
    EndTextureMode();

    BeginDrawing();
    {
      ClearBackground(BLANK);
      // Draw the gray texture.
      DrawTexture(render_tex.texture, 0, 0, WHITE);
      rlDrawRenderBatchActive();

      // ImGui stuff goes below.
      gui::ImGuiBeginFrame();
      ImGui::ShowDemoWindow();
      gui::ImGuiEndFrame();
    }
    EndDrawing();
  }

  return 0;
}
