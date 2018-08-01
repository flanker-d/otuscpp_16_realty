cmake_minimum_required(VERSION 3.2)

project(realty VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include_directories(${PROJECT_SOURCE_DIR})

configure_file(version.h.in version.h)

find_package(dlib REQUIRED)

add_executable(rclst realty_clustering/rclst.cpp realty_clustering/clustering.cpp realty_clustering/clustering.h data_types.h)
target_link_libraries(rclst dlib::dlib)

add_executable(rclss realty_classification/rclss.cpp realty_classification/classification.cpp realty_classification/classification.h)
target_link_libraries(rclss dlib::dlib)

set_target_properties(rclst rclss PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

install(TARGETS rclst rclss RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artyom.sorokoumov@gmail.com)

include(CPack)
