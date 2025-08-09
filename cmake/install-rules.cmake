install(
    TARGETS CEUnpack_exe
    RUNTIME COMPONENT CEUnpack_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
