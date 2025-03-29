#include <Windows.h>
#include <iostream>
#include <string>
#include <SetupAPI.h>
#include <initguid.h>
#include <devguid.h>

using namespace std;

#pragma comment(lib, "setupapi.lib")

int main()
{
	HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_USB, 0, 0, DIGCF_PRESENT);

	if (deviceInfoSet == INVALID_HANDLE_VALUE)
	{
		cout << "Eroare" << endl;
		return 1;
	}

	SP_DEVINFO_DATA deviceInfoData;
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	cout << "Dispozitive conectate prin USB: \n\n";

	for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++)
	{
		char deviceName[256] = { 0 };

		if (SetupDiGetDeviceRegistryPropertyA(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName,
			sizeof(deviceName), NULL));
		{
			cout << "Dispozitiv: " << deviceName << endl;
		}
	}

	SetupDiDestroyDeviceInfoList(deviceInfoSet);

	return 0;
}