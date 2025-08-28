#include "Game/editor/editor.hpp"

#include "base/Canvas.hpp"
#include "base/Painter.hpp"

#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "imgui.h"


Editor::Editor() {
	init();
}

void Editor::init() {
	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

	auto& canvas = Canvas::getInstance();
	auto& painter = Painter::getInstance();
    window_ = canvas.GetWindow();
    renderer_ = painter.GetRenderer();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
	style.FontScaleDpi = main_scale; // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForSDLRenderer(canvas.GetWindow(), painter.GetRenderer());
	ImGui_ImplSDLRenderer3_Init(painter.GetRenderer());
}

void Editor::pollevent(SDL_Event& event) {
	ImGui_ImplSDL3_ProcessEvent(&event);
}

bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


void Editor::draw() {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button")) { // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		}
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}

	ImGui::Render();
	//SDL_SetRenderScale(renderer_, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	SDL_SetRenderDrawColorFloat(renderer_, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//SDL_RenderClear(renderer_);
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer_);
	SDL_RenderPresent(renderer_);
}
