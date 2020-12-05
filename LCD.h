/***********************************************************************************************************************************************/
/******************************** PROJECT :                                            *********************************************************/
/*******************************  ABSTRACT: Chip on glass Liquid Crystal Display Module(NHD-C24064WO-ATFH#-3V3 ) *******************************/
/*******************************  FILE    : EOTT_LCD.h                                                           *******************************/
/***********************************************************************************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdint.h>



#define     HIGH                 1
#define     LOW                  0
#define     LCD_CS1(X)           gioSetBit(hetPORT1,2 ,X)   /* N2HET1_2    PINMUX->W5 */
#define     LCD_CS2(X)           gioSetBit(hetPORT1,18,X)   /* N2HET1_18   PINMUX->J1 */
#define     LCD_RST_BAR(X)       gioSetBit(hetPORT1,16,X)   /* N2HET1_16   PINMUX->A4 */
#define     LCD_A0(X)            gioSetBit(hetPORT1,30,X)   /* N2HET1_30   PINMUX->B11 */
#define     LCD_WR_BAR(X)        gioSetBit(hetPORT1,14,X)   /* N2HET1_14   PINMUX->A11 */
#define     LCD_RD_BAR(X)        gioSetBit(hetPORT1,12,X)   /* N2HET1_12   PINMUX->B4 */
#define     LCD_C86(X)           gioSetBit(gioPORTB,2 ,X)   /* GIOB_2      PINMUX->F2 */
#define     LCD_RD_PS(X)         gioSetBit(hetPORT1,29,X)   /* N2HET1_29   PINMUX->C3 */
/************** Command For LCD Display   ***********************************/
#define     LCD_DISP_ON          0XAF         /* Display ON */
#define     LCD_DISP_OFF         0XAE         /* Display OFF */
#define     LCD_STRT_LINE        0X40         /* Display start Line */
#define     LCD_PAGE_ADDR        0XB0         /* Display Page Address Set */
#define     LCD_COLM_ADDR_MSB    0X10         /* Display Column address MSB SET */
#define     LCD_COLM_ADDR_LSB    0X00         /* Display Column address LSB SET */
#define     LCD_ADC_SEL_NORM     0XA0         /* ADC select Normal MOde */
#define     LCD_ADC_SEL_REV      0XA1         /* ADC select Reverse MOde */
#define     LCD_NORM_MODE        0XA6         /* Display Normal mode */
#define     LCD_REV_MODE         0XA7         /* Display Reverse mode */
#define     LCD_RD_WR            0XE0         /* Column address increment */
#define     LCD_BIAS_SET         0XA2         /* Display bias set to 1/9 ratio */
#define     LCD_COM_NORM         0XC0         /* Display COM output Normal Mode */
#define     LCD_COM_REV          0XC8         /* Display COM output Reverse Mode */
#define     LCD_ALLPOINTS_ON     0XA4         /* Display all points Normal Mode */
#define     LCD_ALLPOINTS_OFF    0XA5         /* Display all points Reverse Mode */

#define     LCD_RES_RATIO        0X25         /* Display internal resistor ratio */
#define     LCD_ELEC_VLMODE      0X81         /* Electronic Volume mode  */
#define     LCD_ELEC_VLRES       0X10         /* Electronic Volume resistor  */
#define     LCD_PWR_SET          0X2F         /* LCD power controller is set */
#define     LCD_STATUS_READ      0XB0         /* Display Status Read */
#define     LCD_RESET            0XE2         /* Reset the LCD display */



void Write_MasterComand(uint8_t  ) ;
void Write_SlaveComand (uint8_t  ) ;
void Write_MasterData  (uint8_t  ) ;
void Write_SlaveData   (uint8_t  ) ;
void LCD_Init(void);
void ClearDisplay(void);
void Displaydata_Master(uint8_t ,uint8_t ,uint8_t ,uint8_t ,uint8_t *);
void Displaydat_Slave(uint8_t ,uint8_t ,uint8_t ,uint8_t ,uint8_t *);

/************************************************************************************************************************************************/
/*******************************************          END FILE           ************************************************************************/
/************************************************************************************************************************************************/
/************************************************************************************************************************************************/

