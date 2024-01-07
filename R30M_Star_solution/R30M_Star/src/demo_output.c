/**
* \file  demo_output.c
*
* \brief Demo output Implementation.
*
* Copyright (c) 2018 - 2019 Microchip Technology Inc. and its subsidiaries. 
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

#include "system.h"
#include "miwi_config.h"
#include "miwi_config_p2p.h"
#include "delay.h"
#include "demo_output.h"
#include "miwi_api.h"
#include "sio2host.h"
#include "asf.h"


/*************************************************************************/
// the following two variable arrays are the data to be transmitted
// in this demo. They are bit map of English word "MiWi" and "DE"
// respectively.
/*************************************************************************/
const uint8_t MiWi[6][21] =
{
    {0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0x20,0x20,0xB2,0x20,0xB2,0x0D,0x0A},
    {0xB2,0x20,0xB2,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0xB2,0x20,0x20,0xB2,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x0D,0x0A},
    {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0D,0x0A}
    
};   

const uint8_t DE[6][11] =
{
    {0xB2,0xB2,0xB2,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0xB2,0xB2,0xB2,0xB2,0x0D,0x0A},
    {0xB2,0x20,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0x0D,0x0A},
    {0xB2,0xB2,0xB2,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x0D,0x0A},
    {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x0D,0x0A}
}; 


#define DEBOUNCE_TIME 0x00003FFF

bool PUSH_BUTTON_pressed;
MIWI_TICK PUSH_BUTTON_press_time;

void DemoOutput_Greeting(void)
{    
        printf("\r\nStarting Node 1 of CMAKE Simple Demo for MiWi(TM) STAR Stack ...");  
        printf("\r\n     RF Transceiver: AT86RF212B");
        printf("\r\n   Demo Instruction:");
        printf("\r\n                     Power on the board until LED 1 lights up");
        printf("\r\n                     to indicate connecting with peer.");
        printf("\r\n                     Press SW Button to broadcast message.");
		printf("\r\n                     LED 1 will be toggled upon receiving messages. ");
        printf("\r\n\r\n");		
}        

void demo_output_freezer_options(void)
{ 
}
void DemoOutput_Channel(uint8_t channel, uint8_t Step)
{
    if( Step == 0 )
    {
        #if !defined(MIWIKIT)
        printf("\r\nConnecting Peer on Channel ");
        printf("%d",channel);
        printf("\r\n");
        #endif
    }
    else
    { 
        #if !defined(MIWIKIT)
        printf("\r\nConnected Peer on Channel ");
        printf("%d",channel);
        printf("\r\n");
        #endif
    }
}    

void DemoOutput_Instruction(void)
{
}


void DemoOutput_HandleMessage(void)
{
    uint8_t i;
	uint8_t startPayloadIndex = 0;

    if( rxMessage.flags.bits.secEn )
    {
        sio2host_tx((uint8_t *)"Secured ", sizeof("Secured "));
    }

    if( rxMessage.flags.bits.broadcast )
    {
        sio2host_tx((uint8_t *)"Broadcast Packet with RSSI ", sizeof("Broadcast Packet with RSSI "));
    }
    else
    {
        sio2host_tx((uint8_t *)"Unicast Packet with RSSI ",sizeof("Unicast Packet with RSSI "));
    }
    printf("%02x", rxMessage.PacketRSSI);
    if( rxMessage.flags.bits.srcPrsnt )
    {
        sio2host_tx((uint8_t *)" from ", sizeof(" from "));
        if( rxMessage.flags.bits.altSrcAddr )
        {
            printf( "%x", rxMessage.SourceAddress[1]);
            printf( "%x", rxMessage.SourceAddress[0]);
        }
        else
        {    
            for(i = 0; i < MY_ADDRESS_LENGTH; i++)
            {
                printf("%x", rxMessage.SourceAddress[MY_ADDRESS_LENGTH-1-i]);
            }    
        }
    }
    sio2host_tx((uint8_t *)": ",sizeof(": "));

	/* If the role is not PAN Coordinator and receiving a unicast
	   then first three bytes are source end device info, so skip this*/
	if (END_DEVICE == role && !rxMessage.flags.bits.broadcast)
	{
	    startPayloadIndex = 3;
	}
    
    for(i = startPayloadIndex; i < rxMessage.PayloadSize; i++)
    {
        sio2host_putchar(rxMessage.Payload[i]);
    }
} 

void DemoOutput_UpdateTxRx(uint8_t TxNum, uint8_t RxNum)
{
}

void DemoOutput_ChannelError(uint8_t channel)
{
    printf("\r\nSelection of channel ");
    printf("%d", channel);
    printf(" is not supported in current configuration.\r\n");
}

void DemoOutput_UnicastFail(void)
{
    printf("\r\nUnicast Failed\r\n");
}    

void Source_END_DEVICE_INFO(uint8_t *SrAddr)
{
	delay_ms(1200);
}
    
void STAR_DEMO_OPTIONS_MESSAGE(DeviceRole_t deviceRole)
{
}    

/*********************************************************************
 * Function:        uint8_t ButtonPressed(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Return value to indicate which button has been pressed.
 *                  Return 0 if no button pressed.
 *
 * Side Effects:
 *
 * Overview:        This function check if any button has been pressed
 *
 * Note:
 ********************************************************************/

uint8_t ButtonPressed(void)
{
    MIWI_TICK tickDifference;
    if(!port_pin_get_input_level(BUTTON_0_PIN))
    {
        //if the button was previously not pressed
        if(PUSH_BUTTON_pressed == false)
        {
            PUSH_BUTTON_pressed = true;
            PUSH_BUTTON_press_time.Val = MiWi_TickGet();
            return 1;
        }
    }
    else
    {
        //get the current time
        MIWI_TICK t;
        t.Val = MiWi_TickGet();

        //if the button has been released long enough
        tickDifference.Val = MiWi_TickGetDiff(t,PUSH_BUTTON_press_time);

        //then we can mark it as not pressed
        if(tickDifference.Val > DEBOUNCE_TIME)
        {
            PUSH_BUTTON_pressed = false;
        }
    }
    return 0;
}
