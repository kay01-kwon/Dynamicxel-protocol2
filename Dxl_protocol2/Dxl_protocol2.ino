#include "Dxl_protocol2.h"
#include <avr/io.h>
#include <avr/delay.h>

/** Arduino mega **/
/** Control Pin number : 11 **/
/** Rx Pin number      : 15 **/
/** Tx Pin number      : 14 **/

dxl_protocol2 dxl_pro2;

void setup() {
  Serial.begin(9600);
  dxl_pro2.init_port();
  
  /** Torque Off to write EEPROM **/
  dxl_pro2.torque_en(ID1,0);
//  dxl_pro2.torque_en(ID2,0);
//  dxl_pro2.torque_en(ID3,0);

 /* Trapzoidal velocity profile */
  dxl_pro2.profile_acc(ID1,1);
  dxl_pro2.profile_vel(ID1,1);
  
  /** mode : Extended Position Control mode : 4 **/
  dxl_pro2.op_mode(ID1,1);
//  dxl_pro2.op_mode(ID2,4);
//  dxl_pro2.op_mode(ID3,4);
  
  /** Status packet setting
   *  Return status packet only on read instruction
  **/
  dxl_pro2.status_return_level(ID1,1);
//  dxl_pro2.status_return_level(ID2,1);
//  dxl_pro2.status_return_level(ID3,1);
    
 /** Torque On to activate the motor **/
  dxl_pro2.torque_en(ID1,1);
//  dxl_pro2.torque_en(ID2,1);
//  dxl_pro2.torque_en(ID3,1);

}


void loop() {

  Serial.print("Input :");
  dxl_pro2.wait();
  float input1 = Serial.parseFloat();
  Serial.println(input1);
  dxl_pro2.goal_vel(ID1,input1);
  Serial.println("");
}
