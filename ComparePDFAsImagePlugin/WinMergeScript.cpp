// WinMergeScript.cpp : Implementation of CWinMergeScript
#include "stdafx.h"
#pragma warning(disable : 28251)
#include "Config.h"
#include "WinMergeScript.h"
#include "resource.h"

#include <shcore.h>
#pragma comment(lib, "windowsapp")

// ------------------------------------------------------------------
//
// ------------------------------------------------------------------
static winrt::Windows::Foundation::IAsyncAction PdfRenderAsync(LPCWSTR path, FLOAT scale, LPCWSTR destFolder)
{
    using namespace winrt::Windows::Storage;
    using namespace winrt::Windows::Data::Pdf;
    using namespace winrt::Windows::Storage::Streams;
    winrt::apartment_context ui_thread;
    // co_await winrt::resume_background(); // Return control; resume on thread pool.

    auto stream{co_await FileRandomAccessStream::OpenAsync(path, FileAccessMode::Read)};

    auto doc{co_await PdfDocument::LoadFromStreamAsync(stream)};

    uint32_t pageCount{doc.PageCount()};
    for (UINT pageIndex = 0; pageIndex < pageCount; pageIndex++)
    {
        WCHAR dest[MAX_PATH]{};
        swprintf_s(dest, L"%s\\page_%u.png", destFolder, pageIndex);

        auto destFile{co_await FileRandomAccessStream::OpenAsync(
            dest, FileAccessMode::ReadWrite, StorageOpenOptions::None, FileOpenDisposition::CreateNew)};

        auto page{doc.GetPage(pageIndex)};
        auto size{page.Size()};
        PdfPageRenderOptions renderOptions{};
        renderOptions.BitmapEncoderId(GUID_ContainerFormatPng);
        renderOptions.DestinationWidth(static_cast<UINT>(size.Width * scale));
        renderOptions.DestinationHeight(static_cast<UINT>(size.Height * scale));

        co_await page.RenderToStreamAsync(destFile, renderOptions);
        co_await destFile.FlushAsync();
        destFile.Close();
    }
     co_await ui_thread; // Switch back to calling context.
}

IFACEMETHODIMP CWinMergeScript::get_PluginEvent(/*[out, retval]*/ BSTR *pVal)
{
    *pVal = SysAllocString(L"FILE_FOLDER_PACK_UNPACK");
    return S_OK;
}

IFACEMETHODIMP CWinMergeScript::UnpackFolder(
    /* [in] */ BSTR fileSrc,
    /* [in] */ BSTR folderDst, VARIANT_BOOL *pbChanged, INT *pSubcode,
    /* [retval][out] */ VARIANT_BOOL *pbSuccess)
{
    if (fileSrc == nullptr || folderDst == nullptr)
        return E_INVALIDARG;

    *pbSuccess = VARIANT_FALSE;
    auto config = Config::Load();

    try
    {
        PdfRenderAsync(fileSrc, config->scale(), folderDst).get(); // wait for complete;
    }
    catch (const winrt::hresult_error &hr)
    {
        return hr.code();
    }
    catch (...)
    {
        return E_FAIL;
    }

    *pbChanged = VARIANT_TRUE;
    *pSubcode = 0;
    *pbSuccess = VARIANT_TRUE;
    return S_OK;
}

IFACEMETHODIMP CWinMergeScript::ShowSettingsDialog(VARIANT_BOOL *pbHandled)
{
    auto result =
        DialogBoxParam(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDD_DIALOG1), nullptr, &SettingDlgProc, 0);

    if (result == -1)
        return HRESULT_FROM_WIN32(GetLastError());

    *pbHandled = (result == IDOK) ? VARIANT_TRUE : VARIANT_FALSE;
    return S_OK;
}
