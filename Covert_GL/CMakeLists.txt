
ADD_EXECUTABLE(Caffeine "")

FILE(GLOB_RECURSE 
    SOURCES  
        "*.cpp"
        "*.c"
        "*.hpp"
        "*.h"
)

FILE(GLOB_RECURSE 
    SHADERS  
        "*.vert"
        "*.frag"
)

TARGET_SOURCES(
    Caffeine
    PRIVATE ${SOURCES}
)

TARGET_INCLUDE_DIRECTORIES(
    Caffeine
    PRIVATE
        "./"
        "3rdParty/"
)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)

TARGET_LINK_LIBRARIES(
    Caffeine
    PRIVATE
        OpenGL::GL
        glfw
)

SET_TARGET_PROPERTIES(
    Caffeine PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

IF(UNIX) 
    TARGET_LINK_LIBRARIES(
        Caffeine
        PRIVATE 
            dl
    )
ENDIF()

ADD_CUSTOM_TARGET(
    run
    COMMAND $<TARGET_FILE:Caffeine>
    DEPENDS Caffeine
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

IF(MSVC)
    SET_TARGET_PROPERTIES(
        Caffeine PROPERTIES 
            VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${CMAKE_MSVCIDE_RUN_PATH}"
            LINK_FLAGS "/NODEFAULTLIB:LIBCMT /NODEFAULTLIB:MSVCRT"
    )
ENDIF()

FOREACH(file IN ITEMS ${SOURCES} ${SHADERS})
    FILE(RELATIVE_PATH file_path ${CMAKE_SOURCE_DIR} ${file})
    GET_FILENAME_COMPONENT(file_path ${file_path} DIRECTORY)
    FILE(TO_NATIVE_PATH ${file_path} file_path)
    SOURCE_GROUP(${file_path} FILES ${file})
ENDFOREACH()