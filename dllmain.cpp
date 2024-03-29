// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "SDK/SDK.hpp"

#define HWND_WINDOW_NAME "Tribes Vengeance"
static WNDPROC original_windowproc_callback = NULL;
static HWND game_hwnd = NULL;

LRESULT WINAPI CustomWindowProcCallback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_KEYDOWN) {
        if (wParam == VK_INSERT) {
            auto terrain_list = SDK::UClass_Object::FindObjectsByType<SDK::AClass_Object_Actor_Info_TerrainInfo>();
            if (terrain_list.size())
            {
                int terrain_count = 0;
                for (auto& terrain : terrain_list)
                {
                    auto terrain_file_name = std::string("heightmap_").append(std::to_string(terrain_count)).append(".bin");
                    auto f = fopen(terrain_file_name.c_str(), "wb");

                    unsigned int s;
                    s = terrain->HeightmapX;
                    fwrite(&s, sizeof(unsigned int), 1, f);
                    s = terrain->HeightmapY;
                    fwrite(&s, sizeof(unsigned int), 1, f);

                    for (int i = 0; i < terrain->Vertices.Num(); i++)
                    {
                        fwrite(&terrain->Vertices[i], sizeof(SDK::FStruct_Vector), 1, f);
                    }

                    fclose(f);
                    terrain_count++;
                }
            }
        }
    }
    return CallWindowProc(original_windowproc_callback, hWnd, msg, wParam, lParam);
}

void OnDLLProcessAttach(void)
{
    game_hwnd = FindWindowA(NULL, HWND_WINDOW_NAME);
    original_windowproc_callback = (WNDPROC)SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, (LONG_PTR)CustomWindowProcCallback);
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OnDLLProcessAttach, NULL, NULL, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

