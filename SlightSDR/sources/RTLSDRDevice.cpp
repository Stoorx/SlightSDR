/**
 *		RTLSDRDevice
 *		RTLSDRLIB wrapper
 *		By Stoorx
 *		github.com/Stoorx
 */

#include "RTLSDRDevice.h"
#include <stdint.h>
#include "rtl-sdr.h"
#include <exception>



namespace SlightSDR {


	const uint32_t RTLSDRDevice::getDeviceCount(void)
	{
		return rtlsdr_get_device_count();
	}

	const std::string RTLSDRDevice::getDeviceName(const uint32_t index)
	{
		return std::string(rtlsdr_get_device_name(index));
	}

	void RTLSDRDevice::getUsbStrings(uint32_t index, std::string& manufact, std::string& product, std::string& serial)
	{
		char* tmpManufact = new char[256];
		char* tmpProduct = new char[256];
		char* tmpSerial = new char[256];

		if (rtlsdr_get_device_usb_strings(index, tmpManufact, tmpProduct, tmpSerial) != 0) {
			throw std::exception("ERROR: USB string was not recieved.");
		}
		
		manufact = tmpManufact;
		product = tmpProduct;
		serial = tmpSerial;
		
		delete[] tmpManufact;
		delete[] tmpProduct;
		delete[] tmpSerial;
	}

	const int32_t RTLSDRDevice::getIndexBySerial(const std::string & serial)
	{
		int32_t tmpIndex = rtlsdr_get_index_by_serial(serial.data());
		if (tmpIndex < 0) {
			throw std::exception("ERROR: at getIndexBySerial", tmpIndex);
		}
		return tmpIndex;
	}

	RTLSDRDevice::RTLSDRDevice(uint32_t index)
	{
		// Device opening
		rtlsdr_open(&_device, index);
		
		// Get tuner gains
		uint32_t gainsCount = rtlsdr_get_tuner_gains(_device, NULL);
		if (gainsCount <= 0) {
			throw std::exception("ERROR: Tuner gains error.");
		}
		_gains.resize(gainsCount);
		rtlsdr_get_tuner_gains(_device, _gains.data());

		
	}

	RTLSDRDevice::~RTLSDRDevice()
	{
		rtlsdr_close(_device);
	}

	const std::string RTLSDRDevice::getManufacturer() const 
	{
		char* tmpManufacturer = new char[256];
		rtlsdr_get_usb_strings(_device, tmpManufacturer, NULL, NULL);

		std::string manufacturer(tmpManufacturer);
		
		delete[] tmpManufacturer;
		
		return manufacturer;
	}

	const uint32_t RTLSDRDevice::getCenterFrequency() const
	{
		uint32_t tmpFreq = rtlsdr_get_center_freq(_device);
		if (tmpFreq == 0) {
			throw std::exception("Unable to get center frequency!");
		}

		return tmpFreq;
	}

	const int32_t RTLSDRDevice::getFrequencyCorrection() const
	{
		return rtlsdr_get_freq_correction(_device);
	}

	const RTLSDRDevice::TunerType RTLSDRDevice::getTunerType() const
	{
		TunerType tmpType = (TunerType)rtlsdr_get_tuner_type(_device);
		if (tmpType == TunerType::UNKNOWN) {
			throw std::exception("ERROR: Unknown tuner type or an other tuner error detected.");
		}
		return tmpType;
	}

	const int32_t RTLSDRDevice::getTunerGain() const
	{
		int32_t tmpGain = rtlsdr_get_tuner_gain(_device);
		if (tmpGain == 0) {
			throw std::exception("ERROR: Unable to get tuner gain.");
		}

		return tmpGain;
	}

	const int32_t RTLSDRDevice::getSampleRate() const
	{
		uint32_t tmpRate = rtlsdr_get_sample_rate(_device);
		if (tmpRate == 0) {
			throw std::exception("Unable to get sample rate.");
		}
		return tmpRate;
	}

	const RTLSDRDevice::RTLDirectSamplingMode RTLSDRDevice::getDirectSamplingMode() const
	{
		int32_t tmpMode = rtlsdr_get_direct_sampling(_device);
		if (tmpMode == -1) {
			throw std::exception("Unable to get Direct sampling mode.");
		}
		return (RTLDirectSamplingMode)tmpMode;
	}

	const RTLSDRDevice::OffsetTuningMode RTLSDRDevice::getOffsetTuningMode() const
	{
		int32_t tmpMode = rtlsdr_get_offset_tuning(_device);
		if (tmpMode == -1) {
			throw std::exception("Unable to get offset tuning mode");
		}
		return (OffsetTuningMode)tmpMode;
	}

	void RTLSDRDevice::setFrequencyCorrection(int32_t ppm)
	{
		if (rtlsdr_set_freq_correction(_device, ppm) != 0) {
			throw std::exception("Unable to set frequency correction.");
		}
	}

	void RTLSDRDevice::setCenterFrequency(uint32_t frequency)
	{
		if (rtlsdr_set_center_freq(_device, frequency) != 0) {
			throw std::exception("Can't set center frequency.");
		}
	}

	void RTLSDRDevice::setTunerGain(int32_t gain)
	{
		if (rtlsdr_set_tuner_gain(_device, gain) != 0) {
			throw std::exception("ERROR: Set tuner gain is not success");
		}
	}

	void RTLSDRDevice::setTuneGainMode(TunerGainMode mode)
	{
		if (rtlsdr_set_tuner_gain_mode(_device, (uint32_t)mode) != 0) {
			throw std::exception("Unable to set tuner gain mode.");
		}
	}

	void RTLSDRDevice::setSampleRate(uint32_t rate)
	{
		uint32_t commandReply = rtlsdr_set_sample_rate(_device, rate);
		if (commandReply != 0) {
			if (commandReply == -EINVAL) {
				throw std::exception("Set sample rate: invalid sample rate.");
			}
			else {
				throw std::exception("Set sample rate: unable to do it.");
			}
		}
	}

	void RTLSDRDevice::setDirectSamplingMode(RTLDirectSamplingMode mode)
	{
		if (rtlsdr_set_direct_sampling(_device, (uint32_t)mode) != 0) {
			throw std::exception("Unable to set Direct sampling mode.");
		}
	}

	void RTLSDRDevice::setOffsetTuningMode(OffsetTuningMode mode)
	{
		if (rtlsdr_set_offset_tuning(_device, (uint32_t)mode) != 0) {
			throw std::exception("Unable to set offset tuning");
		}
	}

	void RTLSDRDevice::setTestMode(RTLTestMode mode)
	{
		if (rtlsdr_set_testmode(_device, (uint32_t)mode) != 0) {
			throw std::exception("Can't set test mode.");
		}
	}

	void RTLSDRDevice::resetBuffer()
	{
		rtlsdr_reset_buffer(_device);
	}

	void RTLSDRDevice::readSamplesSync(uint8_t * buffer, uint32_t len)
	{
		uint32_t bytesRead;
		rtlsdr_read_sync(_device, buffer, len, (int*)&bytesRead);

		if (bytesRead < len) {
			throw std::exception("Short read, samples lost.");
		}
	}

	void RTLSDRDevice::waitAsync(rtlsdr_read_async_cb_t callBack, void * additionalContext)
	{
		if (rtlsdr_wait_async(_device, callBack, additionalContext) != 0) {
			throw std::exception("Can't wait async.");
		}
	}

	void RTLSDRDevice::readAsync(rtlsdr_read_async_cb_t callBack, uint32_t buffNum, uint32_t buffLen, void* additionalContext)
	{
		if (rtlsdr_read_async(_device, callBack, additionalContext, buffNum, buffLen) != 0) {
			throw std::exception("Can't read async.");
		}
	}

	void RTLSDRDevice::cancelAsyncPending()
	{
		if (rtlsdr_cancel_async(_device) != 0) {
			throw std::exception("Can't cancel async pending");
		}
	}

	void RTLSDRDevice::readAsyncCallBack(uint8_t * buffer, uint32_t lengh, void * additionalContext)
	{
		std::vector<uint8_t> tmpData(lengh);
		for (uint32_t i = 0; i < lengh; ++i) {
			tmpData[i] = buffer[i];
		}

		{
			std::lock_guard<std::mutex> lock(_sampleQueueMutex);
			_sampleQueue.push(std::move(tmpData));
		}
	}

	std::vector<uint8_t> RTLSDRDevice::getSamples()
	{
		std::lock_guard<std::mutex> lock(_sampleQueueMutex);
		std::vector<uint8_t> tmpData(std::move(_sampleQueue.front()));
		_sampleQueue.pop();

		return tmpData;
	}

	void RTLSDRDevice::readDeviceEEPROM(uint8_t * data, uint8_t offset, uint16_t lengh)
	{
		int32_t requestResult = rtlsdr_read_eeprom(_device, data, offset, lengh);
		if (requestResult < 0) {
			if (requestResult == -1) {
				throw std::exception("EEPROM: Device handle is invalid.");
			}
			else if (requestResult == -2) {
				throw std::exception("EEPROM size is exceeded");
			}
			else if (requestResult == -3) {
				throw std::exception("EEPROM was not found.");
			}

		}
	}

	void RTLSDRDevice::writeDeviceEEPROM(uint8_t * data, uint8_t offset, uint16_t lengh)
	{
		int32_t requestResult = rtlsdr_write_eeprom(_device, data, offset, lengh);
		if (requestResult < 0) {
			if (requestResult == -1) {
				throw std::exception("EEPROM: Device handle is invalid.");
			}
			else if (requestResult == -2) {
				throw std::exception("EEPROM size is exceeded");
			}
			else if (requestResult == -3) {
				throw std::exception("EEPROM was not found.");
			}
		}
	}

	void RTLSDRDevice::setTunerAutoGainControlMode(TunerAutoGainControl mode)
	{
		if (rtlsdr_set_agc_mode(_device, (uint32_t)mode) != 0) {
			throw std::exception("Unable to set AGC mode.");
		}
	}

}