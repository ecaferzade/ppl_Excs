#include "regDefs.h"
#include <SPIv1.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig) {
	printf("terminating...\n");
	exit(1);
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
	    printf("%c", (char) cc1200_reg_read(0x3F, NULL));
	}
}
