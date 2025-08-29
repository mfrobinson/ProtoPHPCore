#pragma once
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "Internal/Session/c_session_create_id.h"
#include "Extensions/PHP_RETURN.h"


namespace Proto {

	namespace PHP {

		PHP_FUNCTION(session_create_id) {
			if (arguments.length() != 0) {
				throw std::runtime_error("session_create_id does not take any arguments!");
			}
			PHP_RETURN(Variable(Value(c_session_create_id())));
		}

		PHP_FUNCTION_SIGNATURE(session_create_id) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}