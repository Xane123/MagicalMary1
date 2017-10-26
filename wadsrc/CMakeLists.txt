cmake_minimum_required( VERSION 2.8.7 )

if(ZDOOM_GENERATE_PK3)
	add_pk3(data.pk3 ${CMAKE_CURRENT_SOURCE_DIR}/static)
endif()