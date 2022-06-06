#include "registers.h"
#include <stdio.h>
#include <SPIv1.h>
#include<unistd.h>
#include<string.h>



    int ConvertToDec(int* bits, int size)
{
	    int result = 0;

		for (int i = 0; i < size; i++) {

		result |= bits[i];
		if(i != size-1)
		result <<= 1;
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

 for(i=0;n>0;i++)    
{    
	a[i]=n%2;    
	n=n/2;    
		} 


 printf("\nBinary of Given Number is=");    
     for(i=i-1;i>=0;i--)   

  {    
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
int check = a[k];
if(a[k]!=-1){

freq2[m]=a[k];}

else
{ freq2[m]=0;
}
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


printf("Reading the set frequency...\n");

cc1200_reg_read(adr0, &val0);
cc1200_reg_read(adr1, &val1);
cc1200_reg_read(adr2, &val2);
printf("The value saved in freq0 is: %d\n", val0);
printf("The value saved in freq1 is: %d\n", val1);
printf("The value saved in freq2 is: %d\n", val2);

}






int main(int argc, char *argv[]) {


typedef struct {
        int adr;  /**< Register Adresse  */
        int val;  /**< Wert des Registers */
} REG_TYPE;

#define MAX_REG  47
#define MAX_EXT_REG  130

REG_TYPE RegSettings[MAX_REG] =
{
    {IOCFG3         , 0x06 }, // GPIO3 IO Pin Configuration
    {IOCFG2         , 0x06 }, // GPIO2 IO Pin Configuration
    {IOCFG1         , 0x30 }, // GPIO1 IO Pin Configuration
    {IOCFG0         , 0x3c }, // GPIO0 IO Pin Configuration
    {SYNC3          , 0x93 }, // Sync Word Configuration [31:24]
    {SYNC2          , 0x0b }, // Sync Word Configuration [23:16]
    {SYNC1          , 0x51 }, // Sync Word Configuration [15:8]
    {SYNC0          , 0xde }, // Sync Word Configuration [7:0]
    {SYNC_CFG1      , 0xa9 }, // Sync Word Detection Configuration Reg. 1
    {SYNC_CFG0      , 0x03 }, // Sync Word Detection Configuration Reg. 0
    {DEVIATION_M    , 0x06 }, // Frequency Deviation Configuration
    {MODCFG_DEV_E   , 0x0b }, // Modulation Format and Frequency Deviation Configur..
    {DCFILT_CFG     , 0x4c }, // Digital DC Removal Configuration
    {PREAMBLE_CFG1  , 0x14 }, // Preamble Length Configuration Reg. 1 (reset);
    {PREAMBLE_CFG0  , 0x8a }, // Preamble Detection Configuration Reg. 0
    {IQIC           , 0xc8 }, // Digital Image Channel Compensation Configuration
    {CHAN_BW        , 0x10 }, // Channel Filter Configuration
    {MDMCFG1        , 0x42 }, // General Modem Parameter Configuration Reg. 1
    {MDMCFG0        , 0x05 }, // General Modem Parameter Configuration Reg. 0
    {SYMBOL_RATE2   , 0x8f }, // Symbol Rate Configuration Exponent and Mantissa [1..
    {SYMBOL_RATE1   , 0x75 }, // Symbol Rate Configuration Mantissa [15:8]
    {SYMBOL_RATE0   , 0x10 }, // Symbol Rate Configuration Mantissa [7:0]
    {AGC_REF        , 0x27 }, // AGC Reference Level Configuration
    {AGC_CS_THR     , 0xee }, // Carrier Sense Threshold Configuration
    {AGC_GAIN_ADJUST, 0x00 }, // RSSI Offset Configuration
    {AGC_CFG3       , 0xb1 }, // Automatic Gain Control Configuration Reg. 3
    {AGC_CFG2       , 0x20 }, // Automatic Gain Control Configuration Reg. 2
    {AGC_CFG1       , 0x11 }, // Automatic Gain Control Configuration Reg. 1
    {AGC_CFG0       , 0x94 }, // Automatic Gain Control Configuration Reg. 0
    {FIFO_CFG       , 0x00 }, // FIFO Configuration
    {DEV_ADDR       , 0x00 }, // Device Address Configuration
    {SETTLING_CFG   , 0x0b }, // Frequency Synthesizer Calibration and Settling Con..
    {FS_CFG         , 0x12 }, // Frequency Synthesizer Configuration
    {WOR_CFG1       , 0x08 }, // eWOR Configuration Reg. 1
    {WOR_CFG0       , 0x21 }, // eWOR Configuration Reg. 0
    {WOR_EVENT0_MSB , 0x00 }, // Event 0 Configuration MSB
    {WOR_EVENT0_LSB , 0x00 }, // Event 0 Configuration LSB
    {RXDCM_TIME     , 0x00 }, // RX Duty Cycle Mode Configuration
    {PKT_CFG2       , 0x00 }, // Packet Configuration Reg. 2 (on reset)
    {PKT_CFG1       , 0x03 }, // Packet Configuration Reg. 1 (on reset)
    {PKT_CFG0       , 0x00 }, // Packet Configuration Reg. 0 (on reset)
    {RFEND_CFG1     , 0x0f }, // RFEND Configuration Reg. 1
    {RFEND_CFG0     , 0x00 }, // RFEND Configuration Reg. 0
    {PA_CFG1        , 0x7f }, // Power Amplifier Configuration Reg. 1
    {PA_CFG0        , 0x56 }, // Power Amplifier Configuration Reg. 0
    {ASK_CFG        , 0x0f }, // ASK Configuration
    {PKT_LEN        , 0x0a }  // Packet Length Configuration
};

REG_TYPE ExtRegSettings[MAX_EXT_REG] =
{
    {IF_MIX_CFG      , 0x1c },  // IF Mix Configuration
    {FREQOFF_CFG     , 0x20 },  // Frequency Offset Correction Configuration (on Reset)
    {TOC_CFG         , 0x03 },  // Timing Offset Correction Configuration (reset value)
    {MARC_SPARE      , 0x00 },  // MARC Spare
    {ECG_CFG         , 0x00 },  // External Clock Frequency Configuration
    {MDMCFG2         , 0x02 },  // General Modem Parameter Configuration Reg. 2
    {EXT_CTRL        , 0x01 },  // External Control Configuration
    {RCCAL_FINE      , 0x00 },  // RC Oscillator Calibration Fine
    {RCCAL_COARSE    , 0x00 },  // RC Oscillator Calibration Coarse
    {RCCAL_OFFSET    , 0x00 },  // RC Oscillator Calibration Clock Offset
    {FREQOFF1        , 0x00 },  // Frequency Offset MSB
    {FREQOFF0        , 0x00 },  // Frequency Offset LSB
    {FREQ2           , 0x56 },  // Frequency Configuration [23:16]
    {FREQ1           , 0xcc },  // Frequency Configuration [15:8]
    {FREQ0           , 0xcc },  // Frequency Configuration [7:0]
    {IF_ADC2         , 0x02 },  // Analog to Digital Converter Configuration Reg. 2
    {IF_ADC1         , 0xee },  // Analog to Digital Converter Configuration Reg. 1
    {IF_ADC0         , 0x10 },  // Analog to Digital Converter Configuration Reg. 0
    {FS_DIG1         , 0x04 },  // Frequency Synthesizer Digital Reg. 1
    {FS_DIG0         , 0x50 },  // Frequency Synthesizer Digital Reg. 0
    {FS_CAL3         , 0x00 },  // Frequency Synthesizer Calibration Reg. 3
    {FS_CAL2         , 0x20 },  // Frequency Synthesizer Calibration Reg. 2
    {FS_CAL1         , 0x40 },  // Frequency Synthesizer Calibration Reg. 1
    {FS_CAL0         , 0x0e },  // Frequency Synthesizer Calibration Reg. 0
    {FS_CHP          , 0x28 },  // Frequency Synthesizer Charge Pump Configuration
    {FS_DIVTWO       , 0x03 },  // Frequency Synthesizer Divide by 2
    {FS_DSM1         , 0x00 },  // FS Digital Synthesizer Module Configuration Reg. 1
    {FS_DSM0         , 0x33 },  // FS Digital Synthesizer Module Configuration Reg. 0
    {FS_DVC1         , 0xf7 },  // Frequency Synthesizer Divider Chain Configuration ..
    {FS_DVC0         , 0x0f },  // Frequency Synthesizer Divider Chain Configuration ..
    {FS_LBI          , 0x00 },  // Frequency Synthesizer Local Bias Configuration
    {FS_PFD          , 0x00 },  // Frequency Synthesizer Phase Frequency Detector Con..
    {FS_PRE          , 0x6e },  // Frequency Synthesizer Prescaler Configuration
    {FS_REG_DIV_CML  , 0x1c },  // Frequency Synthesizer Divider Regulator Configurat..
    {FS_SPARE        , 0xac },  // Frequency Synthesizer Spare
    {FS_VCO4         , 0x14 },  // FS Voltage Controlled Oscillator Configuration Reg..
    {FS_VCO3         , 0x00 },  // FS Voltage Controlled Oscillator Configuration Reg..
    {FS_VCO2         , 0x00 },  // FS Voltage Controlled Oscillator Configuration Reg..
    {FS_VCO1         , 0x00 },  // FS Voltage Controlled Oscillator Configuration Reg..
    {FS_VCO0         , 0xb5 },  // FS Voltage Controlled Oscillator Configuration Reg..
    {GBIAS6          , 0x00 },  // Global Bias Configuration Reg. 6
    {GBIAS5          , 0x02 },  // Global Bias Configuration Reg. 5
    {GBIAS4          , 0x00 },  // Global Bias Configuration Reg. 4
    {GBIAS3          , 0x00 },  // Global Bias Configuration Reg. 3
    {GBIAS2          , 0x10 },  // Global Bias Configuration Reg. 2
    {GBIAS1          , 0x00 },  // Global Bias Configuration Reg. 1
    {GBIAS0          , 0x00 },  // Global Bias Configuration Reg. 0
    {IFAMP           , 0x09 },  // Intermediate Frequency Amplifier Configuration
    {LNA             , 0x01 },  // Low Noise Amplifier Configuration
    {RXMIX           , 0x01 },  // RX Mixer Configuration
    {XOSC5           , 0x0e },  // Crystal Oscillator Configuration Reg. 5
    {XOSC4           , 0xa0 },  // Crystal Oscillator Configuration Reg. 4
    {XOSC3           , 0x03 },  // Crystal Oscillator Configuration Reg. 3
    {XOSC2           , 0x04 },  // Crystal Oscillator Configuration Reg. 2
    {XOSC1           , 0x03 },  // Crystal Oscillator Configuration Reg. 1
    {XOSC0           , 0x00 },  // Crystal Oscillator Configuration Reg. 0
    {ANALOG_SPARE    , 0x00 },  // Analog Spare
    {PA_CFG3         , 0x00 },  // Power Amplifier Configuration Reg. 3
    {WOR_TIME1       , 0x00 },  // eWOR Timer Counter Value MSB
    {WOR_TIME0       , 0x00 },  // eWOR Timer Counter Value LSB
    {WOR_CAPTURE1    , 0x00 },  // eWOR Timer Capture Value MSB
    {WOR_CAPTURE0    , 0x00 },  // eWOR Timer Capture Value LSB
    {BIST            , 0x00 },  // MARC Built-In Self-Test
    {DCFILTOFFSET_I1 , 0x00 },  // DC Filter Offset I MSB
    {DCFILTOFFSET_I0 , 0x00 },  // DC Filter Offset I LSB
    {DCFILTOFFSET_Q1 , 0x00 },  // DC Filter Offset Q MSB
    {DCFILTOFFSET_Q0 , 0x00 },  // DC Filter Offset Q LSB
    {IQIE_I1         , 0x00 },  // IQ Imbalance Value I MSB
    {IQIE_I0         , 0x00 },  // IQ Imbalance Value I LSB
    {IQIE_Q1         , 0x00 },  // IQ Imbalance Value Q MSB
    {IQIE_Q0         , 0x00 },  // IQ Imbalance Value Q LSB
    {RSSI1           , 0x80 },  // Received Signal Strength Indicator Reg. 1
    {RSSI0           , 0x00 },  // Received Signal Strength Indicator Reg.0
    {MARCSTATE       , 0x41 },  // MARC State
    {LQI_VAL         , 0x00 },  // Link Quality Indicator Value
    {PQT_SYNC_ERR    , 0xff },  // Preamble and Sync Word Error
    {DEM_STATUS      , 0x00 },  // Demodulator Status
    {FREQOFF_EST1    , 0x00 },  // Frequency Offset Estimate MSB
    {FREQOFF_EST0    , 0x00 },  // Frequency Offset Estimate LSB
    {AGC_GAIN3       , 0x00 },  // Automatic Gain Control Reg. 3
    {AGC_GAIN2       , 0xd1 },  // Automatic Gain Control Reg. 2
    {AGC_GAIN1       , 0x00 },  // Automatic Gain Control Reg. 1
    {AGC_GAIN0       , 0x3f },  // Automatic Gain Control Reg. 0
    {CFM_RX_DATA_OUT , 0x00 },  // Custom Frequency Modulation RX Data
    {CFM_TX_DATA_IN  , 0x00 },  // Custom Frequency Modulation TX Data
    {ASK_SOFT_RX_DATA, 0x30 },  //:ASK Soft Decision Output
    {RNDGEN          , 0x7f },  // Random Number Generator Value
    {MAGN2           , 0x00 },  // Signal Magnitude after CORDIC [16]
    {MAGN1           , 0x00 },  // Signal Magnitude after CORDIC [15:8]
    {MAGN0           , 0x00 },  // Signal Magnitude after CORDIC [7:0]
    {ANG1            , 0x00 },  // Signal Angular after CORDIC [9:8]
    {ANG0            , 0x00 },  // Signal Angular after CORDIC [7:0]
    {CHFILT_I2       , 0x02 },  // Channel Filter Data Real Part [16]
    {CHFILT_I1       , 0x00 },  // Channel Filter Data Real Part [15:8]
    {CHFILT_I0       , 0x00 },  // Channel Filter Data Real Part [7:0]
    {CHFILT_Q2       , 0x00 },  // Channel Filter Data Imaginary Part [16]
    {CHFILT_Q1       , 0x00 },  // Channel Filter Data Imaginary Part [15:8]
    {CHFILT_Q0       , 0x00 },  // Channel Filter Data Imaginary Part [7:0]
    {GPIO_STATUS     , 0x00 },  // General Purpose Input/Output Status
    {FSCAL_CTRL      , 0x01 },  // Frequency Synthesizer Calibration Control
    {PHASE_ADJUST    , 0x00 },  // Frequency Synthesizer Phase Adjust
    {PARTNUMBER      , 0x20 },  // Part Number
    {PARTVERSION     , 0x11 },  // Part Revision
    {SERIAL_STATUS   , 0x00 },  // Serial Status
    {MODEM_STATUS1   , 0x10 },  // Modem Status Reg. 1
    {MODEM_STATUS0   , 0x00 },  // Modem Status Reg. 0
    {MARC_STATUS1    , 0x00 },  // MARC Status Reg. 1
    {MARC_STATUS0    , 0x00 },  // MARC Status Reg. 0
    {PA_IFAMP_TEST   , 0x00 },  // Power Amplifier Intermediate Frequency Amplifier T..
    {FSRF_TEST       , 0x00 },  // Frequency Synthesizer Test
    {PRE_TEST        , 0x00 },  // Frequency Synthesizer Prescaler Test
    {PRE_OVR         , 0x00 },  // Frequency Synthesizer Prescaler Override
    {ADC_TEST        , 0x00 },  // Analog to Digital Converter Test
    {DVC_TEST        , 0x0b },  // Digital Divider Chain Test
    {ATEST           , 0x40 },  // Analog Test
    {ATEST_LVDS      , 0x00 },  // Analog Test LVDS
    {ATEST_MODE      , 0x00 },  // Analog Test Mode
    {XOSC_TEST1      , 0x3c },  // Crystal Oscillator Test Reg. 1
    {XOSC_TEST0      , 0x00 },  // Crystal Oscillator Test Reg. 0
    {AES             , 0x00 },  // AES
    {MDM_TEST        , 0x00 },  // MODEM Test
    {RXFIRST         , 0x00 },  // RX FIFO Pointer First Entry
    {TXFIRST         , 0x00 },  // TX FIFO Pointer First Entry
    {RXLAST          , 0x00 },  // RX FIFO Pointer Last Entry
    {TXLAST          , 0x00 },  // TX FIFO Pointer Last Entry
    {NUM_TXBYTES     , 0x00 },  // TX FIFO Status
    {NUM_RXBYTES     , 0x00 },  // RX FIFO Status
    {FIFO_NUM_TXBYTES, 0x0f },  //:TX FIFO Status
    {FIFO_NUM_RXBYTES, 0x00 },  //:RX FIFO Status
    {RXFIFO_PRE_BUF  , 0x00 }  // RX FIFO Status
};




// first initialize
  if(spi_init()){
    printf("ERROR: Initialization failed\n");
  return -1;
  
  }
  
 
  // do some register reading or writing, 
  // performance commands and get status information
 
  // reset CC1200
  cc1200_cmd(SRES);
  sleep(1);
  
  
  for(int i=0; i<MAX_REG; i++){
	  
	  cc1200_reg_write(RegSettings[i].adr, RegSettings[i].val);
	  
	  
  }
  
    
  for(int i=0; i<MAX_EXT_REG; i++){
	  
	  cc1200_reg_write(ExtRegSettings[i].adr, ExtRegSettings[i].val);
	  
																	 
  }
  
  int freq=850;
  setFrequency(freq);  
  
  //while(1){
   //RFEND_CFG0 needs to be programmed 
   
    int bytes;
    
    printf("Enter the number of bytes: ");
    scanf("%d", &bytes);

    char c[bytes];

    printf("Enter the string to be transmitted: ");
    
    scanf("%s", c);
    //int length = strlen(c);
    printf("Transmitting string\n");

    cc1200_reg_write(0x3F, PKT_CFG0);
    while(1){
    for(int i=0; i<bytes; i++){

    cc1200_reg_write(0x3F, c[i]);
    }
    
    sleep(1);
    cc1200_cmd(STX);
    sleep(1);
    
    printf("String transmitted\n");
    }
    
  //}
  
  
  
  
  
  }
