#pragma once

#if defined(ON_RUNTIME_WIN) && defined(_MFC_VER)
#include "rhinoSdkTMfcPages.h"
#endif

#if defined(ON_RUNTIME_APPLE)
#include "rhinoSdkTMacPages.h"
#endif
