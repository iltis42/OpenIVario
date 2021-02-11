/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************

File: Compass.h

Class to handle compass data access.

Author: Axel Pauli, January 2021

Last update: 2021-02-11

**************************************************************************/

#pragma once

#include "SetupNG.h"
#include "QMC5883L.h"

class Compass : public QMC5883L
{
public:

  /*
    Creates instance for I2C connection with passing the desired parameters.
    No action is done at the bus. Note if i2cBus is not set in the constructor,
    you have to set it by calling method setBus(). The default address of the
    chip is 0x0D.
   */
  Compass( const uint8_t addr,
           const uint8_t odr,
           const uint8_t range,
           const uint16_t osr,
           I2C_t *i2cBus=nullptr );

  ~Compass();

  /**
   * Returns the heading by considering deviation and declination. If ok is
   * passed, it is set to true, if heading data is valid, otherwise it is set
   * to false.
   */
  float trueHeading( bool *okIn=nullptr );

  /**
   * Returns the magnetic heading by considering deviation and declination.
   * If ok is passed, it is set to true, if heading data is valid, otherwise
   * it is set to false.
   */
  float magneticHeading( bool *okIn=nullptr );

  /**
   * Calibrate compass by using the read x, y, z raw values. The calibration
   * duration is passed as seconds.
   */
  bool calibrate( const uint16_t seconds );

private:

  static SetupNG<float> *deviations[8];
};
