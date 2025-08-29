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

		PHP_FUNCTION(strlen) {
			if (arguments.length() != 1) {
				throw std::runtime_error("strlen takes one argument!");
			}
			if (arguments[0].value()->type() != ValueType::STRING_TYPE) {
				throw std::runtime_error("strlen must take a string as an argument!");
			}
			const Value::PHP_STRING_TYPE& str = *arguments[0].value();
			PHP_RETURN(Value((Value::PHP_INTEGER_TYPE)str.length()));
		}

		PHP_FUNCTION_SIGNATURE(strlen) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("arg", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}