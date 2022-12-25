cmake_minimum_required (VERSION 3.10)

PROJECT (WIKI-TEST-FOOD)

add_definitions(-DUNICODE)

SET(HEADER_LIST 
    Tools.h
    Definition.h
    Core.h
    )

SET(SRC_LIST 
    main.cpp
    Tools.cpp
    Definition.cpp
    Core.cpp
    )

ADD_EXECUTABLE(WIKI-TEST-FOOD ${HEADER_LIST} ${SRC_LIST})

#调试配置launch.vs.json中需增加一条
# "currentDir": "${workspaceRoot}"