/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    appms1.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "appms1.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APPMS1_DATA appms1Data;
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APPMS1_Initialize ( void )

  Remarks:
    See prototype in appms1.h.
 */

void APPMS1_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appms1Data.state = APPMS1_STATE_INIT;
    
    appms1Data.val_queue_handle = xQueueCreate(1, sizeof(appms1qtype)); //creates a queue that holds one item
    
}


/******************************************************************************
  Function:
    void APPMS1_Tasks ( void )

  Remarks:
    See prototype in appms1.h.
 */

void APPMS1_Tasks ( void )
{
    dbgOutputLoc(DLOC_TASK_ENTER);
    dbgOutputLoc(DLOC_TASK_BEFORE_WHILE);
    while(1){
        APPMS1_serviceTasks();
    }
#if 0   //ignore state machine for now 
    
    /* Check the application's current state. */
    switch ( appms1Data.state )
    {
        /* Application's initial state. */
        case APPMS1_STATE_INIT:
        {
            bool appInitialized = true;
       
        
            if (appInitialized)
            {
            
                appms1Data.state = APPMS1_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APPMS1_STATE_SERVICE_TASKS:
        {
            APPMS1_serviceTasks();
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
#endif
}

void APPMS1_serviceTasks(){
    
    appms1qtype recv;
    xQueueReceive(appms1Data.val_queue_handle, &recv, portMAX_DELAY);
    dbgOutputLoc(DLOC_TASK_AFTER_QRECIEVE);
    //do stuff
    //--------
    //output to UART and to 8-bit I/O for logic analyzer
    
    dbgOutputVal(recv); //to I/O lines
    dbgUARTVal(recv);   //to UART (duh)
    
}

void appms1_send_val_to_queue_block(appms1qtype* param1){ //blocks if queue is full
    xQueueSend(appms1Data.val_queue_handle, param1, portMAX_DELAY);
    return;
}

BaseType_t appms1_send_val_to_queue_noblock(appms1qtype* param1){ //returns error if queue is full
    return xQueueSendFromISR(appms1Data.val_queue_handle, param1, NULL);
 }

/*******************************************************************************
 End of File
 */
