#ifndef TCP_H
#define TCP_H

#include <QObject>
#include <QWidget>
#include <QtCore>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#define SAP_STATE_WORD_NUM 4
#define TARGET_NUM 56
#define TARGET_WORD_NUM 9

/**
 * @def MAX_TMS_ADDRESS
 * @brief Max address of 32-bit words in TMS (MSB - 0xDDDDCCCC & 0xBBBBAAAA & 0xYYYYXXXX & 0xFFFFEEEE - LSB)
 */
#define MAX_TMS_ADDRESS SAP_STATE_WORD_NUM + TARGET_NUM * TARGET_WORD_NUM

/**
 * @def MAX_FPGA_ADDRESS
 * @brief Max address of 16-bit in FPGA (MSB - 0xDDDD & 0xCCCC & 0xBBBB & 0xAAAA & 0xYYYY & 0xXXXX & 0xFFFF & 0xEEEE - LSB)
 */
#define MAX_FPGA_ADDRESS MAX_TMS_ADDRESS * sizeof(uint32_t)/sizeof(uint16_t)

/**
 * @def ESP_SPI_BUF_SIZE
 * @brief Размер кольцевого буфера приема по SPI (от ПЛИС)
 * + 512 на всякий случай
 */
#define ESP_SPI_BUF_SIZE MAX_FPGA_ADDRESS * sizeof(uint16_t)/* + 512*/

/**
 * @def ESP_UART_BUF_SIZE
 * @brief Размер кольцевого буфера приема по UART (от ESP)
 */
#define ESP_UART_BUF_SIZE 1024

#define CURRENT_TIME chrono::steady_clock::now()

//#define TIMER_START() do { DURATION_CALCULATION::start_time = CURRENT_TIME; } while(0)
//#define TIMER_STOP() do { DURATION_CALCULATION::stop_time = CURRENT_TIME; } while(0)

//#define DURATION_ms(start, stop) chrono::duration_cast<chrono::milliseconds>(stop - start).count()
//#define CALCULATE_DURATION_ms DURATION_ms(DURATION_CALCULATION::start_time, DURATION_CALCULATION::stop_time)
//#define DURATION_us(start, stop) chrono::duration_cast<chrono::microseconds>(stop - start).count()
//#define CALCULATE_DURATION_us DURATION_us(DURATION_CALCULATION::start_time, DURATION_CALCULATION::stop_time)
//#define DURATION_ns(start, stop) chrono::duration_cast<chrono::nanoseconds>(stop - start).count()
//#define CALCULATE_DURATION_ns DURATION_ns(DURATION_CALCULATION::start_time, DURATION_CALCULATION::stop_time)

//using namespace std;
//namespace DURATION_CALCULATION {
//auto start_time = CURRENT_TIME;
//auto stop_time = CURRENT_TIME;
//}

/**
 * @enum _TCP_Packet_Type
 * @brief
 */
typedef enum _TCP_Packet_Type
{
	FixedAddressRW,
	ReadFrom306,
} _TCP_Packet_Type;

/**
 * @struct _TCP_Packet
 * @brief Пакет для передачи на STP по TCP, UART
 */
typedef struct _TCP_Packet
{
	uint8_t Type;
	void* Data;
} _TCP_Packet;



#endif // TCP_H
