/**************************************************************************//*!
 *  @file           main.c
 *  @brief          main() を定義したファイル。
 *  @author         Ryoji Morita
 *  @attention      none.
 *  @sa             none.
 *  @bug            none.
 *  @warning        none.
 *  @version        1.00
 *  @last updated   2019.10.09
 *************************************************************************** */
#ifdef __cplusplus
    extern "C"{
#endif


//********************************************************
/* include                                               */
//********************************************************
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>

#include "hal.h"


//********************************************************
/*! @def                                                 */
//********************************************************
// なし


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
// getopt() で使用
extern char *optarg;
extern int  optind, opterr, optopt;


//********************************************************
/* 関数プロトタイプ宣言                                  */
//********************************************************
static void         Run_Help( void );
static void         Run_Led( char* str );
static void         Run_LedSequence( void );




/**************************************************************************//*!
 * @brief     HELP を表示する。
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
static void
Run_Help(
    void
){
    printf( "\n\r" );
    printf( "  -h, --help                  display the help menu. \n\r" );
    printf( "  -l number, --led=number     control the LED.                  \n\r" );
    printf( "  -s, --sequence              light the LED sequencely.         \n\r" );
    printf( "\n\r" );
    return;
}


/**************************************************************************//*!
 * @brief     LED を実行する
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
static void
Run_Led(
    char*           str     ///< [in] 文字列
){
    unsigned int    num;
    printf( "str = %s \n\r", str );

    sscanf( str, "%X", &num );
    HalLed_Set( num );

    return;
}


/**************************************************************************//*!
 * @brief     LED を順番に点灯する
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
static void
Run_LedSequence(
    void
){
    int             i = 0;
    unsigned int    value = 0x1;

    for( i = 0; i < 26; i++ )
    {
        HalLed_Set( value );
        usleep( 500 * 1000 );
        value = ( value << 1 ) % 0x03FFFFFF;
    }

    return;
}


/**************************************************************************//*!
 * @brief     メイン
 * @attention なし。
 * @note      なし。
 * @sa        なし。
 * @author    Ryoji Morita
 * @return    なし。
 *************************************************************************** */
int main(int argc, char *argv[ ])
{
    int             opt = 0;
    const char      optstring[] = "hl:s";
    const struct    option longopts[] = {
      //{ *name,         has_arg,           *flag, val }, // 説明
        { "help",        no_argument,       NULL,  'h' },
        { "led",         required_argument, NULL,  'l' },
        { "sequence",    no_argument,       NULL,  's' },
        { 0,             0,                 NULL,   0  }, // termination
    };
    int longindex = 0;

    HalCmnGpio_Init();
    HalLed_Init();

    while( 1 )
    {
        opt = getopt_long( argc, argv, optstring, longopts, &longindex );
//      opt = getopt( argc, argv, optstring );
        printf( "optind = %d \n\r", optind );
        printf( "opt    = %c \n\r", opt );

        if( opt == -1 )   // 処理するオプションが無くなった場合
        {
            break;
        } else  if( opt == '?' )  // optstring で指定していない引数が見つかった場合
        {
            printf( "optopt = %c \n\r", optopt );
            break;
        }

        switch( opt )
        {
        case 'h': Run_Help(); break;
        case 'l': Run_Led( optarg ); break;
        case 's': Run_LedSequence(); break;
        default:
            printf( "invalid command/option. : \"%s\" \n\r", argv[1] );
            Run_Help();
        break;
        }
    }

    HalLed_Fini();
    HalCmnGpio_Fini();
    return 0;
}


#ifdef __cplusplus
    }
#endif
