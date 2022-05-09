#pragma once
#include "stdafx.h"

#include <memory>

class Config final
{
    DWORD m_scale{100};
    DWORD m_backgroundColor{0x0FFFFFF};

  public:
    static constexpr LPCWSTR key_Scale{L"Scale"};
    static constexpr LPCWSTR key_BackgroundColor{L"BackgroundColor"};

    static std::unique_ptr<Config> Load();

    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;
    Config(Config &&) = default;
    Config() noexcept
    {
    }
    Config &operator=(Config &&) = default;

    FLOAT scale() const
    {
        return scaleInt() / 100.f;
    }
    DWORD scaleInt() const
    {
        return m_scale;
    }
    UINT backgroundColor() const
    {
        return m_backgroundColor & 0xFFFFFF;
    }
};
