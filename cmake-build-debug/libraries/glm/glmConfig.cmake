set(GLM_VERSION "0.9.8")
set(GLM_INCLUDE_DIRS "C:/Users/lsand5108/CLionProjects/opengl_game/libraries/glm")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
