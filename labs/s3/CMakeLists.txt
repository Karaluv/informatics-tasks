# add_executable(l10
# l10.cpp)
# add_executable(l15
# l15.cpp)

add_library(all_libs
    l10_rect.cpp
)

add_executable(l20
    l20.cpp)
target_link_libraries(l20
    ${ALL_LIBS}
    all_libs
)