/**************************************************************************//*!
 *  @file           hal_cmnGpio.c
 *  @brief          [HAL] GPIO の共通 API を定義したファイル。
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
#include <fcntl.h>
#include <sys/mman.h>

#include "hal_cmn.h"


//********************************************************
/*! @def                                                 */
//********************************************************
#define BLOCK_SIZE          (4 * 1024)
#define PERIPHERAL_BASE     (0x3F000000)
#define GPIO_BASE           (PERIPHERAL_BASE + 0x00200000)


//********************************************************
/*! @enum                                                */
//********************************************************
typedef enum tagEHalIO
{
    EN_INPUT = 0,           ///< @var : INPUT
    EN_OUTPUT = 1           ///< @var : OUTPUT
} EHalIO_t;


//********************************************************
/*! @struct                                              */
//********************************************************
typedef struct {
    unsigned long           base;
    int                     fd;         // "/dev/mem" のファイルデスクリプタ
    void*                   map;        // mmap() の戻り値
    volatile unsigned int*  addr;       // mmap() 後のレジスタの先頭アドレス
} SHalCmnGpio_t;


//********************************************************
/* モジュールグローバル変数                              */
//********************************************************
static SHalCmnGpio_t        g_param;


//********************************************************
/* 関数プロトタイプ宣言                                  */
//********************************************************
static void         InitParam( void );
static EHalBool_t   InitReg( void );
static EHalBool_t   Config( unsigned char pin, EHalIO_t mode );




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
    g_param.base = GPIO_BASE;
    g_param.fd = -1;
    g_param.map = (void*)-1;
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
    EHalBool_t      ret = EN_FALSE;

    g_param.fd = open( "/dev/mem", O_RDWR | O_SYNC );
    if( g_param.fd < 0 )
    {
        perror( "Failed to open /dev/mem, try change permission." );
        return ret;
    }

    g_param.map = mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        g_param.fd,
        g_param.base
    );

    if( g_param.map == MAP_FAILED )
    {
        perror( "mmap()" );
        close( g_param.fd );
        return ret;
    }

    g_param.addr = (volatile unsigned int *)g_param.map;
    ret = EN_TRUE;
    return ret;
}


/**************************************************************************//*!
 * @brief     GPIO 設定レジスタへアクセスするためにメモリアドレスを mmap する。
 * @attention なし。
 * @note      mmap で GPIO(物理メモリ) を gpio->map(仮想メモリ) に対応づける。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    EN_TRUE : 成功, EN_FALSE : 失敗
 *************************************************************************** */
EHalBool_t
HalCmnGpio_Init(
    void
){
    EHalBool_t      ret = EN_FALSE;

    InitParam();
    ret = InitReg();

    return ret;
}


/**************************************************************************//*!
 * @brief     GPIO レジスタのメモリアドレスを munmap する。
 * @attention なし。
 * @note      OpenGPIO() で呼んだ open()/mmap() を munmap()/close() する。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
void
HalCmnGpio_Fini(
    void
){
    munmap( g_param.map, BLOCK_SIZE );
    close( g_param.fd );
    return;
}


/**************************************************************************//*!
 * @brief     GPIO を出力 or 入力設定する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    EN_TRUE : 成功, EN_FALSE : 失敗
 *************************************************************************** */
static EHalBool_t
Config(
    unsigned char   pin,                ///< [in] 設定する pin 番号 GPIO00 ～ GPIO27
    EHalIO_t        mode                ///< [in] 設定するモード ( INPUT=0, OUTPUT=1 )
){
    EHalBool_t      ret = EN_FALSE;

    unsigned char   index = 0;          // mmap() 後のレジスタの先頭アドレスからのインデックス
    unsigned char   shift = 0;          // 対象の pin を設定するための左シフト回数
    unsigned int    mask = 0x00000000;  // レジスタの中身をマスクするための変数
    volatile unsigned int   *addr;      // 対象 pin の設定レジスタのアドレス
    unsigned int    data = 0x00000000;  // レジスタに書き込む値

    if( pin < 0 || 27 < pin )
    {
        perror( "pin number is out of range." );
        return ret;
    }

    index = pin / 10;
    shift = (pin % 10) * 3;
    mask  = ~( 0x7 << shift ) & 0x3FFFFFFF; // 対象の 3bit を 0 でマスクする

    // 対象 pin の設定レジスタのアドレスを求める
    addr = g_param.addr + index;

    // 設定レジスタにセットする値を求める
    data = ( *addr & mask );                // 設定レジスタを読み出して対象の 3bit 部分だけ 0 でマスクする
    data |= ( (mode & 0x7) << shift );      // 0 でマスクしたビット位置に mode の値をセットする

    // 対象 pin の設定レジスタの中身を書き換える
//    printf( "[0x%p] : 0x%08X : 0x%08X \n", addr, mask, data );
    *addr = data;
    ret = EN_TRUE;
    return ret;
}


/**************************************************************************//*!
 * @brief     指定した pin に LOW or HIGH を出力する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    EN_TRUE : 成功, EN_FALSE : 失敗
 *************************************************************************** */
EHalBool_t
HalCmnGpio_Set(
    unsigned char       pin,    ///< [in] 出力 pin 番号 GPIO00 ～ GPIO27
    EHalOputputLevel_t  value   ///< [in] EN_LOW=0、EN_HIGH=1
){
    EHalBool_t          ret = EN_FALSE;

    ret = Config( pin, EN_OUTPUT );
    if( ret == EN_FALSE )
    {
        perror( "pin number is out of range." );
        return ret;
    }

    switch( value )
    {
    case EN_LOW  : *(g_param.addr + 10) = ( 0x1 << pin ); break;  // LOW 出力
    case EN_HIGH : *(g_param.addr +  7) = ( 0x1 << pin ); break;  // HIGH 出力
    default      : perror( "please set EN_LOW or EN_HIGH." ); break;
    }

    ret = EN_TRUE;
    return ret;
}


/**************************************************************************//*!
 * @brief     指定した pin の入力の LOW or HIGH を取得する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    EN_TRUE : HIGH 入力, EN_FALSE : LOW 入力
 *************************************************************************** */
EHalBool_t
HalCmnGpio_Get(
    unsigned char       pin     ///< [in] 入力 pin 番号 GPIO00 ～ GPIO27
){
    unsigned int        data = 0x00000000;
    EHalBool_t          ret = EN_FALSE;

    ret = Config( pin, EN_INPUT );
    if( ret == EN_FALSE )
    {
        perror( "pin number is out of range." );
        return ret;
    }

    data = *(g_param.addr + 13) & ( 0x1 << pin );

    if( data != 0 )
    {
        ret = EN_FALSE;
    } else
    {
        ret = EN_TRUE;
    }

    return ret;
}


#ifdef __cplusplus
    }
#endif

