cmake_minimum_required(VERSION 3.10)

set(replication_sources src/main.cpp
                        src/game_object.cpp
                        src/streams.cpp
						src/quaternion.cpp
						src/vector3.cpp
						src/player.cpp
						src/ennemy.cpp
						src/linking_context.cpp
						src/class_registry.cpp
						src/replication_manager.cpp
						src/client.cpp
						src/server.cpp)

include_directories(include)
set(replication_headers include/game_object.hpp
                        include/utils.hpp
                        include/streams.hpp
						include/quaternion.hpp
						include/vector3.hpp
						include/player.hpp
						include/ennemy.hpp
						include/linking_context.hpp
						include/class_registry.hpp
						include/replication_manager.hpp
						include/client.hpp
						include/server.hpp)

add_executable(tp2 ${replication_sources} ${replication_headers})
target_link_libraries(tp2 PUBLIC uvw_interface GSL)

include(CTest)
add_executable(TestPackUnpack test/TestPackUnpack.cpp include/quaternion.hpp src/quaternion.cpp include/vector3.hpp src/vector3.cpp)
add_test(Test_PackUnpack TestPackUnpack)