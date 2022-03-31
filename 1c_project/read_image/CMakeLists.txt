project(ReadImageLibrary)


set(SOURCE_FILES "read_image.cpp")
set(HEADER_FILES "read_image.h")

add_library(ReadImageLibrary STATIC ${HEADER_FILES} ${SOURCE_FILES})