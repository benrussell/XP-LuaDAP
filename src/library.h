#ifndef LUADAP_LIBRARY_H
#define LUADAP_LIBRARY_H


#include <XPLMDefs.h>


#include <lrdb/server.hpp>

struct LuaDAPGlobals{
	lrdb::server* debug_server = nullptr;
	bool client_attached = false;
	std::string client_plugin_sig{};
};

LuaDAPGlobals globals;


//Standard X-Plane plugin function hooks.
PLUGIN_API int XPluginStart(
		char *		outName,
		char *		outSig,
		char *		outDesc);

PLUGIN_API void XPluginStop(void);

PLUGIN_API int XPluginEnable(void);

PLUGIN_API void XPluginDisable(void);

PLUGIN_API void XPluginReceiveMessage(
		XPLMPluginID   inFromWho,
		intptr_t        inMessage,
		void *      inParam);



#endif //LUADAP_LIBRARY_H
