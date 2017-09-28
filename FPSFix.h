// Author: Sean Pesce
/*
	FPSFix.h

	Defines the loop that continuously checks for the bonfire input glitch conditions.
*/

#pragma once

#ifndef _SP_DS1_FPS_FIX_PLUS_H_
	#define _SP_DS1_FPS_FIX_PLUS_H_

// Main loop that checks if bonfire input bug conditions exist
DWORD WINAPI detection_thread(LPVOID lpParam)
{
	// Check whether to beep when fix is applied
	if ((int)GetPrivateProfileInt("Bonfire Input Fix", "BeepOnDetection", beep_on_fix, CONFIG_FILE) != 0)
		beep_on_fix = true;

	// Wait a bit for the game to load, just in case
	Sleep(1000);

	// Pointer to current player character status (loading, human, hollow, white phantom, or black phantom)
	SpPointer player_char_status = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF7E204), { 0xA28 });

	// Records time at which the bug conditions were first detected
	DWORD first_detected = 0;

	// Bug detection loop
	while (run_thread)
	{
		Sleep(200);

		// Get current player status
		int status = DS1_PLAYER_STATUS_LOADING;
		if (player_char_status.read(&status) != ERROR_SUCCESS)
			// Error reading memory location
			continue;

		// Check for bonfire input glitch conditions
		if (status == DS1_PLAYER_STATUS_HOLLOW || status == DS1_PLAYER_STATUS_HUMAN) // Check if player is hollow/human
		{
			// Get pointer to current character animation
			SpPointer bonfire_anim_fix = SpPointer((void*)0x12E29E8, { 0x0, 0xFC });

			// Read current character animation
			uint32_t current_anim;
			if (bonfire_anim_fix.read(&current_anim) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}


			// Read bonfire menu flag
			SpPointer bonfire_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x40 });
			uint8_t bonfire_menu_is_open;
			if (bonfire_menu_flag.read(&bonfire_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read repair menu flag
			SpPointer repair_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x4C });
			uint8_t repair_menu_is_open;
			if (repair_menu_flag.read(&repair_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read level up menu flag
			SpPointer level_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x78 });
			uint8_t level_menu_is_open;
			if (level_menu_flag.read(&level_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read bottomless box menu flag
			SpPointer bottomless_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x84 });
			uint8_t bottomless_menu_is_open;
			if (bottomless_menu_flag.read(&bottomless_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read attune magic menu flag
			SpPointer attune_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x80 });
			uint8_t attune_menu_is_open;
			if (attune_menu_flag.read(&attune_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read reinforce weapon/armor menu flag
			SpPointer reinforce_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x50 });
			uint8_t reinforce_menu_is_open;
			if (reinforce_menu_flag.read(&reinforce_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read warp menu flag
			SpPointer warp_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0xAC });
			uint8_t warp_menu_is_open;
			if (warp_menu_flag.read(&warp_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}

			// Read "reverse hollowing?"/"can't kindle"/"can't reverse hollowing"/"insufficient attunement slots" dialog flag
			SpPointer dialog_menu_flag = SpPointer((void*)((uint32_t)GetModuleHandle(NULL) + 0xF786D0), { 0x60 });
			uint8_t dialog_menu_is_open;
			if (dialog_menu_flag.read(&dialog_menu_is_open) != ERROR_SUCCESS)
			{
				// Error reading memory location
				first_detected = 0;
				continue;
			}


			// Check bonfire input bug conditions
			if ((current_anim == 7701 || current_anim == 7711 || current_anim == 7721) // 3 different bonfire resting animation IDs
				&& !bonfire_menu_is_open && !repair_menu_is_open && !bottomless_menu_is_open && !reinforce_menu_is_open && !level_menu_is_open && !attune_menu_is_open && !dialog_menu_is_open && !warp_menu_is_open) // Make sure no bonfire menus are open
			{
				// Bonfire input glitch conditions currently exist

				if (first_detected == 0)
				{
					// First detection; log time
					first_detected = GetTickCount();
					continue;
				}
				else if ((GetTickCount() - first_detected) >= 1000)
				{
					// Too much time has elapsed; bonfire input glitch is definitely present
					
					// Fix bonfire input glitch
					bonfire_anim_fix.write((uint32_t)0); // Write zero to player animation address, forcing player to leave bonfire
					if(beep_on_fix)
						Beep(500, 500);
				}
				else
				{
					// Not enough time has elapsed; return and check again later
					continue;
				}
			}
		}

		// Reset detection time
		first_detected = 0;
	}

	return 0;
}


#endif // _SP_DS1_FPS_FIX_PLUS_H_
