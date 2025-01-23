/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    ssd.h

  @Description
    This file groups the declarations of the functions that implement
        the SSD library (defined in ssd.c).
        Include the file in the project when this library is needed.
        Use #include "ssd.h" in the source files where the functions are needed.
 */
/* ************************************************************************** */

#ifndef _SSD_H    /* Guard against multiple inclusion */
#define _SSD_H

//#ifdef __cplusplus
//extern "C" {
//#endif



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************


void init_gpio();
uint8_t get_segment_pattern(uint8_t digit);
void display_digit(uint8_t digit_value, uint8_t digit_position);
void printOnSevenSeg(const char* num);

    /* Provide C++ Compatibility */
//#ifdef __cplusplus
//}
//#endif
#endif /* _SSD_H */

/* *****************************************************************************
 End of File
 */