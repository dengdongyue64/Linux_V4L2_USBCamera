project(usb_camera)
cmake_minimum_required(VERSION 2.8.12)

set(TARGET_NAME usb_camera)
set(SRC_FILES
	main.c
	camera.c
	V4L2.c
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
  #${CMAKE_CURRENT_SOURCE_DIR}/../../video/
  #${CMAKE_CURRENT_SOURCE_DIR}/../../../out/system/include/
)

link_directories(
  #${CMAKE_CURRENT_SOURCE_DIR}/../../../out/system/lib/
)
add_executable(${TARGET_NAME} ${SRC_FILES})
#target_link_libraries(${TARGET_NAME} ion mpp)

install(TARGETS ${TARGET_NAME} DESTINATION bin)
