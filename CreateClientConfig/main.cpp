#include "pch.h"



int main()
{
    winrt::init_apartment();
    
	std::wcout << L"Hallo" << std::endl;

    std::wstring clientId = L"CPP-CLIENT-001";

    DATA_BLOB inputBlob;
    inputBlob.pbData = reinterpret_cast<BYTE*>(const_cast<wchar_t*>(clientId.c_str()));

    inputBlob.cbData = static_cast<DWORD>((clientId.size() + 1) * sizeof(wchar_t));

    DATA_BLOB outputBlob;

    BOOL ok = CryptProtectData(
        &inputBlob,
        L"ImpulsAufKurs ClientId",
        nullptr,
        nullptr,
        nullptr,
        0,
        &outputBlob
    );

    if (!ok)
    {
        std::wcout << L"CryptProtectData fehlgeschlagen.\n";
        return 1;
    }

    std::wstring folder = std::wstring(_wgetenv(L"LOCALAPPDATA")) + L"\\ImpulsAufKurs";

    std::filesystem::create_directories(folder);

    std::wstring filePath = folder + L"\\client.dat";

    std::ofstream file(filePath, std::ios::binary);

    file.write(reinterpret_cast<char*>(outputBlob.pbData), outputBlob.cbData);

    file.close();

    LocalFree(outputBlob.pbData);

    std::wcout << L"ClientId wurde verschluesselt gespeichert:\n";
    std::wcout << filePath << std::endl;
    
	system("pause"); 

    return 0;
}
