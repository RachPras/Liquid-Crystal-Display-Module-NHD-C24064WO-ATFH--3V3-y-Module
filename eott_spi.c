///***********************************************************************************************************************************************/
///******************************** PROJECT : End of Train Telemetry System(EoTT)        *********************************************************/
///*******************************  ABSTRACT: Chip on glass Liquid Crystal Display Module(NHD-C24064WO-ATFH#-3V3 ) *******************************/
///*******************************  FILE    : EOTT_LCD.c                                                           *******************************/
///***********************************************************************************************************************************************/
#include "EOTT_LCD.h"
#include "HL_spi.h"
#include "string.h"
#include "uartstdio.h"
#include "EOTT_Hardware.h"
/*****************************************************/
//below is picture.h file information
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

spiDAT1_t dataconfig1_t;
/*****************************************************/
/*****************************************************************************************************************************************************
 ** Function name   : LCD_TransmitData
 ** Descriptions    : transmit the data Via serial communication
 ** parameters      : None
 ** Returned value  : None
 ****************************************************************************************************************************************************/
uint32 LCD_TransmitData(spiBASE_t *spi, spiDAT1_t *dataconfig_t, uint32 blocksize, uint8 * srcbuff)
{
    volatile uint32 SpiBuf;
    uint16 Tx_Data;
    uint32 Chip_Select_Hold = (dataconfig_t->CS_HOLD) ? 0x10000000U : 0U;
    uint32 WDelay = (dataconfig_t->WDEL) ? 0x04000000U : 0U;
    SPIDATAFMT_t DataFormat = dataconfig_t->DFSEL;
    uint8 ChipSelect = dataconfig_t->CSNR;
    while(blocksize != 0U)
    {
        if((spi->FLG & 0x000000FFU) !=0U)
        {
            break;
        }
        if(blocksize == 1U)
        {
            Chip_Select_Hold = 0U;
        }
        Tx_Data = *srcbuff;
        spi->DAT1 =  ((uint32)DataFormat << 24U) |
                ((uint32)ChipSelect << 16U) |
                (WDelay)           |
                (Chip_Select_Hold) |
                (uint32)Tx_Data;
        srcbuff++;
        while((spi->FLG & 0x00000100U) != 0x00000100U)
        {
        } /* Wait */
        SpiBuf = spi->BUF;
        blocksize--;
    }
    return (spi->FLG & 0xFFU);
}
/*****************************************************************************************************************************************************
 ** Function name   : Write_MasterComand
 ** Descriptions    : write the command to the master
 ** parameters      : data
 ** Returned value  : None
 ****************************************************************************************************************************************************/
void Write_MasterComand(uint8_t j)
{
    uint8_t *ptr1;
    ptr1 = &j;
    LCD_A0(LOW);                                              /*  A0 = Low */
    LCD_CS1(LOW);                                             /*  CS1 = Low */
    LCD_TransmitData(spiREG1,&dataconfig1_t, 1,  ptr1);       /*  transmit the data*/
    LCD_CS1(HIGH);                                            /*  CS1 = High */
}
/*****************************************************************************************************************************************************
 ** Function name   : Write_SlaveComand
 ** Descriptions    : write the slave to the master
 ** parameters      : data
 ** Returned value  : None
 ****************************************************************************************************************************************************/
void Write_SlaveComand(uint8_t j)
{
    uint8_t *ptr1;
    ptr1 = &j;
    LCD_A0(LOW);                                              /*  A0 = Low */
    LCD_CS2(LOW);                                             /*  CS2 = Low */
    LCD_TransmitData(spiREG1,&dataconfig1_t, 1,  ptr1);       /*  transmit the data*/
    LCD_CS2(HIGH);                                            /*  CS2 = High */
}
/*****************************************************************************************************************************************************
 ** Function name   : Write_MasterData
 ** Descriptions    : write the data to the master
 ** parameters      : data
 ** Returned value  : None
 ****************************************************************************************************************************************************/
void Write_MasterData(uint8_t i)
{
    uint8_t *ptr;
    ptr = &i;
    LCD_A0(HIGH);                                             /*  A0 = high */
    LCD_CS1(LOW);                                             /*  CS1 = Low */
    LCD_TransmitData(spiREG1,&dataconfig1_t, 1,  ptr);        /*  transmit the data*/
    LCD_CS1(HIGH);                                            /*  CS1 = High */
}
/*****************************************************************************************************************************************************
 ** Function name   : Write_SlaveData
 ** Descriptions    : write the data to the Slave
 ** parameters      : data
 ** Returned value  : None
 ****************************************************************************************************************************************************/
void Write_SlaveData(uint8_t i)
{
    uint8_t *ptr;
    ptr = &i;
    LCD_A0(HIGH);                                            /*  A0 = high */
    LCD_CS2(LOW);                                            /*  CS2 = Low */
    LCD_TransmitData(spiREG1,&dataconfig1_t, 1,  ptr);       /*  transmit the data*/
    LCD_CS2(HIGH);                                           /*  CS2 = High */
}
/*****************************************************************************************************************************************************
 ** Function name   : LCD_Init
 ** Descriptions    : Initialization For controller  Turn On the LCD display by using commands
 ** parameters      : None
 ** Returned value  : None
 ****************************************************************************************************************************************************/
void LCD_Init(void)
{
    LCD_RD_PS(LOW);                                   /* P/S = “H”: Parallel data input.P/S = “L”: Serial data input.       */
    LCD_C86(LOW);                                     /* C86 = “H”: 6800 Series MPU interface.C86 = “L”: 8080 MPU interface.*/
    LCD_RST_BAR(LOW);                                 /* When reset is set to “L,” the settings are initialized             */
    Delay_uSec(2000);                                 /* Delay 2msec            */
    LCD_RST_BAR(HIGH);                                /*  reset is set to “H,”              */
    Delay_uSec(20000);                                /* Delay 20msec            */
    /*  Send Display wake up command for the Master processor */
    Write_MasterComand(LCD_BIAS_SET);                 /* 1/9 bias  LCD_BIAS_SET*/
    Write_MasterComand(LCD_ADC_SEL_NORM);
    Write_MasterComand(LCD_COM_REV);                  /* Com output normal */
    Write_MasterComand(LCD_ALLPOINTS_ON);             /* Display all points normal mode */
    Write_MasterComand(LCD_STRT_LINE);                /*  Display start Line */
    Write_MasterComand(LCD_RES_RATIO);                /*  Display resistor ratio is set to be 5.5*/
    Write_MasterComand(LCD_ELEC_VLMODE);              /*  Electronic volume mode  set the V5 output voltage*/
    Write_MasterComand(LCD_ELEC_VLRES);               /*  Electronic volume register value is set to be 63*/
    Write_MasterComand(LCD_PWR_SET);                  /*  LCD Booster circuit: ON,Voltage regulator circuit: ON,Voltage follower circuit: ON*/
    Write_MasterComand(LCD_DISP_ON);                         /* display on*/
    /*  Send Display wake up command for the Master processor */
    Write_SlaveComand(LCD_BIAS_SET);                  /* 1/9 bias */
    Write_SlaveComand(LCD_ADC_SEL_NORM);               /* ADC segment driver direction (A0=Normal) */
    Write_SlaveComand(LCD_COM_REV);                  /* Com output normal */
    Write_SlaveComand(LCD_ALLPOINTS_ON);              /* Display all points normal mode */
    Write_SlaveComand(LCD_STRT_LINE);                 /*  Display start Line */
    Write_SlaveComand(LCD_RES_RATIO);                 /*  Display resistor ratio is set to be 5.5*/
    Write_SlaveComand(LCD_ELEC_VLMODE);               /*  Electronic volume mode  set the V5 output voltage*/
    Write_SlaveComand(LCD_ELEC_VLRES);                /*  Electronic volume register value is set to be 63*/
    Write_SlaveComand(LCD_PWR_SET);                   /*  LCD Booster circuit: ON,Voltage regulator circuit: ON,Voltage follower circuit: ON*/
    Write_SlaveComand(LCD_DISP_ON);                          /* display on*/
}
/*****************************************************************************************************************************************************
 ** Function name   : ClearDisplay
 ** Descriptions    : Function clears the whole display
 ** parameters      : None
 ** Returned value  : None
 ****************************************************************************************************************************************************/
void ClearDisplay(void)
{
    unsigned int i= 0,j = 0;
    uint8_t MSB = 0X10,LSB = 0X00;
    uint8_t page = 0xB0;                                       /* Page Address + 0xB0  */
    Write_MasterComand(LCD_STRT_LINE);                               /* Master Display start address + 0x40 */
    Write_SlaveComand(LCD_STRT_LINE);                                /* Slave Display start address + 0x40   */
    for(j= 0;j<8;j++)                                                /* for 8 pages */
    {
        Write_MasterComand(page);                                    /* send master page address  */
        Write_SlaveComand(page);                                     /* send slave page address   */
        for(i=0;i<132;i++)                                           /* 132 Line address */
        {
            LSB = (i & 0X0F);
            MSB = (i & 0XF0) >> 4;
            Write_MasterComand(LSB);                                 /* Master column address upper 4 bits + 0x10 */
            Write_MasterComand(LCD_COLM_ADDR_MSB | MSB);             /* Master column address lower 4 bits + 0x00 */
            Write_SlaveComand(LSB);                                  /* Slave column address upper 4 bits + 0x10 */
            Write_SlaveComand(LCD_COLM_ADDR_MSB | MSB);              /* Slave column address lower 4 bits + 0x00 */
            Write_MasterData(0X00);                                  /* clear the master pixel */
            Write_SlaveData(0X00);                                   /* clear the slave pixel */
        }
        page++;
    }
}
/*****************************************************************************************************************************************************
 ** Function name   : DispLaydat_master
 ** Descriptions    : Function writes the data into the Master Display
 ** parameters      : Data wants to write
 ** Returned value  : None
 ****************************************************************************************************************************************************/

void Displaydat_Slave(uint8_t pageaddr,uint8_t clmnaddr,uint8_t pagesize,uint8_t colomnsize,uint8_t *lcdstrng)
{
    unsigned int i,j;
    uint8_t MSB = 0X10,LSB = 0X00;

    uint8_t page = pageaddr;                                       /* Page Address + 0xB0  */
    Write_SlaveComand(LCD_STRT_LINE);                           /* slave Display start address + 0x40 */

    for(j= 0;j<pagesize;j++)                                           /* for 8 pages */
    {

        Write_SlaveComand(page);                                /* send slave page address  */
        MSB = 0X10,LSB = 0X00;
        for(i=clmnaddr;i<colomnsize+clmnaddr;i++)
        {

            LSB = (i & 0X0F);
            MSB = (i & 0XF0) >> 4;
            Write_SlaveComand(LSB);                              /* slave column address upper 4 bits + 0x10 */
            Write_SlaveComand(LCD_COLM_ADDR_MSB | MSB);          /* slave column address lower 4 bits + 0x00 */
            Write_SlaveData(*lcdstrng);
            lcdstrng++;
        }
        page++;
    }
    Write_SlaveComand(0xAF);                                    /*  slave Display ON */

}

void Displaydata_Master(uint8_t pageaddr,uint8_t clmnaddr,uint8_t pagesize,uint8_t colomnsize,uint8_t *lcdstrng)
{

    unsigned int i,j;
    uint8_t MSB = 0X10,LSB = 0X00;
    uint8_t page = pageaddr;                                 /* Page Address + 0xB0  */
    LSB = (clmnaddr & 0X0F);
    MSB = (clmnaddr & 0XF0) >> 4;

    Write_MasterComand(LCD_STRT_LINE);                         /* Master Display start address + 0x40 */
    for(j= 0;j<pagesize;j++)                                          /* for 8 pages */
    {
        Write_MasterComand(page);                              /* send master page address  */
        for(i=clmnaddr;i<colomnsize+clmnaddr;i++)                                     /* 132 Line address */
        {
            LSB = (i & 0X0F);
            MSB = (i & 0XF0) >> 4;
            Write_MasterComand(LSB);                           /* Master column address upper 4 bits + 0x10 */
            Write_MasterComand(LCD_COLM_ADDR_MSB | MSB);       /* Master column address lower 4 bits + 0x00 */
            Write_MasterData(*lcdstrng);
            lcdstrng++;
        }
        page++;
    }
    Write_MasterComand(LCD_DISP_ON);                                   /*  master Display ON */

}
/************************************************************************************************************************************************/
/*******************************************          END FILE           ************************************************************************/
/************************************************************************************************************************************************/
/************************************************************************************************************************************************/




