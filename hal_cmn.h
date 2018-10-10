/**************************************************************************//*!
 *  @file           hal_cmn.h
 *  @brief          [HAL] 共通 API を宣言したヘッダファイル。
 *  @author         Ryoji Morita
 *  @attention      none.
 *                  関数命名規則
 *                      通常         : Hal[デバイス名]_処理名()
 *                      割込ハンドラ : Hal[デバイス名]_IH_処理名()
 *  @sa             none.
 *  @bug            none.
 *  @warning        none.
 *  @version        1.00
 *  @last updated   2016.06.05
 *************************************************************************** */

// 多重コンパイル抑止
#ifndef _HAL_CMN_H_
#define _HAL_CMN_H_


//********************************************************
/* include                                               */
//********************************************************
#include <stdio.h>
#include <unistd.h>


//********************************************************
/*! @def                                                 */
//********************************************************
// なし


//********************************************************
/*! @enum                                                */
//********************************************************
//*************************************
// 一般用途で使用する型
//*************************************
typedef enum tagEHalBool
{
    EN_FALSE = 0,           ///< @var : FALSE (= 偽 )
    EN_TRUE                 ///< @var : TRUE  (= 真 )
} EHalBool_t;


typedef enum tagEHalOutputLevel
{
    EN_LOW = 0,             ///< @var : LOW  (= 0  V out )
    EN_HIGH = 1             ///< @var : HIGH (= 3.3V out )
} EHalOputputLevel_t;


//********************************************************
/*! @struct                                              */
//********************************************************
// なし


//********************************************************
/* 関数プロトタイプ宣言                                  */
//********************************************************
EHalBool_t  HalCmnGpio_Init( void );
void        HalCmnGpio_Fini( void );
EHalBool_t  HalCmnGpio_Set( unsigned char pin, EHalOputputLevel_t value );
EHalBool_t  HalCmnGpio_Get( unsigned char pin );


#endif /* _HAL_CMN_H_ */

