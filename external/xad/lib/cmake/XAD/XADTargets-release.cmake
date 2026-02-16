#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "XAD::xad" for configuration "Release"
set_property(TARGET XAD::xad APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(XAD::xad PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/xad64_vc144_mt.lib"
  )

list(APPEND _cmake_import_check_targets XAD::xad )
list(APPEND _cmake_import_check_files_for_XAD::xad "${_IMPORT_PREFIX}/lib/xad64_vc144_mt.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
