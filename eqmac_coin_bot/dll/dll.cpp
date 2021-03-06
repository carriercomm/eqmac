#define WINVER 0x0500

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

#include <boost/algorithm/string.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <boost/range/algorithm.hpp>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include <windows.h>
#include <psapi.h>

#include <winbase.h>

#include "memory.hpp"

#include "eqmac.hpp"

#define APPLICATION_NAME "EQMac Coin Bot"

const std::string ini_file = "eqmac_coin_bot.ini";

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_Z 0x5A

#define VK_ALT VK_MENU

memory memory;

bool exit_dll = false;

HMODULE module_global;

std::vector<everquest_spawn_t> everquest_spawns;
std::vector<everquest_spawn_t>::iterator everquest_spawns_it;

bool coin_bot_activated = false;

std::string aggro_npc_name = "A_Castrorum_Seniori01";
float aggro_npc_minimum_distance = 250;

std::string get_coin_npc_name = "Examiner_Malikin00";
float get_coin_npc_y;
float get_coin_npc_x;
float get_coin_npc_z;
float get_coin_npc_heading;
float get_coin_npc_warp_y;
float get_coin_npc_warp_x;
float get_coin_npc_warp_z;
float get_coin_npc_warp_heading;

std::string give_coin_npc_name = "Percontorius_Ontu00";
float give_coin_npc_y;
float give_coin_npc_x;
float give_coin_npc_z;
float give_coin_npc_heading;
float give_coin_npc_warp_y;
float give_coin_npc_warp_x;
float give_coin_npc_warp_z;
float give_coin_npc_warp_heading;
int give_coin_npc_mouse_x;
int give_coin_npc_mouse_y;

int give_button_mouse_x;
int give_button_mouse_y;

int hot_button_mouse_x;
int hot_button_mouse_y;

void load_config()
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(ini_file, pt);

    aggro_npc_name = pt.get<std::string>("AggroNPC.Name");
    aggro_npc_minimum_distance = pt.get<float>("AggroNPC.MinimumDistance");

    get_coin_npc_name         = pt.get<std::string>("GetCoinNPC.Name");
    get_coin_npc_y            = pt.get<float>("GetCoinNPC.Y");
    get_coin_npc_x            = pt.get<float>("GetCoinNPC.X");
    get_coin_npc_z            = pt.get<float>("GetCoinNPC.Z");
    get_coin_npc_heading      = pt.get<float>("GetCoinNPC.Heading");
    get_coin_npc_warp_y       = pt.get<float>("GetCoinNPC.WarpY");
    get_coin_npc_warp_x       = pt.get<float>("GetCoinNPC.WarpX");
    get_coin_npc_warp_z       = pt.get<float>("GetCoinNPC.WarpZ");
    get_coin_npc_warp_heading = pt.get<float>("GetCoinNPC.WarpHeading");
    //get_coin_npc_mouse_x      = pt.get<int>("GetCoinNPC.MouseX");
    //get_coin_npc_mouse_y      = pt.get<int>("GetCoinNPC.MouseY");

    give_coin_npc_name         = pt.get<std::string>("GiveCoinNPC.Name");
    give_coin_npc_y            = pt.get<float>("GiveCoinNPC.Y");
    give_coin_npc_x            = pt.get<float>("GiveCoinNPC.X");
    give_coin_npc_z            = pt.get<float>("GiveCoinNPC.Z");
    give_coin_npc_heading      = pt.get<float>("GiveCoinNPC.Heading");
    give_coin_npc_warp_y       = pt.get<float>("GiveCoinNPC.WarpY");
    give_coin_npc_warp_x       = pt.get<float>("GiveCoinNPC.WarpX");
    give_coin_npc_warp_z       = pt.get<float>("GiveCoinNPC.WarpZ");
    give_coin_npc_warp_heading = pt.get<float>("GiveCoinNPC.WarpHeading");
    give_coin_npc_mouse_x      = pt.get<int>("GiveCoinNPC.MouseX");
    give_coin_npc_mouse_y      = pt.get<int>("GiveCoinNPC.MouseY");

    give_button_mouse_x = pt.get<int>("GiveButton.MouseX");
    give_button_mouse_y = pt.get<int>("GiveButton.MouseY");

    hot_button_mouse_x = pt.get<int>("HotButton.MouseX");
    hot_button_mouse_y = pt.get<int>("HotButton.MouseY");
}

void inject_warp_dll()
{
    HANDLE process_handle = memory.get_process_handle();

    if (process_handle == NULL)
    {
        return;
    }

    char dll_path_name[MAX_PATH] = {0};
    GetFullPathName("eqmac_function_warp.dll", MAX_PATH, dll_path_name, NULL);

    LPVOID remote_memory = VirtualAllocEx(process_handle, NULL, strlen(dll_path_name), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    WriteProcessMemory(process_handle, remote_memory, dll_path_name, strlen(dll_path_name), NULL);

    HANDLE remote_thread = CreateRemoteThread(process_handle, NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA"), remote_memory, 0, NULL);

    WaitForSingleObject(remote_thread, INFINITE);

    VirtualFreeEx(process_handle, remote_memory, strlen(dll_path_name), MEM_RELEASE);

    CloseHandle(remote_thread);
}

void toggle_bool(bool &b)
{
    b = !b;
}

void update_spawns()
{
    if (memory.get_process_id() == 0)
    {
        return;
    }

    everquest_update_spawns(memory, everquest_spawns);
}

std::string get_target_name()
{
    std::string target_name = "null";

    int target_spawn_info = everquest_get_target_spawn_info(memory);

    if (target_spawn_info != EVERQUEST_SPAWN_INFO_NULL)
    {
        target_name = memory.read_string(target_spawn_info + EVERQUEST_OFFSET_SPAWN_INFO_NAME, EVERQUEST_SPAWN_INFO_NAME_SIZE);
    }

    return target_name;
}

void set_target_by_name(std::string target_name)
{
    update_spawns();

    foreach (everquest_spawn_t everquest_spawn, everquest_spawns)
    {
        if (everquest_spawn.name == target_name)
        {
            memory.write_any<DWORD>(EVERQUEST_TARGET_SPAWN_INFO_POINTER, everquest_spawn.address);

            break;
        }
    }
}

float get_target_distance_by_name(std::string target_name)
{
    update_spawns();

    foreach (everquest_spawn_t everquest_spawn, everquest_spawns)
    {
        if (everquest_spawn.name == target_name)
        {
            return everquest_spawn.distance;

            break;
        }
    }
}

float get_target_distance_z_by_name(std::string target_name)
{
    update_spawns();

    foreach (everquest_spawn_t everquest_spawn, everquest_spawns)
    {
        if (everquest_spawn.name == target_name)
        {
            return everquest_spawn.distance_z;

            break;
        }
    }
}

bool check_duck_to_deactivate()
{
    int player_spawn_info = everquest_get_player_spawn_info(memory);

    BYTE player_standing_state = memory.read_any<BYTE>(player_spawn_info + EVERQUEST_OFFSET_SPAWN_INFO_STANDING_STATE);

    if (player_standing_state == EVERQUEST_STANDING_STATE_DUCKING)
    {
        coin_bot_activated = false;

        everquest_function_chat_write_ex(APPLICATION_NAME " deactivated.");

        return true;
    }

    return false;
}

bool check_if_sitting()
{
    int player_spawn_info = everquest_get_player_spawn_info(memory);

    BYTE player_standing_state = memory.read_any<BYTE>(player_spawn_info + EVERQUEST_OFFSET_SPAWN_INFO_STANDING_STATE);

    if (player_standing_state == EVERQUEST_STANDING_STATE_SITTING)
    {
        return true;
    }

    return false;
}

bool is_target_null()
{
    int target_spawn_info = everquest_get_target_spawn_info(memory);

    if (target_spawn_info == EVERQUEST_SPAWN_INFO_NULL)
    {
        return true;
    }

    return false;
}

void clear_target()
{
    memory.write_any<DWORD>(EVERQUEST_TARGET_SPAWN_INFO_POINTER, 0);
}


void move_mouse_to_top_left_of_screen()
{
    memory.write_any<DWORD>(EVERQUEST_MOUSE_X, 0);
    memory.write_any<DWORD>(EVERQUEST_MOUSE_Y, 0);
}

void move_mouse_to_center_of_screen()
{
    memory.write_any<DWORD>(EVERQUEST_MOUSE_X, 640 / 2);
    memory.write_any<DWORD>(EVERQUEST_MOUSE_Y, 480 / 2);
}

void mouse_click(int x, int y)
{
    memory.write_any<DWORD>(EVERQUEST_MOUSE_X, x);
    memory.write_any<DWORD>(EVERQUEST_MOUSE_Y, y);

    Sleep(100);

    memory.write_any<DWORD>(EVERQUEST_MOUSE_CLICK_STATE, EVERQUEST_MOUSE_CLICK_STATE_LEFT);

    Sleep(100);

    move_mouse_to_top_left_of_screen();
}

bool is_mouse_cursor_holding_item()
{
    int mouse_cursor_info = everquest_get_mouse_cursor_info(memory);

    return memory.read_any<BYTE>(mouse_cursor_info + EVERQUEST_OFFSET_MOUSE_CURSOR_INFO_IS_HOLDING_ITEM);
}

bool is_trade_window_open()
{
    int old_ui_info = everquest_get_old_ui_info(memory);

    return memory.read_any<DWORD>(old_ui_info + EVERQUEST_OFFSET_OLD_UI_INFO_IS_TRADE_WINDOW_OPEN);
}

void warp_to_coordinates(float y, float x, float z, float heading)
{
    int player_spawn_info = everquest_get_player_spawn_info(memory);

    memory.write_any<float>(player_spawn_info + EVERQUEST_OFFSET_SPAWN_INFO_HEADING, heading);

    memory.write_any<float>(EVERQUEST_ZONE_INFO_STRUCTURE + EVERQUEST_OFFSET_ZONE_INFO_SAFE_POINT_Y, y);
    memory.write_any<float>(EVERQUEST_ZONE_INFO_STRUCTURE + EVERQUEST_OFFSET_ZONE_INFO_SAFE_POINT_X, x);
    memory.write_any<float>(EVERQUEST_ZONE_INFO_STRUCTURE + EVERQUEST_OFFSET_ZONE_INFO_SAFE_POINT_Z, z);

    Sleep(100);

    everquest_function_warp_to_safe_point(EVERQUEST_FUNCTION_WARP_TO_SAFE_POINT_VALUE);

    Sleep(1000);
}

void set_movement_updates(bool enabled)
{
    if (enabled == true)
    {
        memory.write_any<WORD>(0x0053EAC0, 0x9090);
    }
    else
    {
        memory.write_any<WORD>(0x0053EAC0, 0x2E75);
    }
}

bool is_aggro_npc_within_distance()
{
    bool is_within_distance = false;

    update_spawns();

    foreach (everquest_spawn_t everquest_spawn, everquest_spawns)
    {
        if (everquest_spawn.name == aggro_npc_name)
        {
            float aggro_npc_distance_from_npc = everquest_calculate_distance(get_coin_npc_x, get_coin_npc_y, everquest_spawn.x, everquest_spawn.y);

            if (aggro_npc_distance_from_npc <= aggro_npc_minimum_distance)
            {
                if (everquest_spawn.distance <= aggro_npc_minimum_distance)
                {
                    is_within_distance = true;
                    break;
                }
            }
        }
    }

    return is_within_distance;
}

void warp_to_give_coin_npc()
{
    //return;

    warp_to_coordinates(give_coin_npc_warp_y, give_coin_npc_warp_x, give_coin_npc_warp_z, give_coin_npc_warp_heading);

    while (get_target_distance_by_name(give_coin_npc_name) > 100)
    {
        warp_to_give_coin_npc();
    }

    while (get_target_distance_z_by_name(give_coin_npc_name) > 5)
    {
        warp_to_give_coin_npc();
    }
}

void warp_to_get_coin_npc()
{
    //return;

    if (is_aggro_npc_within_distance() == true)
    {
        warp_to_give_coin_npc();
        return;
    }

    warp_to_coordinates(get_coin_npc_warp_y, get_coin_npc_warp_x, get_coin_npc_warp_z, get_coin_npc_warp_heading);

    while (get_target_distance_by_name(get_coin_npc_name) > 100)
    {
        warp_to_get_coin_npc();
    }

    while (get_target_distance_z_by_name(get_coin_npc_name) > 5)
    {
        warp_to_get_coin_npc();
    }
}

void thread_load(HMODULE module)
{
    memory.enable_debug_privileges();

    memory.set_process_by_id(GetCurrentProcessId());

    load_config();

    everquest_function_chat_write_ex(APPLICATION_NAME " loaded.");

    return;
}

void thread_keys(HMODULE module)
{
    while (1)
    {

        if (exit_dll == true)
        {
            break;
        }

        if (memory.get_process_id() == 0)
        {
            continue;
        }

        if (memory.is_foreground_window_current_process_id() == false)
        {
            continue;
        }

        if
        (
            (GetAsyncKeyState(VK_CONTROL)) &&
            (GetAsyncKeyState(VK_ALT)) &&
            (GetAsyncKeyState(VK_BACK))
        )
        {
            if (coin_bot_activated == false)
            {
                exit_dll = true;
                break;
            }
        }

        if
        (
            (GetAsyncKeyState(VK_CONTROL)) &&
            (GetAsyncKeyState(VK_ALT)) &&
            (GetAsyncKeyState(VK_Z))
        )
        {
            toggle_bool(coin_bot_activated);

            //if (is_aggro_npc_within_distance() == true)
            //{
                //coin_bot_activated = false;

                //everquest_function_chat_write_ex(APPLICATION_NAME " aggro NPC is within distance!");
            //}

            if (coin_bot_activated == true)
            {
                everquest_function_chat_write_ex(APPLICATION_NAME " activated.");
            }
            else
            {
                everquest_function_chat_write_ex(APPLICATION_NAME " deactivated.");
            }

            Sleep(1000);
        }

        Sleep(1);
    }

    if (exit_dll == true)
    {
        everquest_function_chat_write_ex(APPLICATION_NAME " unloaded.");

        Sleep(1000);

        FreeLibraryAndExitThread(module, 0);
        return;
    }
}

void thread_coin_bot(HMODULE module)
{
    while (1)
    {
        if (exit_dll == true)
        {
            return;
        }

        if (memory.get_process_id() == 0)
        {
            continue;
        }

        if (coin_bot_activated == false)
        {
            continue;
        }

        if (check_if_sitting() == true)
        {
            continue;
        }

        if (check_duck_to_deactivate() == true)
        {
            continue;
        }

        std::string zone_short_name = everquest_get_zone_short_name(memory);

        boost::algorithm::to_lower(zone_short_name);

        if (zone_short_name != "sseru")
        {
            continue;
        }

        clear_target();

        move_mouse_to_top_left_of_screen();

        if (is_aggro_npc_within_distance() == true)
        {
            warp_to_give_coin_npc();
            continue;
        }

        if (is_target_null() == true)
        {
            if (is_mouse_cursor_holding_item() == true)
            {
                set_target_by_name(give_coin_npc_name);
                warp_to_give_coin_npc();
            }
            else
            {
                set_target_by_name(get_coin_npc_name);
                warp_to_get_coin_npc();
            }
        }

        if (get_target_name() == give_coin_npc_name)
        {
            if (is_mouse_cursor_holding_item() == false)
            {
                if (is_trade_window_open() == false)
                {
                    set_target_by_name(get_coin_npc_name);
                    warp_to_get_coin_npc();
                }
            }
        }

        if (get_target_name() == get_coin_npc_name)
        {
            while (is_mouse_cursor_holding_item() == false)
            {
                if (is_aggro_npc_within_distance() == true)
                {
                    warp_to_give_coin_npc();
                    break;
                }

                if (check_duck_to_deactivate() == true)
                {
                    break;
                }

                if (get_target_name() == give_coin_npc_name)
                {
                    if (is_mouse_cursor_holding_item() == false)
                    {
                        if (is_trade_window_open() == false)
                        {
                            set_target_by_name(get_coin_npc_name);
                            warp_to_get_coin_npc();
                            break;
                        }
                    }
                }

                mouse_click(hot_button_mouse_x, hot_button_mouse_y);
                Sleep(100);
            }

            if (is_mouse_cursor_holding_item() == true)
            {
                set_target_by_name(give_coin_npc_name);
                warp_to_give_coin_npc();
            }
        }

        if (get_target_name() == give_coin_npc_name)
        {
            while (is_mouse_cursor_holding_item() == true)
            {
                if (check_duck_to_deactivate() == true)
                {
                    break;
                }

                if (is_trade_window_open() == false)
                {
                    mouse_click(give_coin_npc_mouse_x, give_coin_npc_mouse_y);
                    Sleep(100);
                }
            }

            if (is_mouse_cursor_holding_item() == false)
            {
                while (is_trade_window_open() == true)
                {
                    if (check_duck_to_deactivate() == true)
                    {
                        break;
                    }

                    mouse_click(give_button_mouse_x, give_button_mouse_y);
                    Sleep(100);
                }

                if (is_trade_window_open() == false)
                {
                    clear_target();
                }
            }
        }

        Sleep(1);
    }
}

extern "C" BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    module_global = module;

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_load,     module, 0, NULL);
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_keys,     module, 0, NULL);
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_coin_bot, module, 0, NULL);
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}
