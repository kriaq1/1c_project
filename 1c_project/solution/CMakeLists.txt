project(SolutionLibrary)


set(SOURCE_FILES "solution.cpp")
set(HEADER_FILES "solution.h")

add_library(SolutionLibrary STATIC ${HEADER_FILES} ${SOURCE_FILES})