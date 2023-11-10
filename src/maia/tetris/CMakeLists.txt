add_executable(tetris "./main.cpp")

target_link_libraries(
  tetris
  PRIVATE gui
          raylib
          imgui::imgui
)
