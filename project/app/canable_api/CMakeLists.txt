project (canable)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/canframe.h
    )

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/canframe.cpp
    )

if (WIN32)
    set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/candle/ch_9.h
        ${CMAKE_CURRENT_SOURCE_DIR}/candle/candle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/candle/candle_defs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/candle/candle_ctrl_req.h
        ${CMAKE_CURRENT_SOURCE_DIR}/candle/WinCan.h
        )
    set(SOURCES
        ${SOURCES}
        #${CMAKE_CURRENT_SOURCE_DIR}/candle/gsusb.c
        ${CMAKE_CURRENT_SOURCE_DIR}/candle/candle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/candle/candle_ctrl_req.c
        ${CMAKE_CURRENT_SOURCE_DIR}/candle/WinCan.cpp
        )
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/candle)

else()
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/socketcan)
    set(SOURCES
        ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/socketcan/socketcan_if.cpp
    )
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) 

ADD_LIBRARY(candle SHARED ${HEADERS} ${SOURCES})
TARGET_LINK_LIBRARIES(candle winusb.lib setupapi.lib)


ADD_EXECUTABLE(sito_motor examples/sito_motor.cpp examples/sito.h examples/sito.cpp)
TARGET_LINK_LIBRARIES(sito_motor candle)

#메인 함수
add_library(EYOUBOTLIB STATIC examples/eyoubot_function.cpp)
ADD_EXECUTABLE(canable examples/main_win.cpp)
TARGET_LINK_LIBRARIES(canable candle)
TARGET_LINK_LIBRARIES(canable EYOUBOTLIB)

# 모터 id를 설정
ADD_EXECUTABLE(eyoubot_motor_id examples/eyoubot_motor_id.cpp examples/eyoubot_id.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_id candle)

# 모터 baudrate를 설정
ADD_EXECUTABLE(eyoubot_motor_baudrate examples/eyoubot_motor_baudrate.cpp examples/eyoubot_baudrate.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_baudrate candle)


#모터를 position 으로 제어
ADD_EXECUTABLE(eyoubot_motor_position_control examples/eyoubot_motor_position_control.cpp examples/eyoubot_position_control.h examples/eyoubot_position_control.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_position_control candle)

# 모터를 current 로 제어
ADD_EXECUTABLE(eyoubot_motor_current_control examples/eyoubot_motor_current_control.cpp examples/eyoubot_current_control.h examples/eyoubot_current_control.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_current_control candle)



# 모터를 의 최대 current 를 제한
ADD_EXECUTABLE(eyoubot_motor_limit_current examples/eyoubot_motor_limit_current.cpp examples/eyoubot_limit_current.h examples/eyoubot_limit_current.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_limit_current candle)


# 모터를 의 최대 speed 를 제한
ADD_EXECUTABLE(eyoubot_motor_limit_speed examples/eyoubot_motor_limit_speed.cpp examples/eyoubot_limit_speed.h examples/eyoubot_limit_speed.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_limit_speed candle)

# 모터를 의 최대 position 를 제한
ADD_EXECUTABLE(eyoubot_motor_limit_upper_position examples/eyoubot_motor_limit_upper_position.cpp examples/eyoubot_limit_upper_position.h examples/eyoubot_limit_upper_position.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_limit_upper_position candle)

# 모터를 의 최저 position 를 제한
ADD_EXECUTABLE(eyoubot_motor_limit_lower_position examples/eyoubot_motor_limit_lower_position.cpp examples/eyoubot_limit_lower_position.h examples/eyoubot_limit_lower_position.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_limit_lower_position candle)



# 모터 중지 (cease)
ADD_EXECUTABLE(eyoubot_motor_cease examples/eyoubot_motor_cease.cpp examples/eyoubot_cease.h examples/eyoubot_cease.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_cease candle)



# 모터 origin 설정
ADD_EXECUTABLE(sito_motor_set_origin examples/sito_motor_set_origin.cpp examples/sito_set_origin.h examples/sito_set_origin.cpp)
TARGET_LINK_LIBRARIES(sito_motor_set_origin candle)

# 모터 origin 으로 돌아가기
ADD_EXECUTABLE(sito_motor_return_to_origin examples/sito_motor_return_to_origin.cpp examples/sito_return_to_origin.h examples/sito_return_to_origin.cpp)
TARGET_LINK_LIBRARIES(sito_motor_return_to_origin candle)





# 모터 speed 로 제어
ADD_EXECUTABLE(eyoubot_motor_speed_control examples/eyoubot_motor_speed_control.cpp examples/eyoubot_speed_control.h examples/eyoubot_speed_control.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_speed_control candle)

# 모터 voltage 출력
ADD_EXECUTABLE(eyoubot_motor_get_voltage examples/eyoubot_motor_get_voltage.cpp examples/eyoubot_get_voltage.h examples/eyoubot_get_voltage.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_get_voltage candle)

# 모터 postion 출력
ADD_EXECUTABLE(eyoubot_motor_get_position examples/eyoubot_motor_get_position.cpp examples/eyoubot_get_position.h examples/eyoubot_get_position.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_get_position candle)

# 모터 current 출력
ADD_EXECUTABLE(eyoubot_motor_get_current examples/eyoubot_motor_get_current.cpp examples/eyoubot_get_current.h examples/eyoubot_get_current.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_get_current candle)

# 모터 temperature 출력
ADD_EXECUTABLE(eyoubot_motor_get_temperature examples/eyoubot_motor_get_temperature.cpp examples/eyoubot_get_temperature.h examples/eyoubot_get_temperature.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_get_temperature candle)



# 모터 temperature 출력
ADD_EXECUTABLE(eyoubot_motor_get_speed examples/eyoubot_motor_get_speed.cpp examples/eyoubot_get_speed.h examples/eyoubot_get_speed.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_get_speed candle)


# eyoubot 함수 통합
ADD_EXECUTABLE(eyoubot_motor_function examples/eyoubot_motor_function.cpp examples/eyoubot_function.h examples/eyoubot_function_export.h examples/eyoubot_function.cpp)
TARGET_LINK_LIBRARIES(eyoubot_motor_function candle)

