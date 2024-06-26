/**
* \file  main.c
*
* \brief Main file of Simple Example Star.
*
* Copyright (c) 2018 - 2020 Microchip Technology Inc. and its subsidiaries.
*
* \asf_license_start
*
* \page License
*
* Subject to your compliance with these terms, you may use Microchip
* software and any derivatives exclusively with Microchip products.
* It is your responsibility to comply with third party license terms applicable
* to your use of third party software (including open source software) that
* may accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
* INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
* AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
* LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
* LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
* SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
* ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
* RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*
* \asf_license_stop
*
*/
/*
* Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
*/

/**
* \mainpage
* \section preface Preface
* The simple example application code focuses on the simplicity of the
* MiWi™ DE protocol stack application programming interfaces.
* It provides a clean and straightforward wireless communication between
* two devices with less than 30 lines of effective C code to run the stack
* in application layer for both devices. In this application, following
* features of MiWi™ DE protocol stack have been demonstrated:
* <P>• Establish connection automatically between two devices.</P>
* <P>• Broadcast a packet.</P>
* <P>• Unicast a packet from one node to another through Pan Coordinator.</P>
* <P>• Apply security to the transmitted packet.</P>
*/

/************************ HEADERS ****************************************/
#include "task.h"
#include "asf.h"
#include "sio2host.h"

#if defined(ENABLE_NETWORK_FREEZER)
#include "pdsDataServer.h"
#include "wlPdsTaskManager.h"
#endif

/************************** DEFINITIONS **********************************/
#define NVM_UID_ADDRESS   ((volatile uint16_t *)(0x0080400AU))


/************************** PROTOTYPES **********************************/
void ReadMacAddress(void);

/*********************************************************************
* Function:         void main(void)
*
* PreCondition:     none
*
* Input:            none
*
* Output:            none
*
* Side Effects:        none
*
* Overview:            This is the main function that runs the simple
*                   example demo. The purpose of this example is to
*                   demonstrate the simple application programming
*                   interface for the MiWi(TM) Development
*                   Environment. By virtually total of less than 30
*                   lines of code, we can develop a complete
*                   application using MiApp interface. The
*                   application will first try to establish a
*                   link with another device and then process the
*                   received information as well as transmit its own
*                   information.
*                   MiWi(TM) DE also support a set of rich
*                   features. Example code FeatureExample will
*                   demonstrate how to implement the rich features
*                   through MiApp programming interfaces.
*
* Note:
**********************************************************************/
int main ( void )
{
    bool freezer_enable = false;
    irq_initialize_vectors();

    system_init();
    delay_init();
    cpu_irq_enable();
    sio2host_init();
	
    ReadMacAddress();
    SYS_TimerInit();

    DemoOutput_Greeting();

    nvm_init(INT_FLASH);
    PDS_Init();

    // User Selection to commission a network or use Freezer
    freezer_enable = freezer_feature();

    // Commission the network
    Initialize_Demo(freezer_enable);

    while(1)
    {
        Run_Demo();
    }
}

/*********************************************************************
* Function:         void ReadMacAddress()
*
* PreCondition:     none
*
* Input:            none
*
* Output:            Reads MAC Address from MAC Address EEPROM
*
* Side Effects:        none
*
* Overview:            Uses the MAC Address from the EEPROM for addressing
*
* Note:
**********************************************************************/
void ReadMacAddress(void)
{
   uint8_t i = 0, j = 0;
   for (i = 0; i < 8; i += 2, j++)
   {
     myLongAddress[i] = (NVM_UID_ADDRESS[j] & 0xFF);
     myLongAddress[i + 1] = (NVM_UID_ADDRESS[j] >> 8);
   }
}
