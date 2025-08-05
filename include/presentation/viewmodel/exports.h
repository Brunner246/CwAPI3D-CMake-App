//
// Created by MichaelBrunner on 28/07/2025.
//

#pragma once

#ifdef viewmodel_EXPORTS
#define VM_API __declspec(dllexport)
#else
#define VM_API __declspec(dllimport)
#endif

// don't use dllimport on QObject-based classes!
#ifdef viewmodel_EXPORTS
#define VM_QT_API __declspec(dllexport)
#else
#define VM_QT_API
#endif

// #ifdef viewmodel_EXPORTS
//   #define VM_CLASS_EXPORT Q_DECL_EXPORT
// #else
//   #ifdef Q_MOC_RUN
//     #define VM_CLASS_EXPORT
//   #else
//     #define VM_CLASS_EXPORT Q_DECL_IMPORT
//   #endif
// #endif