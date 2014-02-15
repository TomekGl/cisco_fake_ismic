/** \file ismic.h
 * \addtogroup ismic
 * \brief ISMIC interface implementation
 *
 * \details This module implements very basic functionality of ISMIC.
 * ISMIC in HP BladeSystem enables communication between chassis' Onboard
 * Administrator and removable devices such as servers, switches etc.
 * This is only switch<->ISMIC chip implementation, ISMIC<->OA protocol is
 * unknown due to lack of such hardware.
 *
 * ISMIC stores multiple sequence of bytes, organized into banks. Lenght of banks
 * varies. Banks can be written by device and read by OM, set by OM and read
 * by device, or written and read by both sides.
 *
 *
 * \author Tomasz Głuch, http://tomaszgluch.pl/
 * \date 2012-12-31
 */

#ifndef ISMIC_H_
#define ISMIC_H_

#include <stdint.h>

//compute checksum
uint8_t BankCRC(uint8_t *bank, uint8_t len);

extern volatile uint8_t bankNumber;
extern volatile uint8_t bankByteIndex;
extern volatile uint8_t bankSet;


///array of pointers to banks
extern uint8_t *banks[];

///array of banks sizes
extern uint8_t bank_size[];


#endif /* ISMIC_H_ */
