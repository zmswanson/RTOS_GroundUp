/**
*    Project: Build Your Own RTOS from Ground Up
*    Author: Zach Swanson
*    Date:   August 16, 2021
*    
*    Credit: Israel Gbati (Udemy course creator)
*
*    Description: Introduction to using SVC exceptions on ARM Cortex-M* processors.
*/

int __svc(0x00) svc_service_add(int x, int y);
int __svc(0x01) svc_service_sub(int x, int y);
int __svc(0x02) svc_service_mul(int x, int y);
int __svc(0x03) svc_service_div(int x, int y);
void SVC_Handler_C(unsigned int * svc_args);

volatile int x, y, z;

int main(void)
{
    x = 1;
    y = 5;
    z = svc_service_add(x, y);
    
    x = 9;
    y = 2;
    z = svc_service_sub(x, y);
    
    x = 7;
    y = 8;
    z = svc_service_mul(x, y);
    
    x = 52;
    y = 4;
    z = svc_service_div(x, y);
    
    return 0;
}

/**
*    SVC_Handler
*     |-> 4. Run Supervisor Call (SVC) exception service (see SVC_Handler_C)
*             |-> 3. Determine the SVC number (see SVC_Handler_C)
*                     |-> 2. Read the program counter (PC) register (see SVC_Handler_C)
*                             |-> 1. Read the linker register (LR)
*/
__asm void SVC_Handler(void)
{
    TST LR, #4    // Test bit 2 of link register i.e. 4 = 0b0100
                  // ... performs AND operation
                  // ... ... if ( LR & 4 == 0 ) then conditional flag 'Z' = 1
                  // ... ... else 'Z' = 0
    
    ITE EQ        // If Then Else... if link register bit 2 == 0 (i.e if 'Z' == 1)
                  // ... checks the Z conditional flag (see flag setting explanation above)
                  // *** These conditionals are determined from Table 2-17 "Exception Return
                  //      Behavior" on page 2-28 of Cortex-M4 Devices Generic User Guide ***
    
    MRSEQ R0, MSP // Then access main stack pointer (MSP) using MRS instruction
    MRSNE R0, PSP // Else access program stack pointer (PSP) using MRS instruction
                  // *** MRS and MSR are instructions for accessing special registers
    
    B __cpp(SVC_Handler_C) // Branch to a C implementation of the SVC handler
}

/**
*    svc_args[] ... registers are pushed onto stack when exception/interrupt occurs
*     |-> this stack frame is passed to SVC handler
*         top of stack ... [    R0     ]  svc_arg[0] ->  Parameter passing register 0; Return value register
*                          [    R1     ]  svc_arg[1] ->  Parameter passing register 1
*                          [    R2     ]  svc_arg[2]    ^^^ARM Architecture Procedure Call Standard (AAPCS)^^^
*                          [    R3     ]  svc_arg[3]
*                          [    R12    ]  svc_arg[4]
*                          [  R14(LR)  ]  svc_arg[5]
*                          [  R15(PC)  ]  svc_arg[6] ->  This contatins value of next instruction (PC) stored when SVC instruction executed
*                                                        ^^^ e.g. If SVC instruction @ 0x08000396, then next thumb instruction @ 0x08000398 (this value stored)
*/
void SVC_Handler_C(unsigned int * svc_args)
{
    unsigned int svc_number;
    svc_number = ((char *)svc_args[6])[-2]; // Use -2 offset from stored PC value to obtain SVC number... SVC is 2-byte thumb inst. stored little-endian
                                            // e.g.  address        LSB             MSB
                                            //      0x08000396      00-FF (SVC #)   DF (SVC OPCODE) 
                                            //      0x08000398      XX              XX (this PC stored when SVC exception hits)
    
    switch(svc_number) {
        case 0:
            svc_args[0] = svc_args[0] + svc_args[1];
            break;
        case 1:
            svc_args[0] = svc_args[0] - svc_args[1];
            break;
        case 2:
            svc_args[0] = svc_args[0] * svc_args[1];
            break;
        case 3:
            svc_args[0] = svc_args[0] / svc_args[1];
            break;
        default:
            break;
    }
}
