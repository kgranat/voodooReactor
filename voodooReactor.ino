     /* 
  ArbotiX Firmware - Commander Extended Instruction Set Example
  Copyright (c) 2008-2010 Vanadium Labs LLC.  All right reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of the Vanadium Labs LLC nor the names of its 
        contributors may be used to endorse or promote products derived 
        from this software without specific prior written permission.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL VANADIUM LABS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/ 
 
#include <ax12.h>
#include <BioloidController.h>

/* Hardware Constructs */
BioloidController bioloid = BioloidController(1000000);
#define BASE    0
#define SHOULDER   1
#define ELBOW   2
#define WRIST  3
#define GRIPPER   4
#define SPEED 300

// the F2 'C' bracket attached to the tilt servo creates a physical limitation to how far
// we can move the tilt servo. This software limit will ensure that we don't jam the bracket into the servo.
#define SHOULDER_UPPER_LIMIT 800 
#define SHOULDER_LOWER_LIMIT 200

#define ELBOW_UPPER_LIMIT 868 
#define ELBOW_LOWER_LIMIT 250

#define WRIST_UPPER_LIMIT 896
#define WRIST_LOWER_LIMIT 128

//Upper/Lower limits for the pan servo - by defualt they are the normal 0-1023 (0-300) positions for the servo
#define BASE_UPPER_LIMIT 1023 
#define BASE_LOWER_LIMIT 0

#define GRIPPER_UPPER_LIMIT 512 
#define GRIPPER_LOWER_LIMIT 0


int potBaseVal, potShoulderVal, potElbowVal, potGripperVal, potWristVal;

int avgVal[5][5];

int avgReady = 0;

int avgPosition = 0;

void setup(){
 // SetPosition(WRIST,512);
 //
 Serial.begin(9600);
ax12SetRegister(8, AX_CW_COMPLIANCE_SLOPE, 128);
ax12SetRegister(8, AX_CCW_COMPLIANCE_SLOPE, 128);


//

}

void loop(){
  Serial.println(avgPosition);
  
  for(int i = 0; i < 5; i++)
  {
    
    avgVal[i][avgPosition] = analogRead(i); 
    delay(5);   
  }
  
  
  
  Serial.println(avgPosition++);
  if(avgPosition > 4)
  {
     avgReady = 1;
     avgPosition = 0;
  Serial.println("Moooo");
  }
  
  
  Serial.println("wtf");
  if(avgReady ==1)
  {
    potGripperVal = (avgVal[4][0]+ avgVal[4][1]+ avgVal[4][2]+ avgVal[4][3]+ avgVal[4][4])/5;
    potWristVal = (avgVal[3][0]+ avgVal[3][1]+ avgVal[3][2]+ avgVal[3][3]+ avgVal[3][4])/5;
    potElbowVal = (avgVal[2][0]+ avgVal[2][1]+ avgVal[2][2]+ avgVal[2][3]+ avgVal[2][4])/5;
    potShoulderVal = (avgVal[1][0]+ avgVal[1][1]+ avgVal[1][2]+ avgVal[1][3]+ avgVal[1][4])/5;
    potBaseVal = (avgVal[0][0] + avgVal[0][1] + avgVal[0][2] + avgVal[0][3] + avgVal[0][4])/5;
      
      Serial.print(avgVal[3][0]);
      Serial.print(" | ");
      Serial.print(avgVal[3][1]);
      Serial.print(" | ");
      Serial.print(avgVal[3][2]);
      Serial.print(" | ");
      Serial.print(avgVal[3][3]);
      Serial.print(" | ");
      Serial.print(avgVal[3][4]);
      Serial.print(" | ");
      
      Serial.print(potGripperVal);
      Serial.println(" | ");
    
    potGripperVal = map(potGripperVal-200, 0, 824, 0, 512);
    
    potShoulderVal = min(potShoulderVal,SHOULDER_UPPER_LIMIT);
    potShoulderVal = max(potShoulderVal,SHOULDER_LOWER_LIMIT);
    
    potElbowVal = min(potElbowVal,ELBOW_UPPER_LIMIT);
    potElbowVal = max(potElbowVal,ELBOW_LOWER_LIMIT);
    
    potGripperVal = min(potGripperVal,GRIPPER_UPPER_LIMIT);
    potGripperVal = max(potGripperVal,GRIPPER_LOWER_LIMIT);
    
    potWristVal = min(potWristVal,WRIST_UPPER_LIMIT);
    potWristVal = max(potWristVal,WRIST_LOWER_LIMIT);
      
    SetPosition(1,1023-potBaseVal);
    
    
    SetPosition(2,potShoulderVal);
    SetPosition(3,1023-potShoulderVal);
    
    SetPosition(4,potElbowVal);
    SetPosition(5,1023-potElbowVal);
    
    
    SetPosition(6,1023-potWristVal);
    SetPosition(7,512);
    SetPosition(8,1023-potGripperVal);
    
    //SetPosition(,potGripperVal);
  
    delay(15);   
  }
}


int analogAverage(int reading)
{
  
  
}




