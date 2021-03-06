# We need to execute this script at installation time because the
# DESTDIR environment variable may be unset at configuration time.
# See PR8397.

if(UNIX)
  set(CLANGXX_LINK_OR_COPY create_symlink)
  set(CLANGXX_DESTDIR $ENV{DESTDIR})
else()
  set(CLANGXX_LINK_OR_COPY copy)
endif()

# CMAKE_EXECUTABLE_SUFFIX is undefined on cmake scripts. See PR9286.
if( WIN32 )
  set(EXECUTABLE_SUFFIX ".exe")
else()
  set(EXECUTABLE_SUFFIX "")
endif()

set(bindir "${CLANGXX_DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/")
set(templight "templight${EXECUTABLE_SUFFIX}")
set(templightxx "templight++${EXECUTABLE_SUFFIX}")
set(templight_cl "templight-cl${EXECUTABLE_SUFFIX}")

message("Creating templight++ executable based on ${templight}")

execute_process(
  COMMAND "${CMAKE_COMMAND}" -E ${CLANGXX_LINK_OR_COPY} "${templight}" "${templightxx}"
  WORKING_DIRECTORY "${bindir}")

message("Creating templight-cl executable based on ${templight}")

execute_process(
  COMMAND "${CMAKE_COMMAND}" -E ${CLANGXX_LINK_OR_COPY} "${templight}" "${templight_cl}"
  WORKING_DIRECTORY "${bindir}")
