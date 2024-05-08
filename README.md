# LuaDAP for X-Plane
A plugin that provides Debug Apater Protocol capabilities to X-Plane Lua plugins.

All heavy lifting is done by the [LRDP project](https://github.com/satoren/LRDB/).

## Integration with your plugin:
LuaDAP accepts `XPLMSendMessage(..)` commands to attach and detach from your plugins lua_State pointer.

LuaDAP is compiled with the Lua version string in its plugin signature to avoid incompatibilities.

### Finding LuaDAP:
`XPLMPluginID to = XPLMFindPluginBySignature("LuaJIT-2.1.0-b3.LuaDAP.x-plugins.com");`

### Requesting debug attach:
`XPLMSendMessageToPlugin( to, 0x1, L );`

### Requesting debug detach:
`XPLMSendMessageToPlugin( to, 0x2, nullptr );`


## Using LuaDAP with VSCode:

LuaDAP has only been tested with Gizmo-Avionics.plugin

1. Install the LDRB extension for VSCode.
2. Open your scripting project with VSCode.
3. Create a `.vscode` folder in the root of your project tree.
4. Copy the `usage/launch.json` file from this repository into the new `.vscode` folder.
5. Edit `launch.json` and set the `sourceRoot` value to match the full path to your project scripts folder.
6. Configure your project so it asks the Lua host plugin to attach to LuaDAP.xpl, for Gizmo-Avionics.plugin this is `gizmo.attachDAP()`
7. Start X-Plane with the LuaDAP plugin installed.
8. From the VSCode menu select `Run / Start Debugging`

