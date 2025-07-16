#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/view.h>
#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>
#include <notification/notification_messages.h>
#include <infrared/infrared.h>

#define APP_IR_BRUTE_FORCE "IR Brute Force"

typedef struct {
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    Infrared* infrared;
} IrBruteForceApp;

static void ir_brute_force_send_dummy_signal(IrBruteForceApp* app) {
    InfraredMessage msg = {
        .protocol = InfraredProtocolUnknown,
        .address = 0x00,
        .command = 0x01,
        .repeat = 1
    };
    infrared_send_command(app->infrared, &msg);
}

static void ir_brute_force_menu_callback(void* context, uint32_t index) {
    IrBruteForceApp* app = context;
    switch(index) {
        case 0:
            ir_brute_force_send_dummy_signal(app);
            break;
    }
}

static void ir_brute_force_app_free(IrBruteForceApp* app) {
    view_dispatcher_remove_view(app->view_dispatcher, 0);
    submenu_free(app->submenu);
    view_dispatcher_free(app->view_dispatcher);
    infrared_free(app->infrared);
    furi_record_close(RECORD_IR);
    free(app);
}

int32_t ir_brute_force_app(void* p) {
    UNUSED(p);
    IrBruteForceApp* app = malloc(sizeof(IrBruteForceApp));

    app->infrared = furi_record_open(RECORD_IR);
    app->view_dispatcher = view_dispatcher_alloc();
    app->submenu = submenu_alloc();

    submenu_add_item(app->submenu, "Send Dummy IR Signal", 0, ir_brute_force_menu_callback, app);

    view_dispatcher_add_view(app->view_dispatcher, 0, submenu_get_view(app->submenu));
    view_dispatcher_switch_to_view(app->view_dispatcher, 0);

    view_dispatcher_run(app->view_dispatcher);

    ir_brute_force_app_free(app);
    return 0;
}
