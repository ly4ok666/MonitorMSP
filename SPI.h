#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include "Targets.h"
/**
 * @union _SPI_Data
 * @brief Способы представления данных для пакета SPI_packet_
 */
typedef union _SPI_Data
{
	uint16_t data16;
	uint8_t data8[2];
} _SPI_Data;

/**
 * @enum _RW
 * @brief Read/Write bit enum
 */
typedef enum _RW
{
	R,
	W
} _RW;

/**
 * @struct _SPI_packet
 * @brief Пакет для передачи на ПЛИС по SPI
 */
#pragma pack(push,1)
typedef struct _SPI_Packet
{
	_SPI_Data data;
	uint16_t :2;
	uint16_t address :13;
	uint16_t rw :1;
//	uint16_t nothing;
} _SPI_Packet;
#pragma pack(pop)

#define SAP_STATE_WORD_NUM 4
#define VSK_WORD_NUM 4
#define TARGET_WORD_NUM 9
#define TARGET_NUM 56//56
#define startBit 1
#define maxsizepack (1+sizeof(_Periodical_formular)+sizeof(_SignalParam_formular)*56+sizeof(_VSKRes_formular))

#define WORD_SIZE sizeof(uint16_t)

/**
 * @def MAX_TMS_ADDRESS
 * @brief Max address of 32-bit words in TMS (MSB - 0xDDDDCCCC & 0xBBBBAAAA & 0xYYYYXXXX & 0xFFFFEEEE - LSB)
 */
#define MAX_TMS_ADDRESS (SAP_STATE_WORD_NUM + TARGET_NUM * TARGET_WORD_NUM + VSK_WORD_NUM)

/**
 * @def MAX_FPGA_ADDRESS
 * @brief Max address of 16-bit in FPGA (MSB - 0xDDDD & 0xCCCC & 0xBBBB & 0xAAAA & 0xYYYY & 0xXXXX & 0xFFFF & 0xEEEE - LSB)
 */
#define MAX_FPGA_ADDRESS (MAX_TMS_ADDRESS * sizeof(uint32_t) / sizeof(uint16_t))

/**
 * @def ESP_SPI_BUF_SIZE
 * @brief Размер кольцевого буфера приема по SPI (от ПЛИС)
 */
#define ESP_SPI_BUF_SIZE ((qint64)(MAX_FPGA_ADDRESS * sizeof(uint16_t) + 1))

#endif // SPI_H
