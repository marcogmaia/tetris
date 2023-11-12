// Copyright (c) Maia

#include <chrono>

#include <imgui.h>
#include <raylib.h>
#include <rlgl.h>

#include "maia/gui/imgui_extensions.h"
#include "maia/tetris/grid.h"

namespace maia {

namespace {

constexpr int kSquaseSide = 32;

}

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

void DrawShape(const Shape &shape) {
  for (const auto &pos : shape.positions) {
    DrawRectangle(pos.x * kSquaseSide, pos.y * kSquaseSide, kSquaseSide, kSquaseSide, shape.color);
  }
}

Shape GetShape() {
  auto shape = maia::Tetrominos::GetRandom();
  maia::SetPosition(2, 20, shape);
  return shape;
}

void DrawAllShapes() {
  Position pos{};
  for (const auto &tetromino : Tetrominos::kTetrominos) {
    pos = pos + Position{5, 3};
    Shape shape = tetromino;
    SetPosition(pos.x, pos.y, shape);
    DrawShape(shape);
  }
}

class Clock {
  using TickDuration = std::chrono::duration<double, std::ratio<1, 5>>;

 public:
  bool Tick() {
    auto now = std::chrono::steady_clock::now();
    auto delta = std::chrono::steady_clock::now() - next_update_;
    if (delta.count() * speed_ >= 1.0) {
      next_update_ += TickDuration(1.0 / speed_);
      return true;
    }
    return false;
  }

  void SetSpeed(double speed) {
    speed_ = speed;
  }

 private:
  double speed_ = 1;
  std::chrono::time_point<std::chrono::steady_clock, TickDuration> next_update_ = std::chrono::steady_clock::now();
  std::chrono::steady_clock clock_;
};

}  // namespace maia

namespace {

void Update(maia::Clock &clock, maia::Shape &shape) {
  if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_SPACE)) {
    clock.SetSpeed(5);
  } else {
    clock.SetSpeed(1);
  }

  if (clock.Tick()) {
    maia::Move(0, 1, shape);
  }
}

}  // namespace

int main() {
  constexpr int kWindowWidth = 1024;
  constexpr int kWindowHeight = 768;

  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(kWindowWidth, kWindowHeight, "Tetris");
  gui::ImGuiInit();

  RenderTexture render_tex = LoadRenderTexture(kWindowWidth, kWindowHeight);

  maia::Position pos0{};
  maia::Position pos1{};
  auto shape = maia::GetShape();

  maia::Clock clock{};

  while (!WindowShouldClose()) {
    Update(clock, shape);

    if (shape.positions[0].y < -1) {
      shape = maia::GetShape();
    }

    BeginTextureMode(render_tex);
    {
      ClearBackground(BLANK);
      maia::FillRandomMove(GREEN, pos0);
      maia::FillRandomMove(BLUE, pos1);
      maia::DrawShape(shape);
      maia::DrawGrid();
      maia::DrawAllShapes();
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
      // ImGui::ShowDemoWindow();
      gui::ImGuiEndFrame();
    }
    EndDrawing();
  }

  return 0;
}
