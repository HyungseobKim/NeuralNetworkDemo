/*!*******************************************************************
\headerfile   ImGuiClient.h
\author       Kim Hyungseob
\par          email: hn02415 \@ gmail.com
\date         2021/04/13
\brief
			  Header file for abstracted ImGuiClient class which
			  manages ImGui.
********************************************************************/
#ifndef IMGUICLIENT_H
#define IMGUICLIENT_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

/*!*******************************************************************
\class ImGuiClient
\brief
	   Having methods to handle input and draw.
********************************************************************/
class ImGuiClient
{
public:
	/*!*******************************************************************
	\brief
		   Constructor that create ImGui context and set basic options.
	********************************************************************/
	ImGuiClient();
	/*!*******************************************************************
	\brief
		   Destructor that calls ImGui shutdown functions.
	********************************************************************/
	~ImGuiClient();

	/*!*******************************************************************
	\brief
		   Init ImGui for framework specific.

	\param window
		   SDL_Window of this demo.

	\param context
		   SDL and OpenGL context for this demo.

	\param glsl_version
		   Version of glsl.
	********************************************************************/
	void Init(SDL_Window* window, SDL_GLContext& context, const char* glsl_version);
	/*!*******************************************************************
	\brief
		   Abstracted method to call ImGui handling event function.

	\param event
		   SDL_Event used in this demo.
	********************************************************************/
	void ProcessEvent(SDL_Event* event);
	/*!*******************************************************************
	\brief
		   Determine which items to show in ImGui.

	\param window
		   SDL_Window of this demo.

	\param editMode
		   Where value of related ImGui checkbox will be stored.

	\param showAllNodes
		   Where value of related ImGui checkbox will be stored.

	\param weight
		   Where value of related ImGui float slider will be stored.

	\param color
		   Where value of related ImGui color editor will be stored.

	\param smoothPath
		   Where value of related ImGui checkbox will be stored.

	\return Point
			Mouse position in viewport space.
	********************************************************************/
	bool Draw(SDL_Window* window, bool& start, double* x_data, double* y_data, double* output, int dataSize, int iteration);
	/*!*******************************************************************
	\brief
		   Abstracted method to call ImGui RenderDrawData function.
	********************************************************************/
	void RenderDrawData();

	/*!*******************************************************************
	\brief
		   Check ImGui whether took input this time. If it did, client
		   will ignore this input, so it can be used only for ImGui.

	\return bool
			Returns true, if it took input.
			Return false otherwise.
	********************************************************************/
	bool DidConsumeInput();
};

#endif // !IMGUI_H
