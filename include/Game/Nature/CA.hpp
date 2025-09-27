#pragma once

#include "Tools/Color.hpp"
#include "base/Canvas.hpp"
#include "base/Painter.hpp"
#include "imgui.h"
#include <algorithm>
#include <cassert>
#include <span>
#include <string>
#include <vector>

class CA {
public:
	std::vector<std::vector<int>> generations;
	static std::vector<int> ruleset;
	int w = 10;
	int currentGeneration = 0;
	bool finished = false;

	void Clear(){
		generations.clear();
	}

	CA() {
		auto& canvas = Canvas::getInstance();
		std::vector<int> firstGen(canvas.GetWindowW() / w, 0);
		firstGen[firstGen.size() / 2] = 1;
		generations.push_back(firstGen);
	}

	void generate() {
		if (finished) {
			return;
		}

		auto& currentGen = generations.back();
		std::vector<int> nextGen(currentGen.size(), 0);

		for (int i = 1; i < currentGen.size() - 1; ++i) {
			int left = currentGen[i - 1];
			int me = currentGen[i];
			int right = currentGen[i + 1];
			nextGen[i] = rules(left, me, right);
		}

		generations.push_back(nextGen);
		currentGeneration++;

		// 检查是否到达屏幕底部
		auto& canvas = Canvas::getInstance();
		if (currentGeneration * w >= canvas.GetWindowH()) {
			finished = true;
		}
	}

	void display() {
		auto& painter = Painter::getInstance();

		for (int gen = 0; gen < generations.size(); ++gen) {
			for (int i = 0; i < generations[gen].size(); ++i) {
				if (generations[gen][i] == 1) {
					painter.DrawRect(i * w, gen * w, w, w, Black);
				} else {
					painter.DrawRect(i * w, gen * w, w, w, White);
				}
			}
		}
	}

	int rules(int a, int b, int c) {
		int index = (a << 2) | (b << 1) | c;
		return ruleset[index];
	}

	static void drawRulesetControls() {
		ImGui::Begin("Wolfram CA Ruleset");

		// 直接输入规则数字
		static int ruleNumber = 90; // 默认规则90
		if (ImGui::InputInt("Rule Number (0-255)", &ruleNumber, 1, 10)) {
			ruleNumber = std::clamp(ruleNumber, 0, 255);
			rulesetFromNumber(ruleNumber);
		}

		// 拖动条版本
		ImGui::SliderInt("Rule", &ruleNumber, 0, 255);
		if (ImGui::IsItemDeactivatedAfterEdit()) {
			rulesetFromNumber(ruleNumber);
		}

		// 显示二进制表示
		ImGui::Text("Binary: ");
		ImGui::SameLine();
		for (int i = 7; i >= 0; i--) {
			ImGui::Text("%d", ruleset[i]);
			if (i > 0) {
				ImGui::SameLine();
			}
		}

		ImGui::Text("Pattern: 111 110 101 100 011 010 001 000");
		ImGui::Text("Value:   %d   %d   %d   %d   %d   %d   %d   %d",
				ruleset[7], ruleset[6], ruleset[5], ruleset[4],
				ruleset[3], ruleset[2], ruleset[1], ruleset[0]);

		// 常用规则按钮
		ImGui::Separator();
		ImGui::Text("Common Rules:");

		struct RulePreset {
			int number;
			const char* name;
			const char* description;
		};

		RulePreset presets[] = {
			{ 30, "Rule 30", "Chaotic, random" },
			{ 90, "Rule 90", "Sierpinski triangle" },
			{ 110, "Rule 110", "Turing complete" },
			{ 184, "Rule 184", "Traffic model" },
			{ 54, "Rule 54", "Complex patterns" },
			{ 60, "Rule 60", "Self-similar" },
			{ 73, "Rule 73", "Nested patterns" },
			{ 150, "Rule 150", "Additive rule" }
		};

		for (int i = 0; i < 8; i++) {
			if (ImGui::Button(presets[i].name)) {
				ruleNumber = presets[i].number;
				rulesetFromNumber(ruleNumber);
			}
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("%s: %s", presets[i].name, presets[i].description);
			}
			if (i % 4 != 3) {
				ImGui::SameLine();
			}
		}

		ImGui::End();
	}

	static void setRuleset(const std::vector<int>& newRuleset) {
		if (newRuleset.size() == 8) {
			ruleset = newRuleset;
		}
	}

	// 在CA类中添加
	static int calculateRuleNumber() {
		int number = 0;
		for (int i = 0; i < 8; i++) {
			number |= (ruleset[i] << i);
		}
		return number;
	}

	static void rulesetFromNumber(int number) {
		number = std::clamp(number, 0, 255);
		for (int i = 0; i < 8; i++) {
			ruleset[i] = (number >> i) & 1;
		}
	}
};