cmake_minimum_required(VERSION 3.15...3.30)


project(libprcpp-project)


set(LIBPRCPP_PROJECT_ROOT ${PROJECT_SOURCE_DIR}) # libprcpp project root as var


include(cmake/project-0-pre_config.cmake)
include(cmake/project-1-packages.cmake)
include(cmake/project-0-pre_config.cmake)


add_subdirectory(library/libprcpp)


if(LIBPRCPP_PROJECT_BUILD_TOOLS)
    add_subdirectory(tools/prgent)
endif()


if(LIBPRCPP_PROJECT_BUILD_TESTS)
    add_subdirectory(test/test_libprcpp)
endif()
