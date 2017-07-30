if(${OS} STREQUAL "ubuntu")

file(GLOB ELKA_PYTHON_SRC_FILES 
  "${CMAKE_CURRENT_SOURCE_DIR}/*.py"
)

foreach(python_src_file ${ELKA_PYTHON_SRC_FILES})
  file(
    COPY "${python_src_file}"
    DESTINATION "${ELKA_BINARY_DIR}/python"
  )
endforeach()

else()

message(
	FATAL_ERROR
	"OS ${OS} not supported with elka_comm library"
)

endif()
# vim: set noet ft=cmake fenc=utf-8 ff=unix :
