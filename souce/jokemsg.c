//
//custome meterpreter extensions 
//
#define _CRT_SECURE_NO_DEPRECATE 1

#include "jokemsg.h"
#include "../../common/common.h"
#include "../../DelayLoadMetSrv/DelayLoadMetSrv.h"

#pragma comment(lib, "Ws2_32.lib")

// include the Reflectiveloader() function, we end up linking back to the metsrv.dll's Init function
// but this doesnt matter as we wont ever call DLL_METASPLOIT_ATTACH as that is only used by the
// second stage reflective dll inject payload and not the metsrv itself when it loads extensions.
#include "../../ReflectiveDLLInjection/dll/src/ReflectiveLoader.c"
// NOTE: _CRT_SECURE_NO_WARNINGS has been added to Configuration->C/C++->Preprocessor->Preprocessor

// this sets the delay load hook function, see DelayLoadMetSrv.h
EnableDelayLoadMetSrv();

DWORD request_jokemsg_doingjoke(Remote* remote, Packet* packet);

Command customCommands[] =
{
	COMMAND_REQ("jokemsg_doingjoke", request_jokemsg_doingjoke),
	COMMAND_TERMINATOR
};



typedef int(*MessageBoxPtr)(HWND, LPCSTR, LPCSTR, UINT);

DWORD request_jokemsg_doingjoke(Remote* remote, Packet* packet){
	DWORD result = ERROR_SUCCESS;
	BOOL jokemsg_result = TRUE;
	HMODULE user32dll = NULL;
	MessageBoxPtr jokeMessageBox = NULL;

	Packet* response = packet_create_response(packet);

	do{

		if (!response){
			result = ERROR_NOT_ENOUGH_MEMORY;
			break;
		}

		user32dll = LoadLibraryA("user32.dll");
		if (!user32dll){
			result = GetLastError();
			break;
		}

		jokeMessageBox = (MessageBoxPtr)GetProcAddress(user32dll, "MessageBoxA");
		if (!jokeMessageBox){
			result = GetLastError();
			break;
		}

		char* message = NULL;
		message = packet_get_tlv_value_string(packet, TLV_TYPE_JOKEMSG_MESSAGE);
		if (!message){
			result = ERROR_NOT_ENOUGH_MEMORY;
			break;
		}

		//this need to be done by an another thread
		jokemsg_result = jokeMessageBox(NULL, message, "Hello I'm a Joker", MB_OK);
		
		packet_add_tlv_bool(response, TLV_TYPE_JOKEMSG_RESULT, jokemsg_result);

		packet_transmit_response(result, remote, response);

	} while (0);
	

	return result;
}


/*
* @brief Initialize the server extension.
* @param remote Pointer to the remote instance.
* @return Indication of success or failure.
*/
#ifdef _WIN32
DWORD __declspec(dllexport) InitServerExtension(Remote *remote)
#else
DWORD InitServerExtension(Remote *remote)
#endif
{
#ifdef _WIN32
	hMetSrv = remote->met_srv;
#endif
	command_register_all(customCommands);

	return ERROR_SUCCESS;
}

/*!
* @brief Deinitialize the server extension.
* @param remote Pointer to the remote instance.
* @return Indication of success or failure.
*/
#ifdef _WIN32
DWORD __declspec(dllexport) DeinitServerExtension(Remote *remote)
#else
DWORD DeinitServerExtension(Remote *remote)
#endif
{
	command_deregister_all(customCommands);

	return ERROR_SUCCESS;
}

/*
* @brief Get the name of the extension.
* @param buffer Pointer to the buffer to write the name to.
* @param bufferSize Size of the \c buffer parameter.
* @return Indication of success or failure.
*/
#ifdef _WIN32
DWORD __declspec(dllexport) GetExtensionName(char* buffer, int bufferSize)
#else
DWORD GetExtensionName(char* buffer, int bufferSize)
#endif
{
#ifdef _WIN32
	strncpy_s(buffer, bufferSize, "jokemsg", bufferSize - 1);
#else
	strncpy(buffer, "jokemsg", bufferSize - 1);
#endif
	return ERROR_SUCCESS;
}
