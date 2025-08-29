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

		PHP_FUNCTION(str_replace) {
			if (arguments.length() < 3) {
				throw std::runtime_error("array_values must take at least three arguments!");
			}
			const Value::PHP_STRING_TYPE& search = *arguments[0].value();
			const Value::PHP_STRING_TYPE& replace = *arguments[1].value();
			const Value::PHP_STRING_TYPE& subject = *arguments[2].value();
			PHP_RETURN(Value(subject.replace(search, replace)));
		}

		PHP_FUNCTION_SIGNATURE(str_replace) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("search", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			arguments.set("replace", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			arguments.set("subject", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}