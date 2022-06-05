#include "regDefs.h"
#include "SPIv1.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    
    if(spi_init()){  // first initialize
        printf("ERROR: Initialization failed\n");
        return -1;
    }
    cc1200_cmd(SRES);  // reset CC1200
    sleep(1);
    writeAllRegisters();  // write the register according to the desired mode
    cc1200_cmd(SRX);  // get in receiving mode
    // get status information
    cc1200_cmd(SNOP);  // refreshes the current status
    printf("INFO: Status:%s\n", get_status_cc1200_str());
    
    int received_nr_bytes = 0;
    int expect_nr_bytes = 10;
    fflush(stdout);
    while(received_nr_bytes < expect_nr_bytes){
        /* From the datasheet: "The NUM_RXBYTES register can be polled at a given rate to get
information about the number of bytes in the RX FIFO."
        */
        cc1200_reg_read(NUM_RXBYTES, &received_nr_bytes);  // polls NUM_RXBYTES and writes the value to &received_nr_bytes
    printf("number of received bytes: %d \n", received_nr_bytes);
    }
    
    printf("The received message is: "); // after every expected byte arrived:
    for(int i = 0; i < received_nr_bytes; i++){
        printf("%c", (char) cc1200_reg_read(0x3F, NULL));
    }

    /*
    // Alternative for variable length transmitting
    while(1){
        printf("%c", (char) cc1200_reg_read(0x3F, NULL));
    }
    
    */

}
