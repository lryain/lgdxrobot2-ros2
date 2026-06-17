#ifndef __LGDXROBOT2_H
#define __LGDXROBOT2_H

#include <stdint.h>
#include <stdbool.h>

// Operation Configuration
#define PID_LEVEL 3
#define API_MOTOR_COUNT 4

#define MCU_HEADER1 0xAA
#define MCU_HEADER2 0x55
#define MCU_HEADER3 0xA5
#define MCU_HEADER4 0x5A

#define MCU_DATA_TYPE 'D'
#define MCU_MAG_CALIBRATION_DATA_TYPE 'G'
#define MCU_SERIAL_NUMBER_TYPE 'S'
#define MCU_PID_TYPE 'P'
#define MCU_ENCODER_PPR_TYPE 'Y'  // Encoder PPR data type

#define MCU_SOFTWARE_EMERGENCY_STOP_COMMAND_TYPE 'E'
#define MCU_INVERSE_KINEMATICS_COMMAND_TYPE 'I'
#define MCU_MOTOR_COMMAND_TYPE 'M'
#define MCU_SET_PID_SPEED_COMMAND_TYPE 'L'
#define MCU_GET_PID_COMMAND_TYPE 'P'
#define MCU_SET_PID_COMMAND_TYPE 'Q'
#define MCU_SAVE_CONFIGURATION_COMMAND_TYPE 'R'
#define MCU_GET_SERIAL_NUMBER_COMMAND_TYPE 'S'
#define MCU_RESET_TRANSFORM_COMMAND_TYPE 'T'
#define MCU_SET_MOTOR_MAXIMUM_SPEED_COMMAND_TYPE 'V'
#define MCU_SET_MAG_CALIBRATION_DATA_COMMAND_TYPE 'W'
#define MCU_GET_MAG_CALIBRATION_DATA_COMMAND_TYPE 'X'
#define MCU_MOTOR_BRAKE_COMMAND_TYPE 'B'        // 电机刹车/Coast命令
#define MCU_LED_CONTROL_COMMAND_TYPE 'F'        // LED灯带控制命令
#define MCU_GET_ENCODER_PPR_COMMAND_TYPE 'Y'    // 获取编码器PPR
#define MCU_SET_ENCODER_PPR_COMMAND_TYPE 'Z'    // 设置编码器PPR
#define MCU_GET_AUTO_BRAKE_CONFIG_COMMAND_TYPE 'H'  // Get auto-brake config
#define MCU_SET_AUTO_BRAKE_ENABLED_COMMAND_TYPE 'J' // Set auto-brake enabled
#define MCU_SET_AUTO_BRAKE_TIMEOUT_COMMAND_TYPE 'K' // Set auto-brake timeout

#pragma pack(push, 1)

/*
 * MCU to PC communication
 */

typedef struct {
  float x;
  float y;
  float rotation;
} McuDof;

typedef struct {
  float x;
  float y;
  float z;
} McuAxisRaw;

typedef struct {
  McuAxisRaw accelerometer;
  McuAxisRaw accelerometer_covariance;
  McuAxisRaw gyroscope;
  McuAxisRaw gyroscope_covariance;
  McuAxisRaw magnetometer;
  McuAxisRaw magnetometer_covariance;
} McuImuData;

typedef struct {
  float voltage;
  float current;
} McuPower;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char type;
  uint32_t response_time;
  McuDof transform;
  McuDof forward_kinematic;
  float motors_target_velocity[API_MOTOR_COUNT];
  float motors_desire_velocity[API_MOTOR_COUNT];
  float motors_actual_velocity[API_MOTOR_COUNT];
  uint32_t motors_ccr[API_MOTOR_COUNT];
  McuPower battery1;
  McuPower battery2;
  bool software_emergency_stop_enabled;
  bool hardware_emergency_stop_enabled;
  bool battery_low_emergency_stop_enabled;
  McuImuData imu;
  
  // APA102 LED状态
  uint8_t led_count;                    // LED数量
  bool led_animation_enabled;           // 动画是否启用
  
  // 电机模式状态 (0=运行, 1=刹车, 2=coast)
  uint8_t motor_modes[API_MOTOR_COUNT];
  
  uint8_t header3;
  uint8_t header4;
} McuData;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char type;
  uint32_t serial_number1;
  uint32_t serial_number2;
  uint32_t serial_number3;
  uint8_t header3;
  uint8_t header4;
} McuSerialNumber;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char type;
  float pid_speed[PID_LEVEL];
  float p[PID_LEVEL][API_MOTOR_COUNT];
  float i[PID_LEVEL][API_MOTOR_COUNT];
  float d[PID_LEVEL][API_MOTOR_COUNT];
  float motors_maximum_speed[API_MOTOR_COUNT];
  uint8_t header3;
  uint8_t header4;
} McuPid;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char type;
  float hard_iron_max[3];
  float hard_iron_min[3];
  float soft_iron_matrix[9];
  uint8_t header3;
  uint8_t header4;
} McuMagCalibrationData;

// Encoder PPR data response (MCU to PC)
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char type;
  uint32_t ppr;
  uint8_t header3;
  uint8_t header4;
} McuEncoderPpr;

/*
 * PC to MCU communication
 */

// Emergency stop
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  bool enable;
} McuSoftwareEmergencyStopCommand;

// Motor control
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  McuDof velocity;
} McuInverseKinematicsCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  uint8_t motor;
  float velocity;
} McuMotorCommand;

// PID control
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  float pid_speed[PID_LEVEL];
} McuSetPidSpeedCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
} McuGetPidCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  uint8_t motor;
  uint8_t level;
  float p;
  float i;
  float d;
} McuSetPidCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  float speed[API_MOTOR_COUNT];
} McuSetMotorMaximumSpeedCommand;

// Mag
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  float hard_iron_max[3];
  float hard_iron_min[3];
  float soft_iron_matrix[9];
} McuSetMagCalibrationDataCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
} McuGetMagCalibrationDataCommand;

// Encoder PPR commands (PC to MCU)
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
} McuGetEncoderPprCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  uint32_t ppr;
} McuSetEncoderPprCommand;


// Auto Brake Configuration response (MCU to PC)
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char type;
  uint8_t enabled;        // 0=disabled, 1=enabled
  uint32_t timeout_ms;    // timeout in milliseconds
  uint8_t header3;
  uint8_t header4;
} McuAutoBrakeConfig;

// Auto Brake commands (PC to MCU)
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
} McuGetAutoBrakeConfigCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  uint8_t enabled;      // 0=disabled, 1=enabled
} McuSetAutoBrakeEnabledCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  uint32_t timeout_ms;  // timeout in milliseconds
} McuSetAutoBrakeTimeoutCommand;

// Configuration
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
} McuSaveConfigurationCommand;

// Other
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
} McuGetSerialNumberCommand;

typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
} McuResetTransformCommand;

// 电机刹车/Coast命令
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  uint8_t mode;         // 0=单个刹车, 1=全部刹车, 2=单个coast, 3=全部coast
  uint8_t motor;        // 电机索引�?-3），全部操作时忽�?
} McuMotorBrakeCommand;

// LED灯带控制命令
typedef struct {
  uint8_t header1;
  uint8_t header2;
  char command;
  uint8_t operation;    // 0=设置单个, 1=设置全部, 2=清除, 3=获取数量, 4=启用动画
  uint8_t index;        // LED索引（仅operation=0时使用）
  uint8_t r;            // 红色分量
  uint8_t g;            // 绿色分量
  uint8_t b;            // 蓝色分量
  uint8_t enable;       // 启用/禁用（仅operation=4时使用）
} McuLedControlCommand;

#pragma pack(pop)

#endif