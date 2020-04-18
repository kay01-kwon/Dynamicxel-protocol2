#include "Dxl_protocol2.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/** Control Pin Set and Clear **/
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

/** Functions **/

void dxl_protocol2::init_port(){
  Serial3.begin(57600);
  PORTB = 0x00;
  DDRB = 0xFF;
  _serial=&Serial3;
}

void dxl_protocol2::wait(){
  while(!Serial.available()){
  }
}

void dxl_protocol2::factory_reset(byte id){
  byte CRC_L;
  byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R
  ,id,0x04,0x00,FacReset,0x01,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,9);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;  
  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write((byte)0x04);
  _serial->write((byte)0x00);
  _serial->write((byte)FacReset);
  _serial->write((byte)0x01);
  _serial->write((byte)CRC_L);
  _serial->write((byte)CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}

void dxl_protocol2::op_mode(byte id,unsigned int mode){
  byte CRC_L;
  byte CRC_H;
  byte op_L = lowByte(Operating_Mode);
  byte op_H = highByte(Operating_Mode);
  
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x07,0x00,Write,op_L,op_H,mode,0x00,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,12);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;

  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write((byte)0x07);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write((byte)op_L);
  _serial->write((byte)op_H);
  _serial->write((byte)mode);
  _serial->write((byte)0x00);
  _serial->write((byte)CRC_L);
  _serial->write((byte)CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}

void dxl_protocol2::profile_acc(byte id, unsigned int mode){
  byte CRC_L;
  byte CRC_H;
  
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x07,0x00,Write,Prof_acc,0x00,mode,0x00,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,12);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;

  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write((byte)0x07);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write(Prof_acc);
  _serial->write((byte)0x00);
  _serial->write((byte)mode);
  _serial->write((byte)0x00);
  _serial->write((byte)CRC_L);
  _serial->write((byte)CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}


void dxl_protocol2::profile_vel(byte id, unsigned int mode){
  byte CRC_L;
  byte CRC_H;
  
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x07,0x00,Write,Prof_vel,0x00,mode,0x00,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,12);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;

  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write((byte)0x07);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write(Prof_vel);
  _serial->write((byte)0x00);
  _serial->write((byte)mode);
  _serial->write((byte)0x00);
  _serial->write((byte)CRC_L);
  _serial->write((byte)CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}

void dxl_protocol2::status_return_level(byte id,unsigned int mode){
  byte CRC_L;
  byte CRC_H;
  
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x06,0x00,Write,Status_return,0x00,mode,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,11);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;

  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write((byte)0x06);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write(Status_return);
  _serial->write((byte)0x00);
  _serial->write((byte)mode);
  _serial->write((byte)CRC_L);
  _serial->write((byte)CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}

void dxl_protocol2::torque_en(byte id,unsigned int input){
  byte On_Off=0x00;
  byte CRC_L;
  byte CRC_H;
  if (input == 1){
    On_Off=0x01;
  }
  unsigned short TxPacket[] = {H1,H2,H3,R
  ,id,0x06,0x00,Write,Torque_en,0x00,On_Off,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,11);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;

  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3); 
  _serial->write(R);
  _serial->write(id);
  _serial->write((byte)0x06);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write(Torque_en);
  _serial->write((byte)0x00);
  _serial->write(On_Off);
  _serial->write((byte)CRC_L);
  _serial->write((byte)CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}

void dxl_protocol2::pos_move(byte id,float x){
  int32_t y = x/0.088;    
  byte x_1st = lowByte(y);
  byte x_2nd = highByte(y);
  byte x_3rd = lowByte(y>>16);
  byte x_4th = highByte(y>>16);
  byte CRC_L;
  byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R,id,0x09
  ,0x00,Write,Goal_pos,0x00,x_1st,x_2nd,x_3rd,x_4th,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,14);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;

  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write(0x09);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write(Goal_pos);
  _serial->write((byte)0x00);
  _serial->write(x_1st);
  _serial->write(x_2nd);
  _serial->write(x_3rd);
  _serial->write(x_4th);
  _serial->write(CRC_L);
  _serial->write(CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  Serial.println("Move");
}

void dxl_protocol2::goal_vel(byte id,float vel){
   byte CRC_L;
   byte CRC_H;
   vel = vel/1.374;
  int32_t gvel = vel;    /* 1.374deg/sec */
  byte gvel_1st = lowByte(gvel);
  byte gvel_2nd = highByte(gvel);
  byte gvel_3rd = lowByte(gvel>>16);
  byte gvel_4th = highByte(gvel>>16);
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x09,0x00,Write,Goal_vel,0x00,gvel_1st,gvel_2nd
  ,gvel_3rd,gvel_4th
  ,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,14);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;
  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write(0x09);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write(Goal_vel);
  _serial->write((byte)0x00);
  _serial->write(gvel_1st);
  _serial->write(gvel_2nd);
  _serial->write(gvel_3rd);
  _serial->write(gvel_4th);  
  _serial->write(CRC_L);
  _serial->write(CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);    
}

void dxl_protocol2::sync_pos_move2(byte id1,float x1,byte id2, float x2){
  int32_t y1 = x1/0.088;    
  byte x1_1st = lowByte(y1);
  byte x1_2nd = highByte(y1);
  byte x1_3rd = lowByte(y1>>16);
  byte x1_4th = highByte(y1>>16);
  
  int32_t y2 = x2/0.088;    
  byte x2_1st = lowByte(y2);
  byte x2_2nd = highByte(y2);
  byte x2_3rd = lowByte(y2>>16);
  byte x2_4th = highByte(y2>>16);

  byte CRC_L;
  byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R,Broadcast_ID
  ,0x11,0x00,SyncWrite,Goal_pos,0x00
  ,0x04,0x00,id1,x1_1st,x1_2nd,x1_3rd,x1_4th
  ,id2,x2_1st,x2_2nd,x2_3rd,x2_4th,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,22);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;

  
  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(Broadcast_ID);
  
  _serial->write((byte)0x11);
  _serial->write((byte)0x00);
  _serial->write(SyncWrite);
  _serial->write(Goal_pos);
  _serial->write((byte)0x00);
  
  _serial->write((byte)0x04);
  _serial->write((byte)0x00);
  _serial->write(id1);
  _serial->write(x1_1st);
  _serial->write(x1_2nd);
  _serial->write(x1_3rd);
  _serial->write(x1_4th);

  _serial->write(id2);
  _serial->write(x2_1st);
  _serial->write(x2_2nd);
  _serial->write(x2_3rd);
  _serial->write(x2_4th);
  _serial->write(CRC_L);
  _serial->write(CRC_H);  
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}

void dxl_protocol2::sync_pos_move3(byte id1,float x1,byte id2, float x2,byte id3, float x3){
  int32_t y1 = x1/0.088;    
  byte x1_1st = lowByte(y1);
  byte x1_2nd = highByte(y1);
  byte x1_3rd = lowByte(y1>>16);
  byte x1_4th = highByte(y1>>16);
  
  int32_t y2 = x2/0.088;    
  byte x2_1st = lowByte(y2);
  byte x2_2nd = highByte(y2);
  byte x2_3rd = lowByte(y2>>16);
  byte x2_4th = highByte(y2>>16);

  
  int32_t y3 = x3/0.088;    
  byte x3_1st = lowByte(y3);
  byte x3_2nd = highByte(y3);
  byte x3_3rd = lowByte(y3>>16);
  byte x3_4th = highByte(y3>>16);
  
  byte CRC_L;
  byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R,Broadcast_ID
  ,0x16,0x00,SyncWrite,Goal_pos,0x00
  ,0x04,0x00,id1,x1_1st,x1_2nd,x1_3rd,x1_4th
  ,id2,x2_1st,x2_2nd,x2_3rd,x2_4th
  ,id3,x3_1st,x3_2nd,x3_3rd,x3_4th,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,27);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;

  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(Broadcast_ID);
  
  _serial->write((byte)0x16);
  _serial->write((byte)0x00);
  _serial->write(SyncWrite);
  _serial->write(Goal_pos);
  _serial->write((byte)0x00);
  
  _serial->write((byte)0x04);
  _serial->write((byte)0x00);
  _serial->write(id1);
  _serial->write(x1_1st);
  _serial->write(x1_2nd);
  _serial->write(x1_3rd);
  _serial->write(x1_4th);
  
  _serial->write(id2);
  _serial->write(x2_1st);
  _serial->write(x2_2nd);
  _serial->write(x2_3rd);
  _serial->write(x2_4th);

  _serial->write(id3);
  _serial->write(x3_1st);
  _serial->write(x3_2nd);
  _serial->write(x3_3rd);
  _serial->write(x3_4th);
  
  _serial->write(CRC_L);
  _serial->write(CRC_H);  
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}


/** Read data **/

void dxl_protocol2::moving_status(byte id){
   byte CRC_L;
   byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x07,0x00,Read,Moving,0x00,0x01,0x00
  ,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,12);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;
  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write(0x07);
  _serial->write((byte)0x00);
  _serial->write(Read);
  _serial->write(Moving);
  _serial->write((byte)0x00);
  _serial->write((byte)0x01);
  _serial->write((byte)0x00);  
  _serial->write(CRC_L);
  _serial->write(CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
}


/* Read data */


float dxl_protocol2::read_present_pos(byte id){
   byte CRC_L;
   byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x07,0x00,Read,Pres_pos,0x00,0x04,0x00
  ,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,12);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;
  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write((byte)R);
  _serial->write(id);
  _serial->write(0x07);
  _serial->write((byte)0x00);
  _serial->write(Read);
  _serial->write(Pres_pos);
  _serial->write((byte)0x00);
  _serial->write(0x04);
  _serial->write((byte)0x00);  
  _serial->write(CRC_L);
  _serial->write(CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
  return read_byte_pos(15);
}



int dxl_protocol2::read_present_vel(byte id){
   byte CRC_L;
   byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x07,0x00,Read,Pres_vel,0x00,0x04,0x00
  ,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,12);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;
  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write((byte)R);
  _serial->write(id);
  _serial->write(0x07);
  _serial->write((byte)0x00);
  _serial->write(Read);
  _serial->write(Pres_vel);
  _serial->write((byte)0x00);
  _serial->write(0x04);
  _serial->write((byte)0x00);  
  _serial->write(CRC_L);
  _serial->write(CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  _delay_ms(10);
  return read_byte_vel(15);
}

float dxl_protocol2::read_byte_pos(int n){
  _delay_ms(10);
  while(!_serial->available()){    
  }
  byte data[n];
  int32_t result=0;
  int index=1;
_delay_ms(10);
while(_serial->available()){
    byte leng = _serial->readBytes(data,n);
      if(index==n) break;
      index++;
    }
    for(int i=0;i<n;i++){
      Serial.print(data[i],HEX);
      Serial.print(" ");
    }
    Serial.println();
    data[9] = (int32_t) data[9];
    data[10] = (int32_t) data[10];
    data[11] = (int32_t) data[11];
    data[12] = (int32_t) data[12];
    result = data[9] + (data[10]<<8) + (data[11]<<16) + (data[11]<<24);
    return result*0.088;
    
}


int dxl_protocol2::read_byte_vel(int n){
  _delay_ms(10);
  while(!_serial->available()){    
  }
  byte data[n];
  int result=0;
  int index=1;
_delay_ms(10);
while(_serial->available()){
    byte leng = _serial->readBytes(data,n);
      if(index==n) break;
      index++;
    }
    for(int i=0;i<n;i++){
      Serial.print(data[i],HEX);
      Serial.print(" ");
    }
    Serial.println();

    /*For velocity profile reading */
    /* Velocity >0 : return 1 / Velocity=0 : return 0 */
    if(data[9]==0 && data[10] ==0 && data[11]==0 && data[12]==0){
    return result=0;
    }else{
      return result=1;
    }
}

void dxl_protocol2::homing_offset(byte id, float x){
  int32_t y =  x/0.088;    
  byte x_1st = lowByte(y);
  byte x_2nd = highByte(y);
  byte x_3rd = lowByte(y>>16);
  byte x_4th = highByte(y>>16);
  
   byte CRC_L;
   byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x09,0x00,Write,Homing_offset,0x00,x_1st,x_2nd
  ,x_3rd,x_4th,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,14);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;
  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write(0x09);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write(Homing_offset);
  _serial->write((byte)0x00);
  _serial->write(x_1st);
  _serial->write(x_2nd);
  _serial->write(x_3rd);
  _serial->write(x_4th);  
  _serial->write(CRC_L);
  _serial->write(CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
  
}

void dxl_protocol2::pwm_modulate(byte id, float pwm)
{
  int32_t y1 = pwm * 100/885.0;    
  byte x_1st = lowByte(y1);
  byte x_2nd = highByte(y1);
   byte CRC_L;
   byte CRC_H;
  unsigned short TxPacket[] = {H1,H2,H3,R,id
  ,0x07,0x00,Write,PWM_lim,0x00,x_1st,x_2nd
  ,CRC_L,CRC_H};
  unsigned short CRC = update_crc(0,TxPacket,12);
  CRC_L = (CRC&0x00FF);
  CRC_H = (CRC>>8)&0x0FF;
  sbi(PORTB,PB5);
  _serial->write(H1);
  _serial->write(H2);
  _serial->write(H3);
  _serial->write(R);
  _serial->write(id);
  _serial->write(0x07);
  _serial->write((byte)0x00);
  _serial->write(Write);
  _serial->write(PWM_lim);
  _serial->write((byte)0x00);
  _serial->write(x_1st);
  _serial->write(x_2nd);  
  _serial->write(CRC_L);
  _serial->write(CRC_H);
  _serial->flush();
  cbi(PORTB,PB5);
}

/** CRC Calculation **/
unsigned short dxl_protocol2::update_crc(unsigned short crc_accum, unsigned short *data_blk_ptr, unsigned short data_blk_size){
   unsigned short i, j;
   unsigned short crc_table[256] = {
        0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
        0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
        0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
        0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
        0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
        0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
        0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
        0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
        0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
        0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
        0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
        0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
        0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
        0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
        0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
        0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
        0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
        0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
        0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
        0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
        0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
        0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
        0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
        0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
        0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
        0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
        0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
        0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
        0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
        0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
        0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
        0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
    };

    for(j = 0; j < data_blk_size; j++)
    {
        i = ((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
        crc_accum = (crc_accum << 8) ^ crc_table[i];
    }

    return crc_accum;
}
