#set(CMAKE_CXX_STANDARD 17)
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_executable(Test Test.cpp)
target_link_libraries(Test PRIVATE Catch2::Catch2WithMain LongNumber::library)
add_test(NAME Tests COMMAND Test --success)
add_test(NAME piCounting COMMAND Main)