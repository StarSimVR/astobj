/*
    Copyright (C) 2021 Luka-sama

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/**
 * @author      Luka-sama, Niklas Leukroth
 * @brief       Register GDNative classes.
 * @copyright   (C) 2022 Luka-sama.
 *              This file is licensed GPL 2 as of June 1991.
 * @date        2022
 * @file        gdlibrary.cpp
 * @note        See `LICENSE' for full license.
 *              See `README.md' for project details.
 *
 * This source file registers GDNative classes in Godot.
 */

/******************************************************************************/

/*
 * Includes.
 */

#include "AstroObject.hpp"

/**
 * @brief   Initialize GDNative.
 * @param   o   Options (see Godot reference for details).
 *
 * This function initializes GDNative so we can use GDNative for creating NativeScripts.
 */
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

/**
 * @brief   Terminate GDNative.
 * @param   o   Options (see Godot reference for details).
 *
 * This function terminates GDNative so Godot can clean up.
 */
extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

/**
 * @brief   Register GDNative classes.
 * @param   handle   Handle pointer (see Godot reference for details).
 *
 * This function initializes GDNative so Godot can clean up.
 */
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_tool_class<godot::AstroObject>();
}

/******************************************************************************/