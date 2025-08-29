#pragma once
#include "InterpreterContext.h"
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "Extensions/PHP_RETURN.h"
#include "Parsing/AbstractSyntaxTree.h"


namespace Proto {

	namespace PHP {

		PHP_FUNCTION(isset) {
			if (arguments.length() != 1) {
				throw std::runtime_error("is_set only takes one argument!");
			}
			PHP_RETURN(Value(arguments[0].value()->type() != ValueType::NULL_TYPE));
		}

		PHP_FUNCTION_SIGNATURE(isset) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("arg", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}