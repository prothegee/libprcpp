#[=[
sdl

repo link: https://github.com/libsdl-org/SDL
#]=]
set(LIBPRCPP_PROJECT_USING_SDL true) # always true since use project vendors

set(LIBPRCPP_VENDOR_LUNASVG_DIR "${LIBPRCPP_PROJECT_ROOT}/vendors/sdl")

add_subdirectory(${LIBPRCPP_VENDOR_LUNASVG_DIR} LIBPRCPP_SDL)
