

#include "rtl-sdr.h"
#include <iostream>
#include <stdint.h>
#include <string>


int main() {
	
	uint32_t devCount = rtlsdr_get_device_count();
	
	if (devCount == 0) {
		std::cout << "Device is not connected!\n";
		
	}
	else
	{
		for (uint32_t i = 0; i < devCount; i++) {
			std::string devName = rtlsdr_get_device_name(i);
			std::cout << "Device( " << i << " ): " << devName << std::endl;
		}
		uint32_t devNum = 0;
		if (devCount > 1) {
				std::cout<<"Please enter the device number: ";
				std::cin >> devNum;
		}

		std::cout << "Opening device #" << devNum << std::endl;

		rtlsdr_dev_t* RTLDevice;

		if (rtlsdr_open(&RTLDevice, devNum) != 0) {
			std::cout << "Can't open the device!\n";

		}
		else {
			int32_t gains = rtlsdr_get_tuner_gains(RTLDevice, NULL);
			int* gain = new int[gains];
			rtlsdr_get_tuner_gains(RTLDevice, gain);


			int tunerType = rtlsdr_get_tuner_type(RTLDevice);
			std::string tunerTypeStr;
			switch (tunerType)
			{
				case rtlsdr_tuner::RTLSDR_TUNER_E4000:
				tunerTypeStr = "E4000";
				break;

				case rtlsdr_tuner::RTLSDR_TUNER_FC0012:
				tunerTypeStr = "FC0012";
				break;

				case rtlsdr_tuner::RTLSDR_TUNER_FC0013:
				tunerTypeStr = "FC0013";
				break;

				case rtlsdr_tuner::RTLSDR_TUNER_FC2580:
				tunerTypeStr = "FC2580";
				break;

				case rtlsdr_tuner::RTLSDR_TUNER_R820T:
				tunerTypeStr = "R820T";
				break;

				case rtlsdr_tuner::RTLSDR_TUNER_R828D:
				tunerTypeStr = "R828D";
				break;

				case rtlsdr_tuner::RTLSDR_TUNER_UNKNOWN:
				tunerTypeStr = "UNKNOWN";
				break;

				default:
				tunerTypeStr = "Undefined";
				break;
			}
			std::cout << "Tuner type is: " <<  tunerTypeStr << std::endl;
			std::cout << "Tuned to: " << rtlsdr_get_center_freq(RTLDevice) << " Hz" << std::endl;
			std::cout << "Sample rate: " << rtlsdr_get_sample_rate(RTLDevice) << " Hz" << std::endl;
			


		}


	}
	
	system("pause");
	return 0;
}

