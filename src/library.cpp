#include "library.h"

#include <iostream>

#include <XPLMPlugin.h>
#include <XPLMUtilities.h>




PLUGIN_API int XPluginStart(
		char *		outName,
		char *		outSig,
		char *		outDesc){


	const char lua_version[] = "LuaJIT-2.1.0-beta3"; // ---------------- Change this if you build against a different Lua version.
	const int listen_port = 21110; // LRDP listens on this TCP port.


	sprintf(outName, "XP-LuaDAP v24.05.08.2308");
	sprintf( outSig, "XP-LuaDAP.x-plugins.com/%s", lua_version );
	strcpy(outDesc, "Lua Debug Adapter for VSCode + LRDP");

	char caMsg[1024];
	snprintf( caMsg, 1024, "%s\n%s\n", outName, outDesc );
	XPLMDebugString( caMsg );

	XPLMEnableFeature( "XPLM_USE_NATIVE_PATHS", 1 );

	globals.debug_server = new lrdb::server(listen_port);

	return 1;
}




PLUGIN_API void XPluginStop(void){
	delete( globals.debug_server );
}




PLUGIN_API int XPluginEnable(void) {
	return 1;
}




PLUGIN_API void XPluginDisable(void){

}




PLUGIN_API void XPluginReceiveMessage(
		XPLMPluginID   inFromWho,
		intptr_t        inMessage,
		void *      inParam){

	if( inFromWho != XPLM_PLUGIN_XPLANE ){

//		char outName[256];
//		char outFilePath[256];
		char outSignature[256];
//		char outDescription[256];

		XPLMGetPluginInfo(
				inFromWho,
				nullptr, //outName,
				nullptr, //outFilePath,
				outSignature,
				nullptr //outDescription
				);


		// we need detach from multiple places.
		auto lam_detach_client = [](){
			char caMsg[1024];
			snprintf( caMsg, 1024, "XP-LuaDAP: Detach: xpl:[%s]\n", globals.client_plugin_sig.c_str() );
			XPLMDebugString( caMsg );

			globals.client_attached = false;
			globals.client_plugin_sig = {};
			globals.debug_server->reset();
		};


		switch( inMessage ){
			case 0x1: // Client is requesting debug attach.
				{
					if( globals.client_attached ){
						lam_detach_client();
					}

					char caMsg[1024];
					snprintf( caMsg, 1024, "XP-LuaDAP: Attach: xpl:[%s] lua_State*: %p\n", outSignature, inParam );
					XPLMDebugString( caMsg );

					globals.client_attached = true;
					globals.client_plugin_sig = std::string( outSignature );
					globals.debug_server->reset( (lua_State*)inParam );
				}
				break;

			case 0x0: // Client is requesting detach.
				{
					lam_detach_client();
				}
				break;

			default:
				XPLMDebugString("XP-LuaDAP: Unknown message.\n");
				break;
		} //switch msg

	} //msg not from xplane

} //XPluginReceiveMessage(..)

