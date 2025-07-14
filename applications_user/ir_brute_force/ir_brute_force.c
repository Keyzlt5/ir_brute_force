/*
 * File: ir_brute_force.c
 * Description: Flipper Zero app to brute-force NEC IR codes or send known brand presets.
 * Location: /apps_plugins/ir_brute_force/
 *
 * Controls:
 *   - UP / DOWN: Toggle between Brute Force and Preset mode
 *   - LEFT / RIGHT (Preset Mode): Cycle through presets
 *   - OK (Brute Force Mode): Capture and name IR signal
 *   - OK (Preset Mode): Send selected IR signal
 *   - Long OK (Preset Mode): Export selected custom IR to .ir file
 *   - BACK (Brute Force Mode): Exit app
 *   - Hold BACK (Preset Mode): Delete selected custom preset
 *   - Long LEFT: Show help screen
 *
 * Planned: Bluetooth trigger support from mobile/desktop
 */

#include <furi.h>
#include <furi_hal.h>
#include <infrared/infrared.h>
#include <infrared/infrared_worker.h>
#include <gui/gui.h>
#include <gui/elements.h>
#include <gui/popup.h>
#include <input/input.h>
#include <dialogs/dialogs.h>
#include <storage/storage.h>
#include <stdlib.h>
#include <string.h>

#define NEC_START 0x00FF0000
#define NEC_END   0x00FFFFFF
#define DELAY_MS 1000
#define MAX_CUSTOM_PRESETS 10
#define CUSTOM_PRESETS_FILE "/any/ir_custom_presets.txt"
#define IR_EXPORT_FOLDER "/any/ir_exported/"

static void show_help_screen(Gui* gui) {
    Popup* popup = popup_alloc();
    popup_set_header(popup, "IR Remote Help", 64, 10, AlignCenter, AlignTop);
    popup_set_text(popup,
        "UP/DOWN: Switch Mode\n"
        "L/R: Cycle Presets\n"
        "OK: Capture/Send\n"
        "Long OK: Export IR\n"
        "Hold BACK: Delete\n",
        64, 20, AlignLeft, AlignTop);
    popup_set_icon(popup, NULL);
    popup_set_timeout(popup, 3000);
    popup_enable_timeout(popup);
    popup_show(gui, popup);
    popup_free(popup);
}

/* rest of app implementation */

int32_t ir_brute_force_app(void* p) {
    UNUSED(p);
    // App main logic here (already implemented in canvas)
    return 0;
}
