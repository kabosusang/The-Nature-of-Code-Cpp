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



void SetupDarkTheme() {
	auto& style = ImGui::GetStyle();
	ImVec4* colors = ImGui::GetStyle().Colors;
	style.Alpha = 1.0f;
	style.FrameRounding = 3.0f;
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
	//style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	//style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	//style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	//style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	//style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
	//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	//style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	//style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
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
	io.Fonts->AddFontDefault();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
	SetupDarkTheme();
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
static short vectorNum() {
    return Draw::nodes_vector.size();
}

static short forceNum() {
    return Draw::nodes_force.size();
}

static short angleNum() {
    return Draw::nodes_angle.size();
}


void Editor::DemoWindowWidgetsListBoxes() {
	static bool showWindow = true;
	static int vector_selected_idx = 0;
	static int force_selected_idx = 0;
	static int angle_selected_idx = 0;
	static int particle_selected_idx = 0;


	if (showWindow) {
		if (ImGui::Begin("Select Demo", &showWindow)) {
			if (ImGui::TreeNode("Vector")) {
				//static int item_selected_idx = 0; // Here we store our selected data as an index.
				// Custom size: use all width, 5 items tall
				ImGui::Text("Select:");
				if (ImGui::BeginListBox("Vector", ImVec2(FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
					for (int n = 0; n < Draw::nodes_vector.size(); n++) {
						bool is_selected = (vector_selected_idx == n);
						ImGuiSelectableFlags flags = 0;
						if (ImGui::Selectable(Draw::nodes_vector[n].data(), is_selected, flags)) {
							vector_selected_idx = n;
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
				ImGui::Text("Select:");
				if (ImGui::BeginListBox("Force", ImVec2(FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
					for (int n = 0; n < Draw::nodes_force.size(); n++) {
						bool is_selected = (force_selected_idx == n);
						ImGuiSelectableFlags flags = 0;
						if (ImGui::Selectable(Draw::nodes_force[n].data(), is_selected, flags)) {
							force_selected_idx = n;
							Draw::index_ = n + vectorNum();
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

			if (ImGui::TreeNode("Angle")) {
				//static int item_selected_idx = 0; // Here we store our selected data as an index.
				// Custom size: use all width, 5 items tall
				ImGui::Text("Select:");
				if (ImGui::BeginListBox("Angle", ImVec2(FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
					for (int n = 0; n < Draw::nodes_angle.size(); n++) {
						bool is_selected = (angle_selected_idx == n);
						ImGuiSelectableFlags flags = 0;
						if (ImGui::Selectable(Draw::nodes_angle[n].data(), is_selected, flags)) {
							angle_selected_idx = n;
							Draw::index_ = n + vectorNum() + forceNum();
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

			if (ImGui::TreeNode("Particle")) {
				//static int item_selected_idx = 0; // Here we store our selected data as an index.
				// Custom size: use all width, 5 items tall
				ImGui::Text("Select:");
				if (ImGui::BeginListBox("Particle", ImVec2(FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing()))) {
					for (int n = 0; n < Draw::nodes_partivle.size(); n++) {
						bool is_selected = (particle_selected_idx == n);
						ImGuiSelectableFlags flags = 0;
						if (ImGui::Selectable(Draw::nodes_partivle[n].data(), is_selected, flags)) {
							particle_selected_idx = n;
							Draw::index_ = n + vectorNum() + forceNum() + angleNum();
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
		}
		ImGui::End();
	}
}
