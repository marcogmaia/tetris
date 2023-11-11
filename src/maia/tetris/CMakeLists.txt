add_executable(tetris "./main.cpp")

target_link_libraries(
  tetris
  PRIVATE gui
          raylib
          imgui::imgui
)

add_executable(tetris_test "./shape_test.cpp")

target_link_libraries(
  tetris_test
  PRIVATE GTest::gmock_main
          gui
          raylib
)

gtest_discover_tests(
  tetris_test
  DISCOVERY_TIMEOUT
  60
)
