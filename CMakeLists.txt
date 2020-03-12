cmake_minimum_required(VERSION 3.15)
project(warp)

set(CMAKE_CXX_STANDARD 14)

add_executable(warp
        README.md src/model/GameModel.cpp src/model/GameModel.h src/main.cpp src/model/Field.cpp src/model/Field.h src/model/FieldEntity.cpp src/model/FieldEntity.h src/model/EntityType.h src/model/Stable/Stable.cpp src/model/Stable/Stable.h src/model/Unstable/Unstable.cpp src/model/Unstable/Unstable.h src/model/Team.h src/model/Stable/Hq.cpp src/model/Stable/Hq.h src/model/Stable/Special.cpp src/model/Stable/Special.h src/model/Stable/Factory.cpp src/model/Stable/Factory.h src/model/Stable/Stable1.cpp src/model/Stable/Stable1.h src/model/Stable/HqDefense.cpp src/model/Stable/HqDefense.h src/model/Stable/HqAttack.cpp src/model/Stable/HqAttack.h src/model/Unstable/Friendly.cpp src/model/Unstable/Friendly.h src/model/Unstable/Enemy.cpp src/model/Unstable/Enemy.h src/model/Unstable/Enemy1.cpp src/model/Unstable/Enemy1.h)
