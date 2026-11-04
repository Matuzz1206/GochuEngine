#include "Precompiled.h"
#include "GochuEngine.h"


GochuEngine::App& GochuEngine::MainApp()
{
    static App sApp;
    return sApp;
}
