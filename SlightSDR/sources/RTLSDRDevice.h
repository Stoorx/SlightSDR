/**
*		RTLSDRDevice
*		RTLSDRLIB wrapper
*		By Stoorx
*		github.com/Stoorx
*/

#pragma once

#include <stdint.h>
#include <string>
#include <exception>
#include <vector>
#include "rtl-sdr.h"
#include <queue>
#include <mutex>



namespace SlightSDR {
	//TODO: IF gain, XTAL set/get
	class RTLSDRDevice {
	public:
		/*Prototypes*/
		enum class TunerType : uint32_t;
		enum class TunerGainMode : uint32_t;
		enum class TunerAutoGainControl : uint32_t;
		//RTL
		enum class RTLDirectSamplingMode : uint32_t;
		enum class OffsetTuningMode : uint32_t;
		enum class RTLTestMode : uint32_t;

		/*Static getters*/
		const static uint32_t getDeviceCount(void);
		const static std::string getDeviceName(const uint32_t index);
		static void getUsbStrings(uint32_t index, std::string& manufact, std::string& product, std::string& serial);
		const static int32_t getIndexBySerial(const std::string& serial);
		
		/*Constructors and destructor*/
		RTLSDRDevice(uint32_t index);
		~RTLSDRDevice();

		/*Getters*/
		const std::string getManufacturer() const;
		const uint32_t getCenterFrequency() const;
		const int32_t getFrequencyCorrection() const;
		const TunerType getTunerType() const;
		const int32_t getTunerGain() const;
		const int32_t getSampleRate() const;
		const RTLDirectSamplingMode getDirectSamplingMode() const;
		const OffsetTuningMode getOffsetTuningMode() const;
		
		/*Setters*/
		//Tuner settings
		void setTunerGain(int32_t gain);
		void setTuneGainMode(TunerGainMode mode);
		void setTunerAutoGainControlMode(TunerAutoGainControl mode);
		//RTL settings
		void setFrequencyCorrection(int32_t ppm);
		void setCenterFrequency(uint32_t frequency);
		void setSampleRate(uint32_t rate);
		void setDirectSamplingMode(RTLDirectSamplingMode mode);
		void setOffsetTuningMode(OffsetTuningMode mode);
		void setTestMode(RTLTestMode mode);

		// BAD!!!!!!
		// TODO: delegates
		typedef void(*rtlsdr_read_async_cb_t)(unsigned char *buf, uint32_t len, void *ctx);

		/*Streming*/
		void resetBuffer();
		void readSamplesSync(uint8_t* buffer, uint32_t len);
		void waitAsync(rtlsdr_read_async_cb_t callBack, void* additionalContext);
		void readAsync(rtlsdr_read_async_cb_t callBack, uint32_t buffNum, uint32_t buffLen, void* additionalContext);
		void cancelAsyncPending();

		/*Callback*/
		//BAD!!!!!
		//TODO: events
		void readAsyncCallBack(uint8_t* buffer, uint32_t lengh, void* additionalContext);
		
		/*Get samples*/
		std::vector<uint8_t> getSamples();
		
		/*EEPROM*/
		void readDeviceEEPROM(uint8_t* data, uint8_t offset, uint16_t lengh);
		void writeDeviceEEPROM(uint8_t* data, uint8_t offset, uint16_t lengh);
		
		/*Constants*/
		//Tuner settings
		enum class TunerType : uint32_t {
			UNKNOWN = 0,
			E4000,
			FC0012,
			FC0013,
			FC2580,
			R820T,
			R828D
		};
		enum class TunerGainMode : uint32_t {
			AUTO = 0,
			MANUAL,
		};
		enum class TunerAutoGainControl : uint32_t {
			DISABLED = 0,
			ENABLED
		};
		//RTL settings
		enum class RTLDirectSamplingMode : uint32_t {
			DISABLED=0,
			I_ADC_ENABLED,
			Q_ADC_ENABLED
		};
		enum class OffsetTuningMode : uint32_t {
			DISABLED = 0,
			ENABLED,
		};
		enum class RTLTestMode : uint32_t {
			DISABLED = 0,
			ENABLED
		};
	private:
		/*Sample queue*/
		//TODO: Thread-Safe queue
		std::queue<std::vector<uint8_t>> _sampleQueue;
		std::mutex _sampleQueueMutex;

		rtlsdr_dev_t* _device;
		std::vector<int32_t> _gains;
	};
}
