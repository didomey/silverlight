add_subdirectory(Game)
add_subdirectory(Internal)
add_subdirectory(Shared)

target_sources(silverlight PRIVATE
        src/Assembly.cpp
)

target_compile_definitions(silverlight PRIVATE VASSEMBLYNAME="Silverlight")
