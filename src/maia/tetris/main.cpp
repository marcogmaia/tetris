// Copyright (c) Maia

#include <chrono>

#include <imgui.h>
#include <raylib.h>
#include <rlgl.h>

#include "maia/gui/imgui_extensions.h"
#include "maia/tetris/grid.h"
#include "maia/tetris/tetris.h"

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

void DrawTetromino(const Tetromino &tetromino) {
  for (const auto &pos : tetromino.positions) {
    DrawRectangle(pos.x * kSquaseSide, pos.y * kSquaseSide, kSquaseSide, kSquaseSide, tetromino.color);
  }
}

class Clock {
  using TickDuration = std::chrono::duration<double, std::ratio<1, 5>>;

 public:
  bool Tick() {
    auto now = std::chrono::steady_clock::now();
    auto delta = std::chrono::steady_clock::now() - next_update_;
    if (delta.count() * speed_ >= 0.0) {
      next_update_ += TickDuration(1.0 / speed_);
      return true;
    }
    return false;
  }

  void Reset() {
    next_update_ = std::chrono::steady_clock::now() + TickDuration{1};
  }

  void SetSpeed(double speed) {
    speed_ = speed;
    next_update_ = std::chrono::steady_clock::now() + TickDuration(1.0 / speed_);
  }

  static float GetClockRate() {
    return static_cast<float>(TickDuration::period::num) / static_cast<float>(TickDuration::period::den);
  }

 private:
  double speed_ = 0.2;
  std::chrono::time_point<std::chrono::steady_clock, TickDuration> next_update_ = std::chrono::steady_clock::now();
  std::chrono::steady_clock clock_;
};

}  // namespace maia

namespace {

void Update(maia::Clock &clock, maia::Tetris &tetris) {
  if (IsKeyReleased(KEY_SPACE)) {
    clock.SetSpeed(maia::Clock::GetClockRate());
  }
  if (IsKeyPressed(KEY_SPACE)) {
    clock.SetSpeed(5);
    tetris.Tick();
    return;
  }

  if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
    tetris.Move(-1, 0);
  }

  if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
    tetris.Move(1, 0);
  }

  if (IsKeyPressed(KEY_R)) {
    tetris.RotateLeft();
  }

  if (IsKeyPressed(KEY_N)) {
    tetris.Reset();
  }

  if (clock.Tick()) {
    tetris.Tick();
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

  maia::Clock clock{};
  maia::Tetris tetris{};

  while (!WindowShouldClose()) {
    Update(clock, tetris);

    // Draw tetris in another texture.
    BeginTextureMode(render_tex);
    {
      ClearBackground(BLANK);
      maia::DrawTetromino(tetris.CurrentTetromino());
      maia::DrawGrid();
      maia::DrawGrid(tetris.grid());
    }
    EndTextureMode();

    BeginDrawing();
    {
      ClearBackground(BLANK);
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
