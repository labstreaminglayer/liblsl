/*
 * Copyright 2010 Vicente J. Botet Escriba
 * Copyright 2015 Andrey Semashev
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef BOOST_WINAPI_LOCAL_MEMORY_HPP_INCLUDED_
#define BOOST_WINAPI_LOCAL_MEMORY_HPP_INCLUDED_

#include <boost/winapi/basic_types.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if BOOST_WINAPI_PARTITION_APP_SYSTEM

#include <boost/winapi/detail/header.hpp>

#if !defined( BOOST_USE_WINDOWS_H )
namespace lslboost { namespace winapi {
typedef HANDLE_ HLOCAL_;
}}

extern "C" {

#if defined (_WIN32_WCE )
BOOST_WINAPI_IMPORT_EXCEPT_WM lslboost::winapi::HLOCAL_ BOOST_WINAPI_WINAPI_CC
LocalAlloc(
    lslboost::winapi::UINT_ uFlags,
    lslboost::winapi::UINT_ uBytes);

BOOST_WINAPI_IMPORT_EXCEPT_WM lslboost::winapi::HLOCAL_ BOOST_WINAPI_WINAPI_CC
LocalReAlloc(
    lslboost::winapi::HLOCAL_ hMem,
    lslboost::winapi::UINT_ uBytes,
    lslboost::winapi::UINT_ uFlags);
#else
BOOST_WINAPI_IMPORT_EXCEPT_WM lslboost::winapi::HLOCAL_ BOOST_WINAPI_WINAPI_CC
LocalAlloc(
    lslboost::winapi::UINT_ uFlags,
    lslboost::winapi::SIZE_T_ uBytes);

BOOST_WINAPI_IMPORT_EXCEPT_WM lslboost::winapi::HLOCAL_ BOOST_WINAPI_WINAPI_CC
LocalReAlloc(
    lslboost::winapi::HLOCAL_ hMem,
    lslboost::winapi::SIZE_T_ uBytes,
    lslboost::winapi::UINT_ uFlags);
#endif

BOOST_WINAPI_IMPORT_EXCEPT_WM lslboost::winapi::HLOCAL_ BOOST_WINAPI_WINAPI_CC LocalFree(lslboost::winapi::HLOCAL_ hMem);
} // extern "C"
#endif

namespace lslboost {
namespace winapi {
#if defined( BOOST_USE_WINDOWS_H )
typedef ::HLOCAL HLOCAL_;
#endif
using ::LocalAlloc;
using ::LocalReAlloc;
using ::LocalFree;
}
}

#include <boost/winapi/detail/footer.hpp>

#endif // BOOST_WINAPI_PARTITION_APP_SYSTEM
#endif // BOOST_WINAPI_LOCAL_MEMORY_HPP_INCLUDED_
