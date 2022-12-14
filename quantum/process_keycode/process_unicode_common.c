/* Copyright 2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "process_unicode_common.h"
#include "unicode.h"
#include "action_util.h"
#include "keycode.h"

#if defined(UNICODE_ENABLE)
#    include "process_unicode.h"
#elif defined(UNICODEMAP_ENABLE)
#    include "process_unicodemap.h"
#elif defined(UCIS_ENABLE)
#    include "process_ucis.h"
#endif

bool process_unicode_common(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        bool shifted = get_mods() & MOD_MASK_SHIFT;
        switch (keycode) {
            case UNICODE_MODE_FORWARD:
                cycle_unicode_input_mode(shifted ? -1 : +1);
                break;
            case UNICODE_MODE_REVERSE:
                cycle_unicode_input_mode(shifted ? +1 : -1);
                break;
            case UNICODE_MODE_MAC:
                set_unicode_input_mode(UC_MAC);
                break;
            case UNICODE_MODE_LNX:
                set_unicode_input_mode(UC_LNX);
                break;
            case UNICODE_MODE_WIN:
                set_unicode_input_mode(UC_WIN);
                break;
            case UNICODE_MODE_BSD:
                set_unicode_input_mode(UC_BSD);
                break;
            case UNICODE_MODE_WINC:
                set_unicode_input_mode(UC_WINC);
                break;
            case UNICODE_MODE_EMACS:
                set_unicode_input_mode(UC_EMACS);
                break;
        }
    }

#if defined(UNICODE_ENABLE)
    return process_unicode(keycode, record);
#elif defined(UNICODEMAP_ENABLE)
    return process_unicodemap(keycode, record);
#elif defined(UCIS_ENABLE)
    return process_ucis(keycode, record);
#else
    return true;
#endif
}
