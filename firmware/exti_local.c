#include "main.h"

#include "softmodem.h"

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * EXTERNS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * PROTOTYPES
 ******************************************************************************
 */
static void txcb(EXTDriver *extp, expchannel_t channel);
static void rxcb(EXTDriver *extp, expchannel_t channel);

/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, txcb},
    {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, rxcb},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}
  }
};

/*
 ******************************************************************************
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 ******************************************************************************
 */

static void txcb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;

  if (0 == ModemOutBit())
    palClearPad(IOPORT1, GPIOA_TX_DATA);
  else
    palSetPad(IOPORT1, GPIOA_TX_DATA);
}

static void rxcb(EXTDriver *extp, expchannel_t channel){
  (void)extp;
  (void)channel;

  if (PAL_LOW == palReadPad(IOPORT2, GPIOB_RX_DATA))
    ModemInBit(0);
  else
    ModemInBit(1);
}

/*
 ******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************
 */

/**
 *
 */
void ExtiLocalStart(void){
  ModemStart();
  extStart(&EXTD1, &extcfg);
}


