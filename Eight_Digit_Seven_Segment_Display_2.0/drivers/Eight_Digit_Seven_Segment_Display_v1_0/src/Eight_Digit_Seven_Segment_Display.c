

/***************************** Include Files *******************************/
#include "Eight_Digit_Seven_Segment_Display.h"

/************************** Function Definitions ***************************/
void Write_BCD_to_SSD(u32 BaseAddress, u32 n)
{
	Xil_Out32(BaseAddress, n);
}

void Write_int_to_SSD(u32 BaseAddress, u32 n)
{
	Xil_Out32(BaseAddress, int2bcd_left_padded_with_ones(n));
}

void Write_int_to_SSD_Left_Padded(u32 BaseAddress, u32 n)
{
	Xil_Out32(BaseAddress, int2bcd(n));
}


void Set_decimal_points(u32 BaseAddress, u32 n)
{
	Xil_Out32(BaseAddress + EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_S00_AXI_SLV_REG1_OFFSET, n);
}


u32 int2bcd(u32 n)
{
    u32 out=0;
    u32 n_reduced=n;
    u32 digit=0;
    u32 i=0;

    while( (n_reduced > 0) && (i<8))
    {
    digit = n_reduced % 10;
    n_reduced  = (n_reduced - digit)/10;
    out = out | (digit << (4*i));
    i++;
    }

    return out;
}

u32 int2bcd_left_padded_with_ones(u32 n)
{
    u32 out=0;
    u32 n_reduced=n;
    u32 digit=0;
    u32 i=0;
    u32 mask = 0xFFFFFFFF;
    //The mask will be shifted left for each digit in the representation

    while( (n_reduced > 0) && (i<8))
    {
    digit = n_reduced % 10;
    n_reduced  = (n_reduced - digit)/10;
    out = out | (digit << (4*i));
    mask = mask << 4;
    i++;
    }



    return out | mask  ;
}
