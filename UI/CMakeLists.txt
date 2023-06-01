SET(SOURCES screens/ui_PeriManageScreen.c
    screens/ui_EthManageScreen.c
    ui.c
    ui_helpers.c
    ui_events.c)

add_library(ui ${SOURCES})
