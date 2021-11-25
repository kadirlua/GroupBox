#ifndef _IR_LUA_FUNCTIONS_GROUPBOX_PLUGIN_H_
#define _IR_LUA_FUNCTIONS_GROUPBOX_PLUGIN_H_

void GroupBox_RegisterLuaFunctions(lua_State* luaState);
static int GroupBox_SetBorderColor(lua_State* luaState);
static int GroupBox_SetLabelText(lua_State* luaState);
static int GroupBox_SetCaptionTextColor(lua_State* luaState);
static int GroupBox_SetBackGroundColor(lua_State* luaState);
#endif