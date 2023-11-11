// Copyright (c) Maia

#include <imgui.h>
#include <raylib.h>
#include <rlgl.h>

#include "maia/gui/imgui_extensions.h"
#include "maia/tetris/grid.h"

namespace maia {

constexpr int kSquaseSide = 32;

void DrawGrid() {
  constexpr auto kWidth = Grid::GridWidth();
  constexpr auto kHeight = Grid::GridHeight();
  constexpr auto kX = kSquaseSide * kWidth;
  constexpr auto kY = kSquaseSide * kHeight;
  for (int h = 0; h <= kHeight; ++h) {
    auto y = h * kSquaseSide;
    DrawLine(0, y, kX, y, WHITE);
  }
  for (int v = 0; v <= kWidth; ++v) {
    auto x = v * kSquaseSide;
    DrawLine(x, 0, x, kY, WHITE);
  }
}

void FillPosition(int x, int y, Color color = GREEN) {
  DrawRectangle(x * kSquaseSide, y * kSquaseSide, kSquaseSide, kSquaseSide, color);
}

void FillRandomPosition(Color color) {
  auto x = GetRandomValue(0, maia::Grid::GridWidth() - 1);
  auto y = GetRandomValue(0, maia::Grid::GridHeight() - 1);
  FillPosition(x, y, color);
}

void FillRandomMove(Color color, Position &pos) {
  pos.x = std::clamp(pos.x + GetRandomValue(-1, 1), 0, Grid::GridWidth() - 1);
  pos.y = std::clamp(pos.y + GetRandomValue(-1, 1), 0, Grid::GridHeight() - 1);
  FillPosition(pos.x, pos.y, color);
}

}  // namespace maia

int main() {
  constexpr int kWindowWidth = 1024;
  constexpr int kWindowHeight = 768;

  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(kWindowWidth, kWindowHeight, "Tetris");
  gui::ImGuiInit();

  RenderTexture render_tex = LoadRenderTexture(kWindowWidth, kWindowHeight);

  maia::Position pos0{};
  maia::Position pos1{};

  while (!WindowShouldClose()) {
    BeginTextureMode(render_tex);
    {
      ClearBackground(GRAY);

      // maia::FillPosition(x, y);
      // maia::FillRandomPosition(GREEN);
      // maia::FillRandomPosition(BLUE);
      maia::FillRandomMove(GREEN, pos0);
      maia::FillRandomMove(BLUE, pos1);
      maia::DrawGrid();
      WaitTime(0.1);
    }
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
