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

		PHP_FUNCTION(array_values) {
			if (arguments.length() != 1) {
				throw std::runtime_error("array_values takes exactly one argument!");
			}
			const Value::PHP_ARRAY_TYPE& array = *arguments[0].value();
			Value::PHP_ARRAY_TYPE values;
			for (size_t i = 0; i < array.length(); ++i) {
				values.set(Variable(Value((Value::PHP_INTEGER_TYPE)i)), Variable(*array.value_at(i).value()));
			}
			PHP_RETURN(Value(values));
		}

		PHP_FUNCTION_SIGNATURE(array_values) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("arg", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}