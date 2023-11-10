add_library(gui "./imgui_extensions.cpp")

target_link_libraries(
  gui
  PUBLIC imgui::imgui raylib
)
