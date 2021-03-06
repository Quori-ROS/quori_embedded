/*
 * safe_brushless_drive_client.hpp
 *
 *  Created on: May 5, 2017
 *      Author: Matthew Piccoli
 */

#ifndef PENN_ECOSYSTEM_HAL_COMMON_CPP_INC_SAFE_BRUSHLESS_DRIVE_CLIENT_HPP_
#define PENN_ECOSYSTEM_HAL_COMMON_CPP_INC_SAFE_BRUSHLESS_DRIVE_CLIENT_HPP_


#include "communication_interface.h"
#include "client_communication.hpp"

//TODO::Cleanup then include common_message_types and delete the below line
const uint8_t kTypeBrushlessDrive = 50;

class SafeBruhslessDriveClient: public ClientAbstract{
  public:
    SafeBruhslessDriveClient(uint8_t obj_idn):
      ClientAbstract(     kTypeBrushlessDrive, obj_idn),
      drive_mode_(        kTypeBrushlessDrive, obj_idn, kSubDriveMode),
      drive_phase_pwm_(   kTypeBrushlessDrive, obj_idn, kSubDrivePhasePwm),
      drive_phase_volts_( kTypeBrushlessDrive, obj_idn, kSubDrivePhaseVolts),
      drive_spin_pwm_(    kTypeBrushlessDrive, obj_idn, kSubDriveSpinPwm),
      drive_spin_volts_(  kTypeBrushlessDrive, obj_idn, kSubDriveSpinVolts),
      drive_brake_(       kTypeBrushlessDrive, obj_idn, kSubDriveBrake),
      drive_coast_(       kTypeBrushlessDrive, obj_idn, kSubDriveCoast),
      drive_angle_offset_(kTypeBrushlessDrive, obj_idn, kSubDriveAngleOffset),
      drive_pwm_(         kTypeBrushlessDrive, obj_idn, kSubDrivePwm),
      drive_volts_(       kTypeBrushlessDrive, obj_idn, kSubDriveVolts),
      mech_lead_angle_(   kTypeBrushlessDrive, obj_idn, kSubMechLeadAngle),
      obs_supply_volts_(  kTypeBrushlessDrive, obj_idn, kSubObsSupplyVolts),
      obs_angle_(         kTypeBrushlessDrive, obj_idn, kSubObsAngle),
      obs_velocity_(      kTypeBrushlessDrive, obj_idn, kSubObsVelocity),
      motor_pole_pairs_(  kTypeBrushlessDrive, obj_idn, kSubMotorPolePairs),
      motor_emf_shape_(   kTypeBrushlessDrive, obj_idn, kSubMotorEmfShape),
      permute_wires_(     kTypeBrushlessDrive, obj_idn, kSubPermuteWires),
      calibration_angle_( kTypeBrushlessDrive, obj_idn, kSubOCalibrationAngle),
      lead_time_(         kTypeBrushlessDrive, obj_idn, kSubLeadTime),
      commutation_hz_(    kTypeBrushlessDrive, obj_idn, kSubCommutationHz),
      phase_angle_(       kTypeBrushlessDrive, obj_idn, kSubPhaseAngle),
      motor_Kv_(          kTypeBrushlessDrive, obj_idn, kSubMotorKv),
      motor_R_ohm_(       kTypeBrushlessDrive, obj_idn, kSubMotorROhm),
      motor_I_max_(       kTypeBrushlessDrive, obj_idn, kSubMotorIMax),
      volts_limit_(       kTypeBrushlessDrive, obj_idn, kSubVoltsLimit),
      est_motor_amps_(    kTypeBrushlessDrive, obj_idn, kSubEstMotorAmps),
      est_motor_torque_(  kTypeBrushlessDrive, obj_idn, kSubEstMotorTorque)
      {};

    // Client Entries
    // Drive values
    ClientEntry<uint8_t>    drive_mode_;
    ClientEntry<float>      drive_phase_pwm_;
    ClientEntry<float>      drive_phase_volts_;
    ClientEntry<float>      drive_spin_pwm_;
    ClientEntry<float>      drive_spin_volts_;
    ClientEntryVoid         drive_brake_;
    ClientEntryVoid         drive_coast_;
    ClientEntry<float>      drive_angle_offset_;
    ClientEntry<float>      drive_pwm_;
    ClientEntry<float>      drive_volts_;
    ClientEntry<float>      mech_lead_angle_;
    // Measurements
    ClientEntry<float>      obs_supply_volts_;
    ClientEntry<float>      obs_angle_;
    ClientEntry<float>      obs_velocity_;
    // Motor parameters
    ClientEntry<uint16_t>   motor_pole_pairs_;
    ClientEntry<uint8_t>    motor_emf_shape_;
    // Drive configuration
    ClientEntry<uint8_t>    permute_wires_;
    ClientEntry<float>      calibration_angle_;
    ClientEntry<float>      lead_time_;
    ClientEntry<uint32_t>   commutation_hz_;
    // Fixed phase angle
    ClientEntry<float>      phase_angle_;
    // More motor parameters
    ClientEntry<float>      motor_Kv_;
    ClientEntry<float>      motor_R_ohm_;
    ClientEntry<float>      motor_I_max_;
    ClientEntry<float>      volts_limit_;
    ClientEntry<float>      est_motor_amps_;
    ClientEntry<float>      est_motor_torque_;

    void ReadMsg(CommunicationInterface& com,
      uint8_t* rx_data, uint8_t rx_length)
    {
      static const uint8_t kEntryLength = kSubEstMotorTorque+1;
      ClientEntryAbstract* entry_array[kEntryLength] = {
        &drive_mode_,           // 0
        &drive_phase_pwm_,      // 1
        &drive_phase_volts_,    // 2
        &drive_spin_pwm_,       // 3
        &drive_spin_volts_,     // 4
        &drive_brake_,          // 5
        &drive_coast_,          // 6
        &drive_angle_offset_,   // 7
        &drive_pwm_,            // 8
        &drive_volts_,          // 9
        &mech_lead_angle_,      // 10
        &obs_supply_volts_,     // 11
        &obs_angle_,            // 12
        &obs_velocity_,         // 13
        &motor_pole_pairs_,     // 14
        &motor_emf_shape_,      // 15
        &permute_wires_,        // 16
        &calibration_angle_,    // 17
        &lead_time_,            // 18
        &commutation_hz_,       // 19
        &phase_angle_,          // 20
        nullptr,                // 21
        nullptr,                // 22
        nullptr,                // 23
        nullptr,                // 24
        nullptr,                // 25
        nullptr,                // 26
        nullptr,                // 27
        nullptr,                // 28
        nullptr,                // 29
        nullptr,                // 30
        nullptr,                // 31
        &motor_Kv_,             // 32
        &motor_R_ohm_,          // 33
        &motor_I_max_,          // 34
        &volts_limit_,          // 35
        &est_motor_amps_,       // 36
        &est_motor_torque_      // 37
      };

      ParseMsg(rx_data, rx_length, entry_array, kEntryLength);
    }

  private:
    static const uint8_t kSubDriveMode        = 0;
    static const uint8_t kSubDrivePhasePwm    = 1;
    static const uint8_t kSubDrivePhaseVolts  = 2;
    static const uint8_t kSubDriveSpinPwm     = 3;
    static const uint8_t kSubDriveSpinVolts   = 4;
    static const uint8_t kSubDriveBrake       = 5;
    static const uint8_t kSubDriveCoast       = 6;
    static const uint8_t kSubDriveAngleOffset = 7;
    static const uint8_t kSubDrivePwm         = 8;
    static const uint8_t kSubDriveVolts       = 9;
    static const uint8_t kSubMechLeadAngle    = 10;
    static const uint8_t kSubObsSupplyVolts   = 11;
    static const uint8_t kSubObsAngle         = 12;
    static const uint8_t kSubObsVelocity      = 13;
    static const uint8_t kSubMotorPolePairs   = 14;
    static const uint8_t kSubMotorEmfShape    = 15;
    static const uint8_t kSubPermuteWires     = 16;
    static const uint8_t kSubOCalibrationAngle= 17;
    static const uint8_t kSubLeadTime         = 18;
    static const uint8_t kSubCommutationHz    = 19;
    static const uint8_t kSubPhaseAngle       = 20;
    static const uint8_t kSubMotorKv          = 32;
    static const uint8_t kSubMotorROhm        = 33;
    static const uint8_t kSubMotorIMax        = 34;
    static const uint8_t kSubVoltsLimit       = 35;
    static const uint8_t kSubEstMotorAmps     = 36;
    static const uint8_t kSubEstMotorTorque   = 37;
};



#endif /* PENN_ECOSYSTEM_HAL_COMMON_CPP_INC_SAFE_BRUSHLESS_DRIVE_CLIENT_HPP_ */
