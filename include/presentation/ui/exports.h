//
// Created by MichaelBrunner on 28/07/2025.
//

#pragma once

#ifdef CmdUi_EXPORTS
#define UI_API __declspec(dllexport)
#else
#define UI_API __declspec(dllimport)
#endif

// don't use dllimport on QObject-based classes!
#ifdef CmdUi_EXPORTS
#define UI_API __declspec(dllexport)
#else
#define UI_API
#endif