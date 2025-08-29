#pragma once
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Extensions/PHP_FUNCTION_OVERLOADS.h"
#include "Extensions/PHP_ADD_FUNCTION_OVERLOAD.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "Cast/move_cast.h"
#include "Extensions/PHP_RETURN.h"
#include "Internal/Session/c_session_id.h"
#include "Parsing/AbstractSyntaxTree.h"

namespace Proto {

	namespace PHP {

		PHP_FUNCTION(session_id_zero) {
			PHP_RETURN(Variable(Value(c_session_id(context))));
		}

		PHP_FUNCTION(session_id_one) {
			c_session_id(context, response, *arguments[0].value());
			PHP_RETURN(Value());
		}

		PHP_FUNCTION_SIGNATURE(session_id_zero) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

		PHP_FUNCTION_SIGNATURE(session_id_one) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("id", ArgumentInformation{ Optional<StrictInformation>(StrictInformation{ValueType::STRING_TYPE, false}), Optional<AbstractSyntaxTree>(), false });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

		PHP_FUNCTION_OVERLOADS(session_id) {
			Array<Pointer<Callable>> overloads(2);
			PHP_ADD_FUNCTION_OVERLOAD(overloads, 0, session_id_zero);
			PHP_ADD_FUNCTION_OVERLOAD(overloads, 1, session_id_one);
			return FunctionOverloads{ move_cast(overloads) };
		}

	}

}