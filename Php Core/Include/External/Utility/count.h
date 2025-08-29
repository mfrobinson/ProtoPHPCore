#pragma once
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "Extensions/PHP_RETURN.h"
#include "Parsing/AbstractSyntaxTree.h"


namespace Proto {

	namespace PHP {

		PHP_FUNCTION(count) {
			if (arguments.length() != 1) {
				throw std::runtime_error("count takes one argument!");
			}
			if (arguments[0].value()->type() != ValueType::ARRAY_TYPE) {
				throw std::runtime_error("count must take an array / Countable as an argument!");
			}
			const Value::PHP_ARRAY_TYPE& arr = *arguments[0].value();
			PHP_RETURN(Value((Value::PHP_INTEGER_TYPE)arr.length()));
		}

		PHP_FUNCTION_SIGNATURE(count) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("arg", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}