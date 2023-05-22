// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.4
// Project name: SquareLine_Project

#include "../ui.h"

void ui_SerialSendBtn_screen_init(void)
{
    ui_SerialSendBtn = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SerialSendBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SerialSendTextArea = lv_textarea_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialSendTextArea, 226);
    lv_obj_set_height(ui_SerialSendTextArea, 151);
    lv_obj_set_x(ui_SerialSendTextArea, -243);
    lv_obj_set_y(ui_SerialSendTextArea, -93);
    lv_obj_set_align(ui_SerialSendTextArea, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_SerialSendTextArea, "Placeholder...");

    ui_PortLabel = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_PortLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_PortLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_PortLabel, -591);
    lv_obj_set_y(ui_PortLabel, -210);
    lv_obj_set_align(ui_PortLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PortLabel, "Port");

    ui_SerialPortSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialPortSelect, 150);
    lv_obj_set_height(ui_SerialPortSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SerialPortSelect, -450);
    lv_obj_set_y(ui_SerialPortSelect, -210);
    lv_obj_set_align(ui_SerialPortSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SerialPortSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_Label2 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, -591);
    lv_obj_set_y(ui_Label2, -90);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "DataBits");

    ui_SerialBaudrateSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialBaudrateSelect, 150);
    lv_obj_set_height(ui_SerialBaudrateSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SerialBaudrateSelect, -450);
    lv_obj_set_y(ui_SerialBaudrateSelect, -150);
    lv_obj_set_align(ui_SerialBaudrateSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SerialBaudrateSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_SerialDatabitsSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialDatabitsSelect, 150);
    lv_obj_set_height(ui_SerialDatabitsSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SerialDatabitsSelect, -450);
    lv_obj_set_y(ui_SerialDatabitsSelect, -90);
    lv_obj_set_align(ui_SerialDatabitsSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SerialDatabitsSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_SerialStopbitsSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialStopbitsSelect, 150);
    lv_obj_set_height(ui_SerialStopbitsSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SerialStopbitsSelect, -450);
    lv_obj_set_y(ui_SerialStopbitsSelect, -30);
    lv_obj_set_align(ui_SerialStopbitsSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SerialStopbitsSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_SerialParitySelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialParitySelect, 150);
    lv_obj_set_height(ui_SerialParitySelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SerialParitySelect, -450);
    lv_obj_set_y(ui_SerialParitySelect, 30);
    lv_obj_set_align(ui_SerialParitySelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SerialParitySelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_SerialFlowControlSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialFlowControlSelect, 150);
    lv_obj_set_height(ui_SerialFlowControlSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SerialFlowControlSelect, -450);
    lv_obj_set_y(ui_SerialFlowControlSelect, 90);
    lv_obj_set_align(ui_SerialFlowControlSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SerialFlowControlSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_Label4 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, -591);
    lv_obj_set_y(ui_Label4, -150);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Baudrate");

    ui_Label7 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label7, -587);
    lv_obj_set_y(ui_Label7, 30);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "Parity");

    ui_Label8 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label8, -591);
    lv_obj_set_y(ui_Label8, -30);
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "StopBits");

    ui_Label9 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, -581);
    lv_obj_set_y(ui_Label9, 90);
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "FlowControl");

    ui_SerialOpenBtn = lv_btn_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialOpenBtn, 226);
    lv_obj_set_height(ui_SerialOpenBtn, 50);
    lv_obj_set_x(ui_SerialOpenBtn, -243);
    lv_obj_set_y(ui_SerialOpenBtn, -210);
    lv_obj_set_align(ui_SerialOpenBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SerialOpenBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SerialOpenBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SerialSendBt = lv_btn_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialSendBt, 100);
    lv_obj_set_height(ui_SerialSendBt, 99);
    lv_obj_set_x(ui_SerialSendBt, -186);
    lv_obj_set_y(ui_SerialSendBt, 56);
    lv_obj_set_align(ui_SerialSendBt, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SerialSendBt, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SerialSendBt, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SerialReadPanel = lv_obj_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SerialReadPanel, 502);
    lv_obj_set_height(ui_SerialReadPanel, 114);
    lv_obj_set_x(ui_SerialReadPanel, -376);
    lv_obj_set_y(ui_SerialReadPanel, -312);
    lv_obj_set_align(ui_SerialReadPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SerialReadPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WifiScanBtn = lv_btn_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_WifiScanBtn, 100);
    lv_obj_set_height(ui_WifiScanBtn, 50);
    lv_obj_set_x(ui_WifiScanBtn, 556);
    lv_obj_set_y(ui_WifiScanBtn, -306);
    lv_obj_set_align(ui_WifiScanBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiScanBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_WifiScanBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_WifiSwitch = lv_switch_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_WifiSwitch, 50);
    lv_obj_set_height(ui_WifiSwitch, 25);
    lv_obj_set_x(ui_WifiSwitch, -59);
    lv_obj_set_y(ui_WifiSwitch, -310);
    lv_obj_set_align(ui_WifiSwitch, LV_ALIGN_CENTER);

    ui_Label1 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -70);
    lv_obj_set_y(ui_Label1, -200);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "SSID");

    ui_WifiSSIDSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_WifiSSIDSelect, 150);
    lv_obj_set_height(ui_WifiSSIDSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WifiSSIDSelect, 50);
    lv_obj_set_y(ui_WifiSSIDSelect, -200);
    lv_obj_set_align(ui_WifiSSIDSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiSSIDSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_WifiPasswordTextArea = lv_textarea_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_WifiPasswordTextArea, 150);
    lv_obj_set_height(ui_WifiPasswordTextArea, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WifiPasswordTextArea, 390);
    lv_obj_set_y(ui_WifiPasswordTextArea, -200);
    lv_obj_set_align(ui_WifiPasswordTextArea, LV_ALIGN_CENTER);
    lv_textarea_set_placeholder_text(ui_WifiPasswordTextArea, "Placeholder...");

    ui_WifiEncryptMethodSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_WifiEncryptMethodSelect, 150);
    lv_obj_set_height(ui_WifiEncryptMethodSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WifiEncryptMethodSelect, 220);
    lv_obj_set_y(ui_WifiEncryptMethodSelect, -200);
    lv_obj_set_align(ui_WifiEncryptMethodSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiEncryptMethodSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_WifiConnectBtn = lv_btn_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_WifiConnectBtn, 100);
    lv_obj_set_height(ui_WifiConnectBtn, 50);
    lv_obj_set_x(ui_WifiConnectBtn, 556);
    lv_obj_set_y(ui_WifiConnectBtn, -200);
    lv_obj_set_align(ui_WifiConnectBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiConnectBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_WifiConnectBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label11 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label11, -63);
    lv_obj_set_y(ui_Label11, -342);
    lv_obj_set_align(ui_Label11, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label11, "WifiSwitch");

    ui_BacklightSlider = lv_slider_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_BacklightSlider, 480);
    lv_obj_set_height(ui_BacklightSlider, 20);
    lv_obj_set_x(ui_BacklightSlider, -376);
    lv_obj_set_y(ui_BacklightSlider, 200);
    lv_obj_set_align(ui_BacklightSlider, LV_ALIGN_CENTER);

    ui_Label12 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label12, -376);
    lv_obj_set_y(ui_Label12, 176);
    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label12, "Backlight");

    ui_Label13 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label13, -376);
    lv_obj_set_y(ui_Label13, 240);
    lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);

    ui_Label10 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label10, -540);
    lv_obj_set_y(ui_Label10, 320);
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "Battery");

    ui_BarttetyPercent = lv_obj_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_BarttetyPercent, 100);
    lv_obj_set_height(ui_BarttetyPercent, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BarttetyPercent, -450);
    lv_obj_set_y(ui_BarttetyPercent, 320);
    lv_obj_set_align(ui_BarttetyPercent, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_BarttetyPercent, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label15 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label15, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label15, -330);
    lv_obj_set_y(ui_Label15, 320);
    lv_obj_set_align(ui_Label15, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label15, "ChargeStatus");

    ui_BatteryChagingStatus = lv_obj_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_BatteryChagingStatus, 100);
    lv_obj_set_height(ui_BatteryChagingStatus, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BatteryChagingStatus, -220);
    lv_obj_set_y(ui_BatteryChagingStatus, 322);
    lv_obj_set_align(ui_BatteryChagingStatus, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_BatteryChagingStatus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SuspendBtn = lv_btn_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_SuspendBtn, 100);
    lv_obj_set_height(ui_SuspendBtn, 50);
    lv_obj_set_x(ui_SuspendBtn, 374);
    lv_obj_set_y(ui_SuspendBtn, 332);
    lv_obj_set_align(ui_SuspendBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SuspendBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SuspendBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PoweroffBtn = lv_btn_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_PoweroffBtn, 100);
    lv_obj_set_height(ui_PoweroffBtn, 50);
    lv_obj_set_x(ui_PoweroffBtn, 510);
    lv_obj_set_y(ui_PoweroffBtn, 332);
    lv_obj_set_align(ui_PoweroffBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_PoweroffBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_PoweroffBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label16 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label16, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label16, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label16, -70);
    lv_obj_set_y(ui_Label16, -90);
    lv_obj_set_align(ui_Label16, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label16, "ADC1");

    ui_ADCValuePanel1 = lv_obj_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_ADCValuePanel1, 100);
    lv_obj_set_height(ui_ADCValuePanel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ADCValuePanel1, 50);
    lv_obj_set_y(ui_ADCValuePanel1, -90);
    lv_obj_set_align(ui_ADCValuePanel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ADCValuePanel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label17 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label17, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label17, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label17, 150);
    lv_obj_set_y(ui_Label17, -90);
    lv_obj_set_align(ui_Label17, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label17, "ADC2");

    ui_ADCValuePanel2 = lv_obj_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_ADCValuePanel2, 100);
    lv_obj_set_height(ui_ADCValuePanel2, 50);
    lv_obj_set_x(ui_ADCValuePanel2, 270);
    lv_obj_set_y(ui_ADCValuePanel2, -90);
    lv_obj_set_align(ui_ADCValuePanel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ADCValuePanel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label14 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label14, 380);
    lv_obj_set_y(ui_Label14, -88);
    lv_obj_set_align(ui_Label14, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label14, "ADC3");

    ui_ADCValuePanel3 = lv_obj_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_ADCValuePanel3, 100);
    lv_obj_set_height(ui_ADCValuePanel3, 50);
    lv_obj_set_x(ui_ADCValuePanel3, 500);
    lv_obj_set_y(ui_ADCValuePanel3, -90);
    lv_obj_set_align(ui_ADCValuePanel3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ADCValuePanel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_GPIOSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_GPIOSelect, 150);
    lv_obj_set_height(ui_GPIOSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GPIOSelect, -20);
    lv_obj_set_y(ui_GPIOSelect, 0);
    lv_obj_set_align(ui_GPIOSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_GPIOSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_Label19 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label19, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label19, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label19, -20);
    lv_obj_set_y(ui_Label19, -30);
    lv_obj_set_align(ui_Label19, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label19, "GPIO");

    ui_GPIODirectionSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_GPIODirectionSelect, 150);
    lv_obj_set_height(ui_GPIODirectionSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GPIODirectionSelect, 170);
    lv_obj_set_y(ui_GPIODirectionSelect, 0);
    lv_obj_set_align(ui_GPIODirectionSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_GPIODirectionSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_Label20 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label20, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label20, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label20, 170);
    lv_obj_set_y(ui_Label20, -30);
    lv_obj_set_align(ui_Label20, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label20, "Direction");

    ui_GPIOValueSelect = lv_dropdown_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_GPIOValueSelect, 150);
    lv_obj_set_height(ui_GPIOValueSelect, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GPIOValueSelect, 360);
    lv_obj_set_y(ui_GPIOValueSelect, 0);
    lv_obj_set_align(ui_GPIOValueSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_GPIOValueSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags

    ui_Label21 = lv_label_create(ui_SerialSendBtn);
    lv_obj_set_width(ui_Label21, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label21, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label21, 360);
    lv_obj_set_y(ui_Label21, -30);
    lv_obj_set_align(ui_Label21, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label21, "Value");

}
