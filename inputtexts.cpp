#include "inputtexts.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

InputTexts::InputTexts(){}
InputTexts::InputTexts(char* _str_id, ImVec2 _pos, ImVec2 _size, ImU32 _color_dark, ImU32 _color_light, ImU32 _color_edge, int _type, GLuint _img_email, GLuint _img_pass, GLuint _img_eye_on, GLuint _img_eye_off) : pos(_pos), size(_size), color_dark(_color_dark), color_light(_color_light), color_edge(_color_edge), type(_type), img_email(_img_email), img_pass(_img_pass), img_eye_on(_img_eye_on), img_eye_off(_img_eye_off)
{
    str_id = new char[strlen(_str_id)];
    strcpy(str_id, _str_id);
    text = new char[30];
    strcpy(text, "");
    status = false;
}

InputTexts::~InputTexts() {
}
int curpos = 0;

int my_callback(ImGuiInputTextCallbackData* data)
{
    curpos = data->CursorPos;
    return 0;
}
void InputTexts::render(ImVec2 _pos, ImVec2 _size) {
    pos = _pos;
    size = _size;
    float padding_x = 20;
    float padding_y = (ImGui::GetFontSize() - ImGui::GetStyle().FramePadding.y) * 2;
    float width = (size.x - padding_x * 2);
    float thick = 2.0f;
    ImVec2 start_pos = { pos.x + padding_x, pos.y + (size.y - padding_y) / 2 };
    char placeholder[30];
    char temptext[30];

    ImGui::SetCursorPos({ start_pos.x + padding_y, start_pos.y });
    ImGui::SetNextItemWidth(width - padding_y);
    if (type == 0) { strcpy(placeholder, "Email"); }
    else { strcpy(placeholder, "********"); }
    strcpy(temptext, text);
    if (type == 1 && status == false) {
        for (int i = 0; i < strlen(text); ++i) { temptext[i] = '*'; }
    }
    ImGui::InputTextWithHint(str_id, placeholder, text, 30, ImGuiInputTextFlags_CallbackEdit, my_callback);
    ImGui::GetWindowDrawList()->AddRectFilledMultiColor(start_pos, { start_pos.x + width, start_pos.y + padding_y }, color_dark, color_light, color_light, color_dark);
    ImGui::GetWindowDrawList()->AddRect({ start_pos.x - thick, start_pos.y - thick }, { start_pos.x + width + thick, start_pos.y + padding_y + thick }, color_edge, 2.0f, 0, thick);
    ImGui::SetCursorPos({start_pos.x + padding_y + 8, start_pos.y + 8 });
    if (text[0] == NULL) { ImGui::Text(placeholder); }
    else { ImGui::Text(temptext); }
    if (type == 0)
        ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)img_email, start_pos, start_pos + ImVec2(padding_y, padding_y));
    else {
        ImGui::GetWindowDrawList()->AddImage((void*)(intptr_t)img_pass, start_pos, start_pos + ImVec2(padding_y, padding_y));
        ImGui::SetCursorScreenPos({ start_pos.x + width - padding_y, start_pos.y });
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0x00, 0x00, 0x00, 0x00));
        if (status == true) {
            if (ImGui::ImageButton("##eye_on", (void*)(intptr_t)img_eye_on, { padding_y - 3, padding_y - 3 })) { status = false; }
        }
        else {
            if (ImGui::ImageButton("##eye_off", (void*)(intptr_t)img_eye_off, { padding_y - 3, padding_y - 3})) { status = true; }
        }
        ImGui::PopStyleColor();
    }
}