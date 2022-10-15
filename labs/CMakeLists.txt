# add libraries
include_directories(my_libs)
include_directories(my_libs/rectangle)
add_subdirectory(my_libs)

# comment different seminar folders not to built them
# add_subdirectory(s1) - empty
# add_subdirectory(s2) - empty
# add_subdirectory(s3)

# add_subdirectory(s4)
# add_subdirectory(s5)

# add my_libs
add_subdirectory(s6)