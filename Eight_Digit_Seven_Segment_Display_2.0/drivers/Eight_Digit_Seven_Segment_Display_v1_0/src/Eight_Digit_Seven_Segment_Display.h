#ifndef EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_H
#define EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

#define EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_S00_AXI_SLV_REG0_OFFSET 0
#define EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_S00_AXI_SLV_REG1_OFFSET 4
#define EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_S00_AXI_SLV_REG2_OFFSET 8
#define EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_S00_AXI_SLV_REG3_OFFSET 12


/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAYdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_Reg_SelfTest(void * baseaddr_p);

/**
 *
 * Writes a 32 bit bcd-encoded number to the display
 *
 * @param   BaseAddress is the base address of the EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY device.
 * @param   n is an eight digit bcd encoded decimal number.
 *          NOTE: if a digit is 0xA through 0xF, the digit will display blank.
 *          This behavior can be used to turn off four of the digits for example.
 *
 * @return  nothing
 *
 */

void Write_BCD_to_SSD(u32 BaseAddress, u32 n);

/**
 * Write a 32 bit positive integer to the display
 *
 * @param   BaseAddress is the base address of the EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY device.
 * @param   n is a non-negative integer less than or equal to 99999999.
 *          The result will not be left padded with 0's. Digits to the left
 *          will be blank.
 *
 * @return  nothing
 *
 */

void Write_int_to_SSD(u32 BaseAddress, u32 n);





/**
 * Write a 32 bit positive integer to the display
 *
 * @param   BaseAddress is the base address of the EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY device.
 * @param   n is a non-negative integer less than or equal to 99999999.
 *          The result will be left padded with 0's.
 *
 * @return  nothing
 *
 */

void Write_int_to_SSD_Left_Padded(u32 BaseAddress, u32 n);







/**
 * Set decimal points
 *
 * @param   BaseAddress is the base address of the EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY device.
 * @param   n is an unsigned integer.  The only thing that matter is the least significant
 *          bits.  Bit 0 controls the decimal point on the first digit, Bit 1 controls the
 *          the decimal point on the second digit etc.  1 = on  0 = off.
 *
 * @return  nothing
 *
 */

void Set_decimal_points(u32 baseaddress, u32 n );

/**
 *
 * Helper function to convert integers to bcd
 * This function will convert non-negative numbers up to 99999999.
 *
 * @param   n is an unsigned integers less than or equal to 99999999.
 *
 * @return  bcd eight digit representation of n
 *
 */

u32 int2bcd(u32 n);


/**
 *
 * Helper function to convert integers to bcd
 * This function will convert non-negative numbers up to 99999999.
 * The only difference between this function and int2bcd
 * is that the result is padded with ones on the left.
 * For example 382 will be output as 0xFFFFF382. The purpose of
 * this representation is to display the left-most digits as blanks.
 *
 * @param   n is an unsigned integers less than or equal to 99999999.
 *
 * @return  bcd eight digit representation of n padded with 1's on the left
 *
 */

u32 int2bcd_left_padded_with_ones(u32 n);


#endif // EIGHT_DIGIT_SEVEN_SEGMENT_DISPLAY_H
