// ir_brute_force.c
#include <furi.h>
#include <furi_hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <infrared/infrared.h>
#include <stdlib.h>

int32_t ir_brute_force_app(void* p) {
    UNUSED(p);
    FuriHalPowerProfile profile = furi_hal_power_get_profile();
    furi_hal_power_enable_otg();

    Infrared* infrared = infrared_alloc();
    if(!infrared) return -1;

    const uint32_t delay_ms = 250;

    for(uint32_t code = 0; code <= 0xFFFF; ++code) {
        uint8_t data[2];
        data[0] = (code >> 8) & 0xFF;
        data[1] = code & 0xFF;
        
        InfraredRawFrame* frame = infrared_raw_frame_alloc();
        frame->protocol = InfraredProtocolNEC;
        frame->address = data[0];
        frame->command = data[1];
        frame->repeat = false;

        infrared_transmit_raw_frame(infrared, frame);
        infrared_raw_frame_free(frame);

        furi_delay_ms(delay_ms);
    }

    infrared_free(infrared);
    furi_hal_power_disable_otg();
    furi_hal_power_set_profile(profile);

    return 0;
}
