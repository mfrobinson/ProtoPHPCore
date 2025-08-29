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

		PHP_FUNCTION(array_keys) {
			if (arguments.length() != 1) {
				throw std::runtime_error("array_keys takes exactly one argument!");
			}
			const Value::PHP_ARRAY_TYPE& array = *arguments[0].value();
			Value::PHP_ARRAY_TYPE keys;
			for (size_t i = 0; i < array.length(); ++i) {
				keys.set(Variable(Value((Value::PHP_INTEGER_TYPE)i)), Variable(*array.key_at(i).value()));
			}
			PHP_RETURN(Value(keys));
		}

		PHP_FUNCTION_SIGNATURE(array_keys) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("arg", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}