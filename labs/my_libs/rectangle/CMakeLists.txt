add_library(point_static STATIC point.cpp)

add_library(rect_static
    STATIC rectangle.cpp
)

# target_link_libraries(rect_static
# STATIC point_static
# )
