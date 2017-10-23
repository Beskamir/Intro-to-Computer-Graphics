set(GLM_VERSION "0.9.8")
set(GLM_INCLUDE_DIRS "D:/Education/University/Current/cpsc453/Assignments/Assignment2/cpsc453_a2/Assignment2/deps/glm")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
