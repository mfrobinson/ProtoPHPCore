#pragma once
#include "Variables/Value.h"
#include "Memory Management/Pointers/Array.h"
#include "Memory Management/find.h"
#include <random>
#include <chrono>


namespace Proto {

	namespace PHP {

		Value::PHP_STRING_TYPE c_session_create_id() {
			const size_t SESSION_ID_LENGTH = 32;
			Array<char> raw_id(SESSION_ID_LENGTH);
			const char* const SELECTABLE_CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUV";
			const size_t NUMBER_OF_SELECTABLE_CHARACTERS = find(SELECTABLE_CHARACTERS, '\0');
			srand(std::chrono::system_clock::now().time_since_epoch().count());
			for (size_t i = 0; i < SESSION_ID_LENGTH; ++i) {
				raw_id[i] = SELECTABLE_CHARACTERS[rand() % NUMBER_OF_SELECTABLE_CHARACTERS];
			}
			return Value::PHP_STRING_TYPE(raw_id, SESSION_ID_LENGTH);
		}

	}

}