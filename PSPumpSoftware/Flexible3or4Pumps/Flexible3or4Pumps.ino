    ////////////////////////////////////////////////////////////////////
    ///////////////////Syringepump controller///////////////////////////
    ////////for teensy 3.1 or 3.2, and stepper drivers based//////////// 
    //and a OSC (open sound control) based frontend in pure data (PD)///
    ////////////////////////////////////////////////////////////////////

    // This version is 'flexible' - all variables (syr. diameter, motor, leadscrew, microstepping etc.)
    // are defined in the PD-frontend
    
    /*
    Electronics:
    -stepper boards are based on the Allegro A4988 stepper driver chip
    
    -enable must be low (ground)
    -MS1, MS2, MS3..if not connected they are pulled high (means it defaults to sixteenth step microstepping) 
    -GND together with teensy
    -step high/low ... minimum 1 microsecond required
    
    -WIRING:
    TEENSY pin
    
    pump0
    PIN 2 DIR
    PIN 3 STEP
    
    pump1
    PIN5 DIR
    PIN6 STEP
    
    pump2
    PIN8 DIR
    PIN9 STEP
    
    pump3
    PIN11 DIR  
    PIN12 STEP   


    How it works:
    The delaytime (delayUS) in microseconds ('inValue') and the direction (clockwise/counterclockwise, 'inDirection') 
    for all four pumps is transferred from the PD-frontend to the microcontroller via the OSC (Open Sound Control) protocol.
    If the microcontroller received a set of values it will send them back to PD, where it is used to 
    confirm that the communication works.

    The delaytime (specific to a given flowrate and the other parameters (syringe diameter, motors, microsteps, leadscrew)) 
    defines when a step has to be performed and is calculated entirely in the PD-frontend.

    If a step is due is determined by jumping into an interrupt every 10 microseconds. 
    If so, the step-pin is pulled high for 1 microsecond, then pulled low again.

    
    -This program is licensed under The MIT License (https://opensource.org/licenses/MIT), Copyright (c) 2016, Martin Fischlechner,
    with the exception of the code-blocks for initializing, receiving and sending OSC-messages, which were copied from https://github.com/CNMAT/OSC/tree/master/examples
    and have the following, similarly liberal, license: [the code-blocks are marked //&&; //&&] 
    
    The Center for New Music and Audio Technologies,
    University of California, Berkeley.  Copyright (c) 2008-14, The Regents of
    the University of California (Regents). 
    Permission to use, copy, modify, distribute, and distribute modified versions
    of this software and its documentation without fee and without a signed
    licensing agreement, is hereby granted, provided that the above copyright
    notice, this paragraph and the following two paragraphs appear in all copies,
    modifications, and distributions.

    IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
    SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
    OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
    BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
    HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
    MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS. 
    */
    
    //library for interrupt
    #include <TimerOne.h>
    ///libraries and code for OSC communication
    #include <OSCBundle.h>
    #include <OSCBoards.h>

    //&&
    #ifdef BOARD_HAS_USB_SERIAL
    #include <SLIPEncodedUSBSerial.h>
    SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
    #else
    #include <SLIPEncodedSerial.h>
     SLIPEncodedSerial SLIPSerial(Serial);
    #endif
    //&& 
    
    ////// define variables////////
    
    ////////Volatile variables needed if in interrupt//////
    volatile unsigned long timer = 0; // timer counter for pump0
    volatile unsigned long timer1 = 0; // timer counter for pump1
    volatile unsigned long timer2 = 0; // timer counter for pump2
    volatile unsigned long timer3 = 0; // timer counter for pump3 
    
    volatile unsigned long counter = 0;//counter and counter1 help in interrupt to adjust for 1us delay times while stepping a pump
    volatile unsigned long counter1 = 0;
    
    volatile unsigned long delayUS = 100000; // delay timer, could this also be 0 for the start, or a high number so that it doesn't squeak when powering up?
    volatile unsigned long delayUS1 = 100000; // delay timer
    volatile unsigned long delayUS2 = 100000; // delay timer
    volatile unsigned long delayUS3 = 100000; // delay timer
    
    ///////SLIPserial/ OSC ///////
    int32_t inDirection = 0;     // pump0 incoming OSC direction (first received integer)
    int32_t inValue = 0;         // pump0 incoming OSC flowrate (second received integer)
    
    int32_t inDirection1 = 0;     // pump1 incoming OSC direction (third received integer)
    int32_t inValue1 = 0;         // pump1 incoming OSC flowrate (fourth received integer)
    
    int32_t inDirection2 = 0;     // pump2 incoming OSC direction (fifth received integer)
    int32_t inValue2 = 0;         // pump2 incoming OSC flowrate (sixth received integer)
    
    int32_t inDirection3 = 0;     // pump3 incoming OSC direction (seventh received integer)
    int32_t inValue3 = 0;         // pump3 incoming OSC flowrate (eighth received integer)
    
    
    
    
    //////normal variables////
    int enableDrive = 1; //if enabled timer can tick
    int directionInState = 0; //direction pump0
    int directionInState1 = 0; //direction pump1
    int directionInState2 = 0; //direction pump2
    int directionInState3 = 0; //direction pump3
       
    
    //pins
    const int steppin = 3;  // pump0; the pin that is used for making the nema-motor step
    const int directionpin = 2; // pump0; the pin that lets the stepper board know which direction to step
    
    const int steppin1 = 6;  // pump1
    const int directionpin1 = 5; // pump1
    
    const int steppin2 = 9;  // pump2
    const int directionpin2 = 8; // pump2
    
    const int steppin3 = 12;  // pump3
    const int directionpin3 = 11; // pump3
    
    void setup(void)
    {
      ///// setup the pins to input or output
      
      pinMode(directionpin, OUTPUT); // pump0; direction out to drive board
      pinMode(steppin, OUTPUT); // pump0; pin that does the stepping
      
      pinMode(directionpin1, OUTPUT); // pump1; 
      pinMode(steppin1, OUTPUT); // pump1; 
      
      pinMode(directionpin2, OUTPUT); // pump2; 
      pinMode(steppin2, OUTPUT); // pump2; 
      
      pinMode(directionpin3, OUTPUT); // pump3; 
      pinMode(steppin3, OUTPUT); // pump3; 
      
      //initialize timer
      Timer1.initialize(10);//interrupt will occur every 10 microseconds
      Timer1.attachInterrupt(clickmove); // clickmove will run every 10 microseconds

      //&&
      // initialize SLIPserial communications:
      //begin SLIPSerial just like Serial
      SLIPSerial.begin(115200);   // set this as high as you can reliably run on your platform
      #if ARDUINO >= 100
          while(!Serial)
            ;   // Leonardo bug
      #endif 
      //&&
    }
    
    /////////////////////////////////////////
    /////this is the interrupt///////////////
    ////which runs every 10 microseconds/////
    /////////////////////////////////////////
    
    void clickmove(void)
    {
      
      //pump0
       if(timer+counter1 >= delayUS) ///counter1 has the number of stepping occurances from last cycle (every step 'costs' one us)
          {
          if(enableDrive==1)
            {
              digitalWrite(steppin, 1); //step-pin on
            } //could use digitalWriteFast library here
          delayMicroseconds(1);
          digitalWrite(steppin, 0); //step-pin off, should I use digitalwritefast here?
          timer=0; //sets time for this pump to 0 when stepped
          counter=counter+1; ///if steppin is triggered it waits for 1us
         }
         timer=timer+10; //this counts timer up in '10usecond steps' every time the interrupt runs and compares delayUS with it
        
      //pump1
       if(timer1+counter1 >= delayUS1) 
          {
          if(enableDrive==1)
            {
              digitalWrite(steppin1, 1); //step-pin on
            } 
          delayMicroseconds(1);
          digitalWrite(steppin1, 0); //step-pin off
          timer1=0;  
          counter=counter+1;    
         }
         timer1=timer1+10;
     
      //pump2
       if(timer2+counter1 >= delayUS2) 
          {
          if(enableDrive==1)
            {
              digitalWrite(steppin2, 1); //step-pin on
            } 
          delayMicroseconds(1);
          digitalWrite(steppin2, 0); //step-pin off
          timer2=0;   
          counter=counter+1;     
         }
         timer2=timer2+10;
         
      //pump3
       if(timer3+counter1 >= delayUS3) 
          {
          if(enableDrive==1)
            {
              digitalWrite(steppin3, 1); //step-pin on
            } //could use digitalWriteFast library here
          delayMicroseconds(1);
          digitalWrite(steppin3, 0); //step-pin off
          timer3=0; 
          counter=counter+1;       
         }
        timer3=timer3+10;
        counter1 = 0; //reset counter1
        counter1 = counter; //make counter1 to counter to be able to adjust timing
        counter = 0; //reset counter after every time interrupt runs
    }
    
    
    /////////////////////////////////
    ///////main loop cycle///////////
    /////////////////////////////////
    void loop(void)
    {
        //////////////////////////////////////////////////////////////////////////
        // transfer OSC values with SLIPserial to and from PD and work with it ///
        //////////////////////////////////////////////////////////////////////////

          //&&
          //OSC slipserial incoming communication
           OSCMessage messageIN(""); //left empty because the code doesn't seem to discriminate on it
             int size;
             while(!SLIPSerial.endofPacket())
             if ((size =SLIPSerial.available()) > 0)
               {
                  while(size--)
                  messageIN.fill(SLIPSerial.read());
               }
               
               if(!messageIN.hasError())
                 { 

                   //get direction and delay-values for all the pumps////////////////////////////////////////////////////////////////////////
                   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                       //pump0
                       messageIN.getInt(0); 
                       inDirection = messageIN.getInt(0); //inDirection gets first integer of received message (should only be 1 or 0)
                       messageIN.getInt(1); 
                       inValue = messageIN.getInt(1); //inValue gets second integer of received message (delaytime in microseconds)
                       //pump1
                       messageIN.getInt(2); 
                       inDirection1 = messageIN.getInt(2); 
                       messageIN.getInt(3); 
                       inValue1 = messageIN.getInt(3);
                       //pump2
                       messageIN.getInt(4); 
                       inDirection2 = messageIN.getInt(4); 
                       messageIN.getInt(5); 
                       inValue2 = messageIN.getInt(5);
                       //pump3
                       messageIN.getInt(6); 
                       inDirection3 = messageIN.getInt(6); 
                       messageIN.getInt(7); 
                       inValue3 = messageIN.getInt(7);             
                  }
               
               messageIN.empty(); ///clears message from contents
              //&&
           
          delayMicroseconds(100);//necessary? if then better put timer in based on elapsedmillis (>10) to make it slow 
         
         ///setting direction pump0
          if (inDirection == 0) {
            directionInState = 0;
          }
          else if (inDirection == 1) {
            directionInState = 1;
          }
          
          ///setting direction pump1
          if (inDirection1 == 0) {
            directionInState1 = 0;
          }
          else if (inDirection1 == 1) {
            directionInState1 = 1;
          }
          
          ///setting direction pump2
          if (inDirection2 == 0) {
            directionInState2 = 0;
          }
          else if (inDirection2 == 1) {
            directionInState2 = 1;
          }
          
          ///setting direction pump3
          if (inDirection3 == 0) {
            directionInState3 = 0;
          }
          else if (inDirection3 == 1) {
            directionInState3 = 1;
          }
          
          
          
          /////TODO for all four pumps, declare all variables at the beginning etc resulting in specific delayUS for all pumps
          
          /////calculate stepping time for all pumps
          //////////////////////////////////////////
          
          //////(pump0)/////////// 
          delayUS = long(inValue);   //this is the delay variable in microseconds for stepping which the interrupt compares time against
          
          //////(pump1)///////////  
          delayUS1 = long(inValue1);   
          
          //////(pump2)///////////  
          delayUS2 = long(inValue2);   
          
          //////(pump3)///////////  
          delayUS3 = long(inValue3);   
          
          /////////write the direction/////////////
          //pump0
          digitalWriteFast(directionpin,directionInState);
          //pump1
          digitalWriteFast(directionpin1,directionInState1);
          //pump2
          digitalWriteFast(directionpin2,directionInState2);
          //pump3
          digitalWriteFast(directionpin3,directionInState3);

          //&&
          //declare the OSC bundle to send back to PD
             OSCBundle bndlOUT;  //name of bundle that is created
             //pump0  
             bndlOUT.add("/pump0/direction").add(inDirection); 
             bndlOUT.add("/pump0/flowrate").add(inValue); 
             //pump1  
             bndlOUT.add("/pump1/direction").add(inDirection1); 
             bndlOUT.add("/pump1/flowrate").add(inValue1);
             //pump2  
             bndlOUT.add("/pump2/direction").add(inDirection2); 
             bndlOUT.add("/pump2/flowrate").add(inValue2);  
             //pump3  
             bndlOUT.add("/pump3/direction").add(inDirection3); 
             bndlOUT.add("/pump3/flowrate").add(inValue3); 
             
             SLIPSerial.beginPacket();
               bndlOUT.send(SLIPSerial); // send the bytes to the SLIP stream
             SLIPSerial.endPacket(); // mark the end of the OSC Packet
               bndlOUT.empty(); // empty the bundle to free room for a new one
             //&&
          
          delayMicroseconds(100); // necessary? better put timer in based on elapsedmillis to make it slow
          
    }
    
    ////////////////////////////
    /////end of main loop///////
    ////////////////////////////
