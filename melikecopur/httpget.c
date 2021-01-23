/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
//Melike ÇOPUR

/*
 *  ======== httpget.c ========
 *  HTTP Client GET example application
 */
#include <string.h>

/* XDCtools Header files */
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Timestamp.h>

/* TI-RTOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/GPIO.h>
#include <ti/net/http/httpcli.h>
#include <ti/drivers/I2C.h>
#include <ti/sysbios/knl/Semaphore.h>

/* BIOS Header files */
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Idle.h>
#include <ti/sysbios/knl/Intrinsics.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Swi.h>
// new headers
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/sysctl.h"

/* Example/Board Header file */
#include "Board.h"

#include <sys/socket.h>

extern Semaphore_Handle semaphore0;
extern Event_Handle event0;


#define TASKSTACKSIZE   2048
#define PAJ7620_ID              0x73                      // DEVICE SLAVE ID
#define PAJ7620_BANK_SEL        0xEF                     // DEVICE BANK SELECT REGISTER

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

#define HOSTNAME         "api.openweathermap.org"                                                 // API ADDRESS
#define REQUEST_URI       "/data/2.5/weather?q=eskisehir&appid=01baf9bb2decfa2884446355a53bba9b" //01baf9bb2decfa2884446355a53bba9b
#define USER_AGENT        "HTTPCli (ARM; TI-RTOS)"
#define SOCKETTEST_IP     "192.168.2.3"
#define HTTPTASKSTACKSIZE 4096
int countersem =0;
uint8_t Gesture_Data1;
char   tempstr[20];

char data[64];
   int ret;
   int len;
   int stringlen=10;
   struct sockaddr_in addr;
   char *ptr,*ptr2;
   char *limit;
   int temp_received;
   char *getword;

/*
 *  ======== printError ========
 */

I2C_Handle      i2c;
I2C_Params      i2cParams;
I2C_Transaction i2cTransaction;

Void heartBeatFxn(UArg arg0, UArg arg1)
{
    while (1) {
        Task_sleep((unsigned int)arg0);
        GPIO_toggle(Board_LED0);
    }
}
bool PAJ7620_OpenComm(void)
{
    bool retval = false;
    int y=0;

    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_100kHz;                                // minimum speed first

    i2c = I2C_open(Board_I2C0, &i2cParams);
    if (i2c == NULL) {
        System_abort("Error InitializinggggI2C\n");              // error, retval is false
    }
    else {
        System_printf("I2C Initialized!\n");                   // everything alright, retval is true
        retval = true;
    }
    System_flush();

    uint8_t txBuffer[1];
    uint8_t rxBuffer[1];

                   txBuffer[0] = 0x00;                                                //register check

                   i2cTransaction.slaveAddress = PAJ7620_ID;
                   i2cTransaction.writeBuf = txBuffer;
                   i2cTransaction.writeCount = 1;
                   i2cTransaction.readBuf = rxBuffer;
                   i2cTransaction.readCount = 1;
                   if (I2C_transfer(i2c, &i2cTransaction)) {
                   System_printf("register check 0x%x\n", rxBuffer[0]);            // 0x20 can be seen on console

                                         }
                   else {
                   System_printf("I2C Bus fault\n");
                                         }
                   System_flush();

                   for(y=0;y<51;y++) {                         //defined initialize values in board.h writer in this for loop


                        uint8_t tx5Buffer[2];

                        uint8_t rx5Buffer[1];
                        tx5Buffer[0] =Init_Register_Array[y][0];
                        tx5Buffer[1] =Init_Register_Array[y][1];
                        i2cTransaction.slaveAddress = PAJ7620_ID;
                        i2cTransaction.writeBuf = tx5Buffer;
                        i2cTransaction.writeCount = 2;
                        i2cTransaction.readBuf = rx5Buffer;
                        i2cTransaction.readCount = 0;

                          if (I2C_transfer(i2c, &i2cTransaction)) {
                                   System_printf("PAJ7620 %x %x\n", tx5Buffer[0], tx5Buffer[1]);
                              }
                           else {
                                   System_printf("I2C Bus fault\n");
                                }
                                    System_flush();
                                 }


    return retval;                                  // return true or false
}


void taskFxn(UArg arg1, UArg arg2)
{

    int i=0;

    PAJ7620_OpenComm();                                       // IIC open and initialize sensor

    uint8_t tx2Buffer[2];
    uint8_t rx2Buffer[1];
    uint8_t cmd=0;

    tx2Buffer[0] = PAJ7620_BANK_SEL;
    tx2Buffer[1] = cmd;
    i2cTransaction.slaveAddress = PAJ7620_ID;
    i2cTransaction.writeBuf = tx2Buffer;
    i2cTransaction.writeCount = 2;
    i2cTransaction.readBuf = rx2Buffer;
    i2cTransaction.readCount = 0;

                    if (I2C_transfer(i2c, &i2cTransaction)) {
                        System_printf("PAJ7620 %x %d\n",PAJ7620_BANK_SEL, cmd);


                         System_printf("bank sel:  %x %d\n", PAJ7620_BANK_SEL, rx2Buffer[0]);

                         System_flush();


                    }
                    else {
                        System_printf("I2C Bus fault\n");
                    }
                    System_flush();


                    for(i=0;i<30;i++) {


                        uint8_t tx4Buffer[2];

                        uint8_t rx4Buffer[2];
                        tx4Buffer[0] =Init_Gesture_Array[i][0];
                        tx4Buffer[1] =Init_Gesture_Array[i][1];
                        i2cTransaction.slaveAddress = PAJ7620_ID;
                        i2cTransaction.writeBuf = tx4Buffer;
                        i2cTransaction.writeCount = 2;
                        i2cTransaction.readBuf = rx4Buffer;
                        i2cTransaction.readCount = 0;
                        if (I2C_transfer(i2c, &i2cTransaction)) {
                                System_printf("PAJ7620 %x %x\n", tx4Buffer[0], tx4Buffer[1]);
                            }
                            else {
                                System_printf("I2C Bus fault\n");
                            }
                            System_flush();


                        }


    while(1) {

                uint8_t tx3Buffer[1];
                uint8_t rx3Buffer[2];

                tx3Buffer[0] = 0x43;

                i2cTransaction.slaveAddress = PAJ7620_ID;
                i2cTransaction.writeBuf = tx3Buffer;
                i2cTransaction.writeCount = 1;
                i2cTransaction.readBuf = rx3Buffer;
                i2cTransaction.readCount = 1;

                if (I2C_transfer(i2c, &i2cTransaction)) {

                Gesture_Data1 =rx3Buffer[0];


                System_flush();

               if (Gesture_Data1)
                  {
                      //System_printf("Gesture_Data if check : %x  \n",Gesture_Data1);

                    //System_flush();

                     switch (Gesture_Data1)
                      {
                         case Board_UP:                  System_printf("Up\r\n");               System_flush();   break;
                         case Board_DOWN:                System_printf("Down\r\n");             System_flush();   break;
                         case Board_LEFT:                System_printf("Left\r\n");             System_flush();   Event_post(event0,Event_Id_00);  break;
                         case Board_RIGHT:               System_printf("Right\r\n");            System_flush();   Event_post(event0,Event_Id_01);  break;
                         case Board_FORWARD:             System_printf("Forward\r\n");          System_flush();   break;
                         case Board_BACKWARD:            System_printf("Backward\r\n");         System_flush();   break;
                         case Board_CLOCKWISE:           System_printf("Clockwise\r\n");        System_flush();   break;
                         case Board_COUNT_CLOCKWISE:     System_printf("AntiClockwise\r\n");    System_flush();   break;
                         case Board_WAVE:                System_printf("Wave\r\n");             System_flush();   break;

                         I2C_close(i2c);
                         default: break;

                       }
                         System_flush();

                      }
                }
            else {
                      System_printf("I2C Bus fault\n");

                  }
                        System_flush();


            Task_sleep(500);
        }

}



void printError(char *errString, int code)
{
    System_printf("Error! code = %d, desc = %s\n", code, errString);
    BIOS_exit(code);
}

/*
 *  ======== httpTask ========
 *  Makes a HTTP GET request
 */
Void httpTask(UArg arg0, UArg arg1)

{

    bool moreFlag = false;
    limit=",";



    HTTPCli_Struct cli;
    HTTPCli_Field fields[3] = {
        { HTTPStd_FIELD_NAME_HOST, HOSTNAME },
        { HTTPStd_FIELD_NAME_USER_AGENT, USER_AGENT },
        { NULL, NULL }
    };
    while(1){

         temp_received=0;

        Event_pend(event0,Event_Id_00,Event_Id_01,BIOS_WAIT_FOREVER);
        System_printf("event_Id_00 pended %d \n",++countersem);
        System_flush();

    System_printf("Sending a HTTP GET request to '%s'\n", HOSTNAME);
    System_flush();

    HTTPCli_construct(&cli);

    HTTPCli_setRequestFields(&cli, fields);

    ret = HTTPCli_initSockAddr((struct sockaddr *)&addr, HOSTNAME, 0);
    if (ret < 0) {
        printError("httpTask: address resolution failed", ret);
    }

    ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, NULL);
    if (ret < 0) {
        printError("httpTask: connect failed", ret);
    }

    ret = HTTPCli_sendRequest(&cli, HTTPStd_GET, REQUEST_URI, false);
    if (ret < 0) {
        printError("httpTask: send failed", ret);
    }

    ret = HTTPCli_getResponseStatus(&cli);
    if (ret != HTTPStd_OK) {
        printError("httpTask: cannot get status", ret);
    }

    System_printf("HTTP Response Status Code: %d\n", ret);

    ret = HTTPCli_getResponseField(&cli, data, sizeof(data), &moreFlag);
    if (ret != HTTPCli_FIELD_ID_END) {
        printError("httpTask: response field processing failed", ret);
    }

    len = 0;
    do {

        ret = HTTPCli_readResponseBody(&cli, data, sizeof(data), &moreFlag);
        if (ret < 0) {
            printError("httpTask: response body processing failed", ret);
        }
        else{

        if (Gesture_Data1 == Board_RIGHT ){
            getword="humidity";
             stringlen= 10;
             limit="}";

        }
        else if (Gesture_Data1 == Board_LEFT){
            getword="temp";
            stringlen= 6;
            limit=",";

                }

                ptr = strstr(data,getword);
                if(ptr){
                 if(temp_received) continue;

                    ptr2 = strstr(ptr,limit);
                    if(ptr2) {
                        *ptr2 = 0;                                           // put end of string
                        System_printf("%s : %s\n", getword, ptr+stringlen); // print the string
                        System_flush();
                        strcpy(tempstr, ptr+stringlen);
                        temp_received = 1;

                    }


                }
        }
        len += ret;
    } while (moreFlag);

    //Semaphore_post(semaphore0);
    Event_post(event0,Event_Id_03);
    System_printf("Total Recieved %d bytes of payload\n", len);
    System_flush();

    HTTPCli_disconnect(&cli);


    }
    HTTPCli_destruct(&cli);

}
void sendDatatoServer(char *serverIP, int serverPort, char *data, int size)
{

    int sockfd;
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);   // SOCK_STREAM: TCP, SOCK_DGRAM: UDP
    if (sockfd == -1) {
        System_printf("Socket not created");
        //BIOS_exit(-1);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));  /* clear serverAddr structure */
    serverAddr.sin_family = AF_INET;       // IPV4 COMMUNICATION
    serverAddr.sin_port = htons(serverPort);     /* convert port # to network order */ // HOST BY ORDER DAN NETWORK BY ORDERA
    inet_pton(AF_INET, serverIP, &(serverAddr.sin_addr));

    int connStat = connect(sockfd, (struct sockaddr *)&serverAddr, /* connecting….*/
                  sizeof(serverAddr));
    if(connStat < 0) {
        System_printf("Error while connecting to server\n");
        if (sockfd > 0)
            close(sockfd);
       // BIOS_exit(-1);
    }

    int numSend = send(sockfd, data, size, 0);       /* send data to the server*/
    if(numSend < 0) {
        System_printf("Error while sending data to server\n");
        if (sockfd > 0) close(sockfd);
        //BIOS_exit(-1);
    }

    if (sockfd > 0) close(sockfd);

}

Void CallSocket(UArg arg1, UArg arg2)
{

        // wait for the event that httpTask() will signal
        // when temperature or humidity string is retrieved from api.openweathermap.org site

       while(1){
       Event_pend(event0,Event_Id_03,Event_Id_NONE,BIOS_WAIT_FOREVER);
       //Semaphore_pend(semaphore0, BIOS_WAIT_FOREVER);
        System_printf("socket task running to send data to server\n");
        System_flush();

        sendDatatoServer(SOCKETTEST_IP, 5011, tempstr, strlen(tempstr));

       }
}

/*
 *  ======== netIPAddrHook ========
 *  This function is called when IP Addr is added/deleted
 */
void netIPAddrHook(unsigned int IPAddr, unsigned int IfIdx, unsigned int fAdd)
{
    static Task_Handle taskHandle1,taskHandle2;
    Task_Params taskParams;
    Error_Block eb;

    /* Create a HTTP task when the IP address is added */
    if (fAdd && !taskHandle1 && !taskHandle2) {
        Error_init(&eb);

        Task_Params_init(&taskParams);
        taskParams.stackSize = HTTPTASKSTACKSIZE;
        taskParams.priority = 1;
        taskHandle1 = Task_create((Task_FuncPtr)httpTask, &taskParams, &eb);
        Task_Params_init(&taskParams);
        taskParams.stackSize = TASKSTACKSIZE;
        taskParams.priority = 1;
        taskHandle2 = Task_create((Task_FuncPtr)CallSocket, &taskParams, &eb);

        if (taskHandle1 == NULL || taskHandle2 == NULL) {
            printError("netIPAddrHook: Failed to create HTTP Task\n", -1);
            System_flush();
        }
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions */
    Task_Params taskParams;
    Board_initGeneral();
    Board_initGPIO();
    Board_initEMAC();
    Board_initI2C();
    /* Turn on user LED */

    /* Construct heartBeat Task  thread */
       Task_Params_init(&taskParams);
       taskParams.arg0 = 1000;
       taskParams.stackSize = TASKSTACKSIZE;
       taskParams.stack = &task0Stack;
       Task_construct(&task0Struct, (Task_FuncPtr)heartBeatFxn, &taskParams, NULL);

    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Starting the HTTP GET example\nSystem provider is set to "
            "SysMin. Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
