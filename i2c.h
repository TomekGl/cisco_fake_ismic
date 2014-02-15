/** \file i2c.h
 * \brief Interrupt-driven I2C bus support
 */

#define I2C_Write 0;
#define I2C_Read 1;

#define I2C_LM75_ADDRESS 0x48 /* not shifted */
#define I2C_OWN_ADDRESS 0x7E

#define I2EN	(unsigned long)(1<<6)
#define STA		(unsigned long)(1<<5)
#define STO		(unsigned long)(1<<4)
#define SI		(unsigned long)(1<<3)
#define AA		(unsigned long)(1<<2)


//void Initialize(void);
//void i2c_main(void);
void I2C_Init(void);
void I2C_Send(void);
