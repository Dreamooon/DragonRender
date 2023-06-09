cmake_minimum_required(VERSION 3.24)
project(dragon)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(Eigen3 CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(embree 3 CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(assimp)
find_package(OpenImageDenoise)



file(GLOB dragon_src
        src/dragon/*.cpp
        src/dragon/core/*.cpp
        src/dragon/cameras/*.cpp
        src/dragon/shapes/*.cpp
        src/dragon/emitters/*.cpp
        src/dragon/bsdfs/*.cpp
        src/dragon/samplers/*.cpp
        src/dragon/integrators/*.cpp
        )

add_executable(dragon ${dragon_src})

target_link_libraries(dragon PRIVATE
        Eigen3::Eigen
        ZLIB::ZLIB
        embree
        TBB::tbb
        TBB::tbbmalloc
        TBB::tbbmalloc_proxy
        spdlog::spdlog
        spdlog::spdlog_header_only
        assimp::assimp
        OpenImageDenoise)

file(GLOB dlls ${EMBREE_ROOT_DIR}/bin/*.dll)
#add_custom_command(TARGET dragon POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${dlls}
#        $<TARGET_FILE_DIR:dragon>)

