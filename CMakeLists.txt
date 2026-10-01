cmake_minimum_required(VERSION 3.15)

project(PankeyEngine_Type_Map_Test)

if(NOT TARGET ThePankeyEngine_Type_Map_Test)

    add_library(ThePankeyEngine_Type_Map_Test INTERFACE)

    target_include_directories(
        ThePankeyEngine_Type_Map_Test
          INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

endif()