/* 
 * File:   fs_common.h
 * Author: fsedano
 *
 * Created on October 28, 2017, 12:40 PM
 */

#ifndef FS_COMMON_H
#define	FS_COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif


    #define ARRAY_SIZE(x)   (sizeof(x)/sizeof(x[0]))
    typedef struct {
        unsigned char out_bank[3];
        unsigned char in_bank[2];
    } oper_params_t;

    typedef struct {
    } config_params_t;

    #define EEPROM_MAGIC_1_VALUE    0xDE
    #define EEPROM_MAGIC_2_VALUE    0xAD

    enum eeprom_pos {
        EEPROM_MAGIC_1,
        EEPROM_MIN_POSL,
        EEPROM_MIN_POSH,
        EEPROM_MAX_POSL,
        EEPROM_MAX_POSH,
        EEPROM_CENTER_TRIML,
        EEPROM_CENTER_TRIMH,
        EEPROM_PRES_ZEROL,
        EEPROM_PRES_ZEROH,
        EEPROM_POLARITY,
        EEPROM_SPEED_K,
        EEPROM_ELASTIC_KL,
        EEPROM_ELASTIC_KH,
        EEPROM_PRES_KL,
        EEPROM_PRES_KH,
        EEPROM_INVERT_PRES_POLARITY,
        EEPROM_MAGIC_2
    };


#ifdef	__cplusplus
}
#endif

#endif	/* FS_COMMON_H */

