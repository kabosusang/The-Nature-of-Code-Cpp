#include "Game/editor/editor.hpp"

#include "Game/Draw.hpp"
#include "base/Canvas.hpp"
#include "base/Painter.hpp"

#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "imgui.h"
#include <iostream>

static void HelpMarker(const char* desc) {
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip()) {
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

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

void Editor::draw() {
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	{
		DemoWindowWidgetsListBoxes();
	}

	ImGui::Render();
	//SDL_SetRenderScale(renderer_, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	//SDL_SetRenderDrawColorFloat(renderer_, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//SDL_RenderClear(renderer_);
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer_);
	//SDL_RenderPresent(renderer_);
}
const static short vectorNum = Draw::nodes_vector.size();
const static short forceNum = Draw::nodes_force.size();




void Editor::DemoWindowWidgetsListBoxes() {
	static bool showWindow = true; // 控制窗口显示
	if (showWindow && ImGui::Begin("Select Demo", &showWindow)) {
		if (ImGui::TreeNode("Vector")) {
			//static int item_selected_idx = 0; // Here we store our selected data as an index.
			// Custom size: use all width, 5 items tall
			auto item_selected_idx = Draw::index_;
			ImGui::Text("Select:");
			if (ImGui::BeginListBox("Vector", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
				for (int n = 0; n < Draw::nodes_vector.size(); n++) {
					bool is_selected = (item_selected_idx == n);
					ImGuiSelectableFlags flags = 0;
					if (ImGui::Selectable(Draw::nodes_vector[n].data(), is_selected, flags)) {
						Draw::index_ = n;
					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndListBox();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Force")) {
			//static int item_selected_idx = 0; // Here we store our selected data as an index.
			// Custom size: use all width, 5 items tall
			auto item_selected_idx = Draw::index_;
			ImGui::Text("Select:");
			if (ImGui::BeginListBox("Force", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
				for (int n = 0; n < Draw::nodes_force.size(); n++) {
					bool is_selected = (item_selected_idx == n);
					ImGuiSelectableFlags flags = 0;
					if (ImGui::Selectable(Draw::nodes_force[n].data(), is_selected, flags)) {
						Draw::index_ = n + vectorNum;
					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndListBox();
			}

			ImGui::TreePop();
		}




		ImGui::End();
	}
}
