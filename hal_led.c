/**************************************************************************//*!
 *  @file           hal_led.c
 *  @brief          [HAL] LED ドライバ API を定義したファイル。
 *  @author         Ryoji Morita
 *  @attention      none.
 *  @sa             none.
 *  @bug            none.
 *  @warning        none.
 *  @version        1.00
 *  @last updated   2016.06.05
 *************************************************************************** */
#ifdef __cplusplus
    extern "C"{
#endif


//********************************************************
/* include                                               */
//********************************************************
#include "hal_cmn.h"
#include "hal.h"


//********************************************************
/*! @def                                                 */
//********************************************************
#define LED00_OUT    (2)
#define LED01_OUT    (3)
#define LED02_OUT    (4)
#define LED03_OUT    (17)
#define LED04_OUT    (27)
#define LED05_OUT    (22)
#define LED06_OUT    (10)
#define LED07_OUT    (9)
#define LED08_OUT    (11)
#define LED09_OUT    (5)

#define LED10_OUT    (6)
#define LED11_OUT    (13)
#define LED12_OUT    (19)
#define LED13_OUT    (26)
#define LED14_OUT    (14)
#define LED15_OUT    (15)
#define LED16_OUT    (18)
#define LED17_OUT    (23)
#define LED18_OUT    (24)
#define LED19_OUT    (25)

#define LED20_OUT    (8)
#define LED21_OUT    (7)
#define LED22_OUT    (12)
#define LED23_OUT    (16)
#define LED24_OUT    (20)
#define LED25_OUT    (21)


//********************************************************
/*! @enum                                                */
//********************************************************
// なし


//********************************************************
/*! @struct                                              */
//********************************************************
// なし


//********************************************************
/* モジュールグローバル変数                              */
//********************************************************
// なし


//********************************************************
/* 関数プロトタイプ宣言                                  */
//********************************************************
static void         InitParam( void );
static EHalBool_t   InitReg( void );




/**************************************************************************//*!
 * @brief     ファイルスコープ内のグローバル変数を初期化する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
static void
InitParam(
    void  ///< [in] ナシ
){
    return;
}


/**************************************************************************//*!
 * @brief     H/W レジスタを初期化する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    EN_TRUE : 成功, EN_FALSE : 失敗
 *************************************************************************** */
static EHalBool_t
InitReg(
    void  ///< [in] ナシ
){
    return EN_TRUE;
}


/**************************************************************************//*!
 * @brief     LED を初期化する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    EN_TRUE : 成功, EN_FALSE : 失敗
 *************************************************************************** */
EHalBool_t
HalLed_Init(
    void  ///< [in] ナシ
){
    EHalBool_t      ret = EN_FALSE;

    InitParam();
    ret = InitReg();
    if( ret == EN_FALSE )
    {
        perror( "Unable to initialize GPIO port." );
        return ret;
    }

    ret = EN_TRUE;
    return ret;
}


/**************************************************************************//*!
 * @brief     LED を終了する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
void
HalLed_Fini(
    void  ///< [in] ナシ
){
    return;
}


/**************************************************************************//*!
 * @brief     LED を点灯する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
void
HalLed_Set(
    unsigned int    value   ///< [in] 点灯する値
){
    unsigned char   flg = 0;

    flg = ( value & 0x00000001 ) >> 0;
    if( flg == 1 ){ HalCmnGpio_Set( LED00_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED00_OUT, EN_LOW  ); }

    flg = ( value & 0x00000002 ) >> 1;
    if( flg == 1 ){ HalCmnGpio_Set( LED01_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED01_OUT, EN_LOW  ); }

    flg = ( value & 0x00000004 ) >> 2;
    if( flg == 1 ){ HalCmnGpio_Set( LED02_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED02_OUT, EN_LOW  ); }

    flg = ( value & 0x00000008 ) >> 3;
    if( flg == 1 ){ HalCmnGpio_Set( LED03_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED03_OUT, EN_LOW  ); }

    flg = ( value & 0x00000010 ) >> 4;
    if( flg == 1 ){ HalCmnGpio_Set( LED04_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED04_OUT, EN_LOW  ); }

    flg = ( value & 0x00000020 ) >> 5;
    if( flg == 1 ){ HalCmnGpio_Set( LED05_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED05_OUT, EN_LOW  ); }

    flg = ( value & 0x00000040 ) >> 6;
    if( flg == 1 ){ HalCmnGpio_Set( LED06_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED06_OUT, EN_LOW  ); }

    flg = ( value & 0x00000080 ) >> 7;
    if( flg == 1 ){ HalCmnGpio_Set( LED07_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED07_OUT, EN_LOW  ); }


    flg = ( value & 0x00000100 ) >> 8;
    if( flg == 1 ){ HalCmnGpio_Set( LED08_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED08_OUT, EN_LOW  ); }

    flg = ( value & 0x00000200 ) >> 9;
    if( flg == 1 ){ HalCmnGpio_Set( LED09_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED09_OUT, EN_LOW  ); }

    flg = ( value & 0x00000400 ) >> 10;
    if( flg == 1 ){ HalCmnGpio_Set( LED10_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED10_OUT, EN_LOW  ); }

    flg = ( value & 0x00000800 ) >> 11;
    if( flg == 1 ){ HalCmnGpio_Set( LED11_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED11_OUT, EN_LOW  ); }

    flg = ( value & 0x00001000 ) >> 12;
    if( flg == 1 ){ HalCmnGpio_Set( LED12_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED12_OUT, EN_LOW  ); }

    flg = ( value & 0x00002000 ) >> 13;
    if( flg == 1 ){ HalCmnGpio_Set( LED13_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED13_OUT, EN_LOW  ); }

    flg = ( value & 0x00004000 ) >> 14;
    if( flg == 1 ){ HalCmnGpio_Set( LED14_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED14_OUT, EN_LOW  ); }

    flg = ( value & 0x00008000 ) >> 15;
    if( flg == 1 ){ HalCmnGpio_Set( LED15_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED15_OUT, EN_LOW  ); }


    flg = ( value & 0x00010000 ) >> 16;
    if( flg == 1 ){ HalCmnGpio_Set( LED16_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED16_OUT, EN_LOW  ); }

    flg = ( value & 0x00020000 ) >> 17;
    if( flg == 1 ){ HalCmnGpio_Set( LED17_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED17_OUT, EN_LOW  ); }

    flg = ( value & 0x00040000 ) >> 18;
    if( flg == 1 ){ HalCmnGpio_Set( LED18_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED18_OUT, EN_LOW  ); }

    flg = ( value & 0x00080000 ) >> 19;
    if( flg == 1 ){ HalCmnGpio_Set( LED19_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED19_OUT, EN_LOW  ); }

    flg = ( value & 0x00100000 ) >> 20;
    if( flg == 1 ){ HalCmnGpio_Set( LED20_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED20_OUT, EN_LOW  ); }

    flg = ( value & 0x00200000 ) >> 21;
    if( flg == 1 ){ HalCmnGpio_Set( LED21_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED21_OUT, EN_LOW  ); }

    flg = ( value & 0x00400000 ) >> 22;
    if( flg == 1 ){ HalCmnGpio_Set( LED22_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED22_OUT, EN_LOW  ); }

    flg = ( value & 0x00800000 ) >> 23;
    if( flg == 1 ){ HalCmnGpio_Set( LED23_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED23_OUT, EN_LOW  ); }


    flg = ( value & 0x01000000 ) >> 24;
    if( flg == 1 ){ HalCmnGpio_Set( LED24_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED24_OUT, EN_LOW  ); }

    flg = ( value & 0x02000000 ) >> 25;
    if( flg == 1 ){ HalCmnGpio_Set( LED25_OUT, EN_HIGH ); }
    else          { HalCmnGpio_Set( LED25_OUT, EN_LOW  ); }


    return;
}


/**************************************************************************//*!
 * @brief     LED を順番に点灯する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
void
HalLed_Sequence(
    void    ///< [in] ナシ
){
    int             i = 0;
    unsigned int    value = 0x1;

    for( i = 0; i < 2; i++ )
    {
        HalLed_Set( value );
        usleep( 500 * 1000 );
        value = ( value << 1 ) % 0x03FFFFFF;
    }

    return;
}


#ifdef __cplusplus
    }
#endif

