project (Tutorial)

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/../include/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
)

add_executable(Tutorial ./Tutorial/tutorial.cxx)
add_library(LedDriver ./LedDriver/LedDriver.c)