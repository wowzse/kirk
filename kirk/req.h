#pragma once

#include <optional>
#include <string>
#include <windows.h>
#include <iostream>

#include <winhttp.h>

#pragma comment(lib, "winhttp.lib")

inline std::optional<std::string> httpReq(std::wstring host, std::wstring path) {
    std::string str = "";

    HINTERNET hS = WinHttpOpen(
        L"reqclient", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0
    );
    if (!hS) { return std::nullopt; }

    HINTERNET hC = WinHttpConnect(
        hS, host.data(), INTERNET_DEFAULT_HTTPS_PORT, 0
    );
    if (!hC) { WinHttpCloseHandle(hS); return std::nullopt; }

    HINTERNET hR = WinHttpOpenRequest(
        hC, L"GET", path.data(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE
    );
    if (!hR) { WinHttpCloseHandle(hC); WinHttpCloseHandle(hS); return std::nullopt; }

    bool ok = WinHttpSendRequest(hR, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    if (ok) ok = WinHttpReceiveResponse(hR, nullptr);

    if (!ok) {
        WinHttpCloseHandle(hR);
        WinHttpCloseHandle(hC);
        WinHttpCloseHandle(hS);
        return std::nullopt;
    }

    DWORD size = 0;

    do {
        if (!WinHttpQueryDataAvailable(hR, &size)) {
            std::cout << "NO data recv for request" << std::endl;
            break;
        }
        if (size == 0) {
            if (str.empty()) {
                std::cout << "no data recv but successful request to ";
                std::wcout << host + path << std::endl;
            }
            break;
        };

        std::string buff(size, '\0');
        DWORD downloaded = 0;

        if (!WinHttpReadData(hR, buff.data(), size, &downloaded)) {
            std::cout << "failed to read request data" << std::endl;
            break;
        }
        str.append(buff.data(), downloaded);
    } while (size > 0);

    WinHttpCloseHandle(hR);
    WinHttpCloseHandle(hC);
    WinHttpCloseHandle(hS);

    return str;
}
