/*!*******************************************************************
\file		  ImGuiClient.cpp
\author       Kim Hyungseob
\par          email: hn02415 \@ gmail.com
\date         2020/01/04
\brief
			  Header file for abstracted ImGuiClient class which
			  manages ImGui.
********************************************************************/
#include "ImGuiClient.h"

#include "ImPlot/implot.h"

ImGuiClient::ImGuiClient()
{
	// ImGUi: setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
	ImGui::StyleColorsDark();
}

void ImGuiClient::Init(SDL_Window* window, SDL_GLContext& context, const char* glsl_version)
{
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImGuiClient::ProcessEvent(SDL_Event* event)
{
	ImGui_ImplSDL2_ProcessEvent(event);
}

bool ImGuiClient::Draw(SDL_Window* window, bool& start, double* x_data, double* y_data, double* output, int dataSize, int iteration)
{
	// Start ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
	ImGui::NewFrame();

	bool compute = false;

	// Show default winodw
	ImGui::Begin("Control Panel");
	
	ImGui::Text("Click start to compute.");
	
	if (ImGui::Checkbox("start", &start))
		compute = true;

	ImGui::Text("You can restart by click again.");

	ImGui::End();

	// Show Output
	if (start)
	{
		ImGui::Begin("Output");

		ImGui::Text("Iteration: %i", iteration);
		
		if (ImPlot::BeginPlot("Graph"))
		{
			ImPlot::PlotLine("y = x^2", x_data, y_data, dataSize);
			ImPlot::PlotLine("Appoximation", x_data, output, dataSize);
			ImPlot::EndPlot();
		}

		ImGui::Text("You can zoom in/out with middle mouse button.");
		ImGui::Text("Drag with mouse to move graph.");

		ImGui::End();
	}

	// Draw ImGui
	ImGui::Render();

	return compute;
}

void ImGuiClient::RenderDrawData()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ImGuiClient::DidConsumeInput()
{
	return ImGui::GetIO().WantCaptureMouse;
}

ImGuiClient::~ImGuiClient()
{
	ImPlot::DestroyContext();
	// ImGui: Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}