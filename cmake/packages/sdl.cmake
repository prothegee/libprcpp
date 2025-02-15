#[=[
sdl

repo link: https://github.com/libsdl-org/SDL
#]=]
set(LIBPRCPP_PROJECT_USING_SDL false)

if(NOT BUILD_SKIPPED_VENDOR_SDL)
    set(LIBPRCPP_PROJECT_USING_SDL true) # always true since use project vendors

    set(LIBPRCPP_VENDOR_SDL_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/sdl")

    # set(SDL_SHARED false)
    # set(SDL_STATIC true)
    set(SDL_TEST_LIBRARY false)

    add_subdirectory(${LIBPRCPP_VENDOR_SDL_DIR} LIBPRCPP_SDL)

    include_directories(${LIBPRCPP_VENDOR_SDL_DIR}/include)

    link_directories(AFTER "${CMAKE_BINARY_DIR}/LIBPRCPP_SDL")

    message(NOTICE "-- sdl lib using project vendor dir as ${LIBPRCPP_VENDOR_SDL_DIR}")
endif()
