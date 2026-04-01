// This file is part of Necroware's GamePort adapter firmware.
// Copyright (C) 2021 Necroware
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "AnalogJoystick.h"
#include "Joystick.h"

class CHProPedals : public Joystick {
public:
  const Description &getDescription() const override {
    // CH Products Pro Pedals - 1994
    static const Description description{"CH Pro Pedals", 5, 0, 0};
    /// INTENDED CONFIGURATION for this driver!!
    /// Connector labeled "AUX PORT" into connector labeled "JOYSTICK".
    /// Switch on the pedal set to "PLANE" and not "CAR".
    ///
    /// Setting it to "CAR" will only disable the Rudder functionality.
    /// Changing the switch position after the adapter is powered on
    /// will mess up with the calibration of the axis.
    return description;
  }

  const State &getState() const override {
    return m_state;
  }

  bool init() override {  
    return true;
  }


  bool update() override {
    /// Assigning axes as Joystick type might cause problems.
    m_state.axes[0] = 512; // Hardcoded centered Joystick
    m_state.axes[1] = 512; // Hardcoded centered Joystick
    /// Make sure the switch on the pedal is set to "PLANE" and not "CAR".
    m_state.axes[2] = m_joystick.getAxis(2); // Rudder
    m_state.axes[3] = m_joystick.getAxis(0); // Left Toe Brake
    m_state.axes[4] = m_joystick.getAxis(1); // Right Toe Brake
    //m_state.axes[3] = m_joystick.getSlider(0); //  Slider implementation - PR pending
    //m_state.axes[4] = m_joystick.getSlider(1); //  Slider implementation - PR pending
  
    log("Code %d : %d , A2 %d", code, m_state.buttons, m_state.axes[2] );
    return true;
  }

private:
  AnalogJoystick m_joystick;
  State m_state;
};
