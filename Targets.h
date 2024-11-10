#ifndef TARGETS_H
#define TARGETS_H

#include <stdint.h>
#include <QVector>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#pragma pack(push,1)
typedef struct {
    uint32_t Visota             :15;
    uint32_t reserv             :1;
    uint32_t Empty              :16;
} _Periodical_formular_W5;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t reserv             :1;
    uint32_t VzaimnZash         :1;
    uint32_t IzluchZPS          :1;
    uint32_t IzluchPPS          :1;
    uint32_t VSKStatus          :2;
    uint32_t CU_quit            :1;
	uint32_t AVT_quit           :1;
    uint32_t StationModes       :2;
    uint32_t BCVM_Connection    :1;
    uint32_t FHS_Enable         :1;
    uint32_t RHS_Enable         :1;
    uint32_t reserv2            :3;
    uint32_t Empty              :16;
} _Periodical_formular_W6;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t m302_1_obsl        :3;
    uint32_t m302_0_obsl        :3;
    uint32_t reserv             :10;
    uint32_t Empty              :16;
} _Periodical_formular_W7;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t m302_1_neobsl      :5;
    uint32_t m302_0_neobsl      :5;
    uint32_t reserv             :6;
    uint32_t Empty              :16;
} _Periodical_formular_W8;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct
{
	_Periodical_formular_W5 W5;
	_Periodical_formular_W6 W6;
	_Periodical_formular_W7 W7;
	_Periodical_formular_W8 W8;
} _Periodical_formular;
#pragma pack(pop)

//----------------------------------------------------------

#pragma pack(push,1)
typedef struct {
    uint32_t m302num            :3;
    uint32_t semisphere         :1;
    uint32_t WorkingFlag        :1;
    uint32_t Reserve            :11;
    uint32_t Empty              :16;
} _SignalParam_formular_W2;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t Carrier            :15;
    uint32_t Reserve            :1;
    uint32_t Empty              :16;
} _SignalParam_formular_W3;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t DlitImp            :15;
    uint32_t Reserve            :1;
    uint32_t Empty              :16;
} _SignalParam_formular_W4;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t PulsePeriod_ml     :15;
    uint32_t Reserve            :1;
    uint32_t Empty              :16;
} _SignalParam_formular_W5;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t PulsePeriod_st     :7;
    uint32_t Amplitude          :8;
    uint32_t Reserve            :1;
    uint32_t Empty              :16;
} _SignalParam_formular_W6;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t Signal_type        :3;
    uint32_t EtapRaboty         :3;
    uint32_t reserv             :10;
    uint32_t Empty              :16;
} _SignalParam_formular_W7;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t Spectrum           :9;
    uint32_t reserv             :7;
    uint32_t Empty              :16;
} _SignalParam_formular_W8;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t PeriodPovtPachki   :11; // ?!
    uint32_t TipPomehi          :4;
    uint32_t reserv             :1;
    uint32_t Empty              :16;
} _SignalParam_formular_W9;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
    uint32_t DlitPachki         :11;
    uint32_t reserv             :5;
    uint32_t Empty              :16;
} _SignalParam_formular_W10;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
	_SignalParam_formular_W2 W2;
	_SignalParam_formular_W3 W3;
	_SignalParam_formular_W4 W4;
	_SignalParam_formular_W5 W5;
	_SignalParam_formular_W6 W6;
	_SignalParam_formular_W7 W7;
	_SignalParam_formular_W8 W8;
	_SignalParam_formular_W9 W9;
	_SignalParam_formular_W10 W10;
} _SignalParam_formular;
#pragma pack(pop)

//--------------------------------------------------------------------------------------------

typedef struct {
	uint32_t L281_1_1           :1;
    uint32_t m101N1             :1;
    uint32_t m101N2             :1;
    uint32_t m102N1             :1;
    uint32_t m102N2             :1;
    uint32_t m104               :1;
    uint32_t MSP_02_02          :1;
    uint32_t MSP_02_01          :1;
    uint32_t L281_1_7           :1;
    uint32_t PK1_2_2            :1;
    uint32_t PK1_2_1            :1;
    uint32_t SAP                :1;
    uint32_t Reserve            :4;
    uint32_t Empty              :16;
} _VSKRes_formular_W2;

typedef struct {
    uint32_t L_281_1_3          :1;
    uint32_t m301N2             :1;
    uint32_t m301N1             :1;
    uint32_t m302N2             :1;
    uint32_t m302N1             :1;
    uint32_t m303N2             :1;
    uint32_t m303N1             :1;
    uint32_t m305               :1;
    uint32_t m306               :1;
    uint32_t m307               :1;
    uint32_t L_281_1_6ZPS       :1;
    uint32_t L_281_1_6PPS       :1;
    uint32_t RSV                :4;
    uint32_t Empty              :16;
} _VSKRes_formular_W3;

typedef struct {
	uint32_t L281_1_4           :1;
    uint32_t m402               :1;
    uint32_t m403N2             :1;
    uint32_t m403N1             :1;
    uint32_t m405               :1;
    uint32_t m406               :1;
    uint32_t m407               :1;
    uint32_t m408               :1;
    uint32_t RSV                :8;
    uint32_t Empty              :16;
} _VSKRes_formular_W4;

typedef struct {
    uint32_t L_281_1_3          :1;
    uint32_t m301N4             :1;
    uint32_t m301N3             :1;
    uint32_t m302N4             :1;
    uint32_t m302N3             :1;
    uint32_t m303N4             :1;
    uint32_t m303N3             :1;
    uint32_t m305_1             :1;
    uint32_t m306_1             :1;
    uint32_t m307_1             :1;
    int32_t Word_Valid          :1;
    uint32_t RSV                :5;
    uint32_t Empty              :16;
} _VSKRes_formular_W5;

typedef struct {
	_VSKRes_formular_W2 W2;
	_VSKRes_formular_W3 W3;
	_VSKRes_formular_W4 W4;
	_VSKRes_formular_W5 W5;
	//	unsigned CheckSum; [?????]
} _VSKRes_formular;

extern _VSKRes_formular VSKRes_formular;

class StructFormularFrom306Mod //реализацию сунул в мейн окно
{
public:
    StructFormularFrom306Mod();
    ~StructFormularFrom306Mod();
    void setVSK_Formular(QByteArray, unsigned long long);
    void setTargets(QByteArray, unsigned long long);
    void setSAPStatus_Formular(QByteArray, unsigned long long);
    _VSKRes_formular getVSK_Formular(void);
    _SignalParam_formular getTargets_Formular(void); //возможно позже добавить умный указатель но это не точно, чтоб получать конкретный или если -1 то получаем весь пакет
    //для него ещё нужно будет создать выдачу размерности заполненного вектора, чтоб наверняка знать сколько читать
    _Periodical_formular getSAPStatus_Formular(void);

    void setSizeVector(size_t newSizeVector);
    size_t getSizeVector() const;
    QVector<_SignalParam_formular> getTargets() const;

private:
    _VSKRes_formular VSKRes; //если нет конструктора, то наверное и динамические массивы ни к чему
    QVector<_SignalParam_formular> Targets; //если нет конструктора, то наверное и динамические массивы ни к чему
    size_t sizeVector;
    _Periodical_formular SAPStatus; //если нет конструктора, то наверное и динамические массивы ни к чему

};







/**
 * @struct _TimerStart_struct
 */
#pragma pack(push,1)
typedef struct _TimerStart_struct
{
	uint32_t TimerStart1;
	uint32_t TimerStart2           :2;
} _TimerStart_struct;
#pragma pack(pop)

/**
 * @struct _DescrWordStruct
 */
#pragma pack(push,1)
typedef struct _DescrWordStruct
{
//	_word0 Word0;
//	_word1 Word1;
//	_word2 Word2;
//	_word3 Word3;
//	_TMS_Settings TMS_Settings;

//----------Word 2 (0)----------//

	uint32_t Archived           :1;
	uint32_t Duration_Jump           :1;
	uint32_t Period_Jump           :1;
	uint32_t Start_Calculation           :1;
	uint32_t Validation           :1;
	uint32_t Reserved2           :11;
	uint16_t SignalDuration;
	uint32_t AveragePowerOfPulses;

	//----------Word 3 (1) ----------//

	uint32_t NumberPulses           :8;
	uint32_t FilterNumber           :4;
	int16_t AverageFrequencyOfPulses;
	uint32_t AveragePeriodPulsesRepetition           :20;
	uint16_t AverageDurationOfPulses;

	//----------Word 4 (2) ----------//

	_TimerStart_struct TimerStart;
	uint32_t           :10;
	uint32_t Confrontation_Right           :2;
	uint32_t Confrontation_Left           :2;
	int16_t Deviation;

	//----------Word 1----------//

	uint32_t FreqPulsesDispersion           :12;
	uint32_t DurationPulsesDispersion           :8;
	uint32_t PeriodPulsesRepetitionDispersion           :8;
	uint32_t Reserved0           :4;
	uint32_t Reserved1;

	//----------TMS settings----------//

	uint8_t IsDiscrFill;
	uint8_t NumberOfDescr;
	uint8_t SintezStepNumber;
	uint8_t IsChirp;
	uint32_t Reserved5;

	int64_t Full_Filter_Freq;

} _DescrWordStruct;
#pragma pack(pop)

extern _DescrWordStruct DescrWordStruct;

#endif // TARGETS_H
