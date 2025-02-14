# libprcpp instlal
install(TARGETS ${LIBPRCPP_PROJECT}
        EXPORT LibprcppTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

        
install(EXPORT LibprcppTargets
        FILE LibprcppConfig.cmake
        NAMESPACE libprcpp::
        DESTINATION share/libprcpp)


## root
set(LIBPRCPP_INC_DIR_BASE
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/libprcpp.hh
)
install(FILES ${LIBPRCPP_INC_DIR_BASE} DESTINATION include/libprcpp)


## base
set(LIBPRCPP_INC_DIR_BASE
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/base/config.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/base/export.hh
)
install(FILES ${LIBPRCPP_INC_DIR_BASE} DESTINATION include/libprcpp/base)


## constants
set(LIBPRCPP_INC_DIR_CONSTANTS
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/constants/files_const.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/constants/header_const.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/constants/host_const.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/constants/return_const.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/constants/strings_const.hh
)
install(FILES ${LIBPRCPP_INC_DIR_CONSTANTS} DESTINATION include/libprcpp/constants)


## enums
set(LIBPRCPP_INC_DIR_ENUMS
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/enums/encdec_enums.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/enums/language_enums.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/enums/result_enums.hh
)
install(FILES ${LIBPRCPP_INC_DIR_ENUMS} DESTINATION include/libprcpp/enums)


## functions
set(LIBPRCPP_INC_DIR_FUNCTIONS
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/functions/cryptography_funcs.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/functions/date_and_times_funcs.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/functions/images_funcs.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/functions/network_funcs.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/functions/system_funcs.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/functions/utility_funcs.hh
)
install(FILES ${LIBPRCPP_INC_DIR_FUNCTIONS} DESTINATION include/libprcpp/functions)


## interfaces
set(LIBPRCPP_INC_DIR_INTERFACES
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/interfaces/idrogon_http_controller_helper.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/interfaces/ipostgresql_core_interface.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/interfaces/iscylladb_core_interface.hh
)
install(FILES ${LIBPRCPP_INC_DIR_INTERFACES} DESTINATION include/libprcpp/interfaces)


## types
set(LIBPRCPP_INC_DIR_TYPES
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/types/base_types.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/types/batch_types.hh
    ${LIBPRCPP_PROJECT_DIR}/inc/libprcpp/types/look_types.hh
)
install(FILES ${LIBPRCPP_INC_DIR_TYPES} DESTINATION include/libprcpp/types)


#######################################################################


## hpdf
install(TARGETS hpdf
        EXPORT LibprcppTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)


## sdl3
install(TARGETS SDL3-static
    EXPORT LibprcppTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS SDL_uclibc
    EXPORT LibprcppTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS SDL3_Headers
    EXPORT LibprcppTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
