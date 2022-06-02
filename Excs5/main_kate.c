#include "regDefs.h"
#include <SPIv1.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig){
    printf("terminating...\n");
    exit(1);
}


int ConvertToDec(int* bits, int size){
    int result = 0;
    for (int i = 0; i < size; i++) {
        result |= bits[i];
        if(i != size-1){
            result <<= 1;
        }
    }
    return result;
}


void setFrequency(int rfFreq){
    int constant = 6553.6;
    int n = constant*rfFreq;
    int freq0[8]={0};
    int freq1[8]={0};
    int freq2[8]={0};
    int a[24],i;    
    system ("cls"); 
    for(i=0;n>0;i++){    
        a[i]=n%2;    
        n=n/2;
    } 
    printf("\nBinary of Given Number is=");    
    for(i=i-1;i>=0;i--){    
        printf("%d",a[i]);
    } 
    int j =0;
    for(int k=7; k>=0; k--){
        freq0[j]=a[k];
        j++;
        printf("Freq0: %d\n", a[k]);
    }
    int l =0;
    for(int k=15; k>=8; k--){
        freq1[l]=a[k];
        l++;
        printf("Freq1: %d\n", a[k]);
    }
    int m=0;
    for(int k=23; k>=16; k--){
        freq2[m]=a[k];
        m++;
        printf("Freq2: %d\n", a[k]);

    }
    int len = (sizeof(freq0) / sizeof(freq0[0])); // get array size
    int result0 = ConvertToDec(freq0, len);
    int result1 = ConvertToDec(freq1, len);
    int result2 = ConvertToDec(freq2, len);
    char hex[5];
    sprintf(hex, "0x%02X", result0);
    printf("The hex frequency is: %s\n", hex);
    int adr0 = 0x2F0E;
    int adr1 = 0x2F0D;
    int adr2 = 0x2F0C;
    int val0=0;
    int val1=0;
    int val2=0;
    cc1200_reg_write(adr0, result0);
    cc1200_reg_write(adr1, result1);
    cc1200_reg_write(adr2, result2);
    printf("Reading the set frequency...");
    cc1200_reg_read(adr0, &val0);
    cc1200_reg_read(adr1, &val1);
    cc1200_reg_read(adr2, &val2);
    printf("The value saved in freq0 is: %d", val0);
    printf("The value saved in freq1 is: %d", val1);
    printf("The value saved in freq2 is: %d", val2);
}


int main(int argc, char *argv[]){

    signal(SIGTSTP, &sig_handler);
    // first initialize
    if(spi_init()){
        printf("ERROR: Initialization failed\n");
        return -1;
    }
    printf("checkpoint 0\n");
    cc1200_cmd(SRES);  // reset CC1200
    printf("checkpoint 1\n");
    sleep(1);
    writeAllRegisters();  //write the register according to the desired mode
    printf("checkpoint 2\n");
    //    sleep(1);
    cc1200_cmd(SRX);
    printf("checkpoint 3\n");
    // get status information
    cc1200_cmd(SNOP);  //refreshes the current status
    printf("INFO: Status:%s\n", get_status_cc1200_str());
    
    int rfFreq[3];
    rfFreq[0]=820;
    rfFreq[1]=850;
    rfFreq[2]=950;

    while(1){
        for(int i =0; i<3; i++){
            printf("Setting frequency to %d", rfFreq[i]);
            setFrequency(rfFreq[i]);
            sleep(1);
            int strength = cc1200_reg_read(RSSI1, NULL);
            printf("RSSI value: %d \n", strength);
            sleep(3);
            if(strength < 50){
                printf("RSSI threshold exceeded. \n");
                sleep(3);
                int packet_len = 0;
                printf("checkpoint 4\n");
                int expect_packet_len = 10;
                printf("checkpoint 5\n");
                printf("while schleife erreicht.");
                fflush(stdout);
                while(packet_len < expect_packet_len){
                /* From the datasheet: "The NUM_RXBYTES register can be polled at a given rate to get
                information about the number of bytes in the RX FIFO."
                */
                    cc1200_reg_read(NUM_RXBYTES, &packet_len);
                    printf("%d \n", packet_len);
                }
                printf("The packet is: ");
                for(int i = 0; i < packet_len; i++){
                    printf("%c \n", (char) cc1200_reg_read(0x3F, NULL));
                    printf("RSSI: %d \n", cc1200_reg_read(RSSI1, NULL));
                }
                break;
            }
            else{
                printf("RSSI is above threshold. \n");
            }
        }
    }
}
