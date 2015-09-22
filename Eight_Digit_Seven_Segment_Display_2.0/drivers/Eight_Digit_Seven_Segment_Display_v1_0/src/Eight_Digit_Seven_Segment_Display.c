

/***************************** Include Files *******************************/
#include "Eight_Digit_Seven_Segment_Display.h"

/************************** Function Definitions ***************************/
void Write_BCD_to_SSD(int baseaddress, int n)
{
	Xil_Out32(baseaddress, n);
}


void Write_int_to_SSD(int baseaddress, int n)
{
	Xil_Out32(baseaddress, int2bcd(n));
}


void Set_decimal_points(int baseaddress, int n)
{
	Xil_Out32(baseaddress + EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_S00_AXI_SLV_REG1_OFFSET, n);
}

int int2bcd(int n)
{
    int out=0;
    int n_reduced=n;
    int digit=0;
    int i=0;

    while( (n_reduced > 0) && (i<8))
    {
    digit = n_reduced % 10;
    n_reduced  = (n_reduced - digit)/10;
    out = out | (digit << (4*i));
    i++;
    }

    return out;
}
