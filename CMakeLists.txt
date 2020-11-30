CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(game)

IF(WIN32)
    SET(3PARTY_PATH_DIR "${PROJECT_SOURCE_DIR}/lib3rd")
    SET(DIR_PROTOBUF ${3PARTY_PATH_DIR}/protobuf-3.14.0)
    #SET(PROTOBUF_INCLUDE ${DIR_PROTOBUF}/include)

    INCLUDE_DIRECTORIES(${DIR_PROTOBUF}/include)

    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/server/share/)
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/server/game/)
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/server/center/)
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/server/cppAgent/)

    FILE(GLOB_RECURSE share_src ${PROJECT_SOURCE_DIR}/server/share/*.cpp ${PROJECT_SOURCE_DIR}/server/share/*.h ${PROJECT_SOURCE_DIR}/server/share/*.cc)
    ADD_LIBRARY(share STATIC ${share_src})

    FILE(GLOB_RECURSE cppAgent_src ${PROJECT_SOURCE_DIR}/server/cppAgent/*.cpp)
    FILE(GLOB_RECURSE cppAgent_h ${PROJECT_SOURCE_DIR}/server/cppAgent/*.h)
    FILE(GLOB_RECURSE game_src ${PROJECT_SOURCE_DIR}/server/game/*.cpp)
    FILE(GLOB_RECURSE game_h ${PROJECT_SOURCE_DIR}/server/game/*.h)
    FILE(GLOB_RECURSE center_src ${PROJECT_SOURCE_DIR}/server/center/*.cpp)
    FILE(GLOB_RECURSE center_h ${PROJECT_SOURCE_DIR}/server/center/*.h)

    ADD_EXECUTABLE(agent ${cppAgent_src} ${cppAgent_h})
    SET_TARGET_PROPERTIES(agent PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/cppAgent/)
    TARGET_LINK_LIBRARIES(agent share)
    TARGET_LINK_LIBRARIES(agent ${PROTOBUF_LIBRARIES})

    ADD_EXECUTABLE(game ${game_src} ${game_h})
    SET_TARGET_PROPERTIES(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/game/)
    TARGET_LINK_LIBRARIES(game share)
    TARGET_LINK_LIBRARIES(game ${PROTOBUF_LIBRARIES})

    ADD_EXECUTABLE(center ${center_src} ${center_h})
    SET_TARGET_PROPERTIES(center PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/center/)
    TARGET_LINK_LIBRARIES(center share)
    TARGET_LINK_LIBRARIES(center ${PROTOBUF_LIBRARIES})









ELSE()


    SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/server/share/)
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/server/game/)
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/server/center/)
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/server/cppAgent/)
    FIND_PACKAGE(Protobuf REQUIRED)

    FILE(GLOB_RECURSE share_src ${PROJECT_SOURCE_DIR}/server/share/*.cpp ${PROJECT_SOURCE_DIR}/server/share/*.h ${PROJECT_SOURCE_DIR}/server/share/*.cc)

    ADD_LIBRARY(share STATIC ${share_src})

    SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/lib)

    FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/cppAgent/)
    FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/game/)
    FILE(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/center/)

    FILE(GLOB_RECURSE cppAgent_src ${PROJECT_SOURCE_DIR}/server/cppAgent/*.cpp)
    FILE(GLOB_RECURSE cppAgent_h ${PROJECT_SOURCE_DIR}/server/cppAgent/*.h)
    FILE(GLOB_RECURSE game_src ${PROJECT_SOURCE_DIR}/server/game/*.cpp)
    FILE(GLOB_RECURSE game_h ${PROJECT_SOURCE_DIR}/server/game/*.h)
    FILE(GLOB_RECURSE center_src ${PROJECT_SOURCE_DIR}/server/center/*.cpp)
    FILE(GLOB_RECURSE center_h ${PROJECT_SOURCE_DIR}/server/center/*.h)

    ADD_EXECUTABLE(agent.bin ${cppAgent_src} ${cppAgent_h})
    SET_TARGET_PROPERTIES(agent.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/cppAgent/)
    TARGET_LINK_LIBRARIES(agent.bin share)
    TARGET_LINK_LIBRARIES(agent.bin ${PROTOBUF_LIBRARIES})

    ADD_EXECUTABLE(game.bin ${game_src} ${game_h})
    SET_TARGET_PROPERTIES(game.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/game/)
    TARGET_LINK_LIBRARIES(game.bin share)
    TARGET_LINK_LIBRARIES(game.bin ${PROTOBUF_LIBRARIES})

    ADD_EXECUTABLE(center.bin ${center_src} ${center_h})
    SET_TARGET_PROPERTIES(center.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/center/)
    TARGET_LINK_LIBRARIES(center.bin share)
    TARGET_LINK_LIBRARIES(center.bin ${PROTOBUF_LIBRARIES})














ENDIF()





