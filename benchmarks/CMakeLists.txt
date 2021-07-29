project(benchmarks)

include(FetchContent)

# Externally provided libraries
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG master) # need master for benchmark::benchmark

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

set(ALL_BENCHES "")

# Find benchmark sources
file(GLOB BENCH_SOURCES "*.cpp")

# Build benchmarks
foreach(BENCH_SOURCE ${BENCH_SOURCES})
    get_filename_component(BENCH_NAME ${BENCH_SOURCE} NAME_WE)
    set(BENCH_TARGET "${BENCH_NAME}")

    add_executable(${BENCH_TARGET} ${BENCH_SOURCE})
    target_link_libraries(${BENCH_TARGET} benchmark bot map)

    list(APPEND ALL_BENCHES ${BENCH_TARGET})
endforeach()
