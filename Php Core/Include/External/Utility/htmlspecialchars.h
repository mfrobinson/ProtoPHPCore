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

		PHP_FUNCTION(htmlspecialchars) {
			if (arguments.length() != 1) {
				throw std::runtime_error("htmlspecialchars takes one argument!");
			}
			if (arguments[0].value()->type() != ValueType::STRING_TYPE) {
				throw std::runtime_error("htmlspecialchars must take a string as an argument!");
			}
			const Value::PHP_STRING_TYPE& str = *arguments[0].value();
			Value::PHP_STRING_TYPE replaced = str.replace("&", "&amp");
			replaced = replaced.replace("\"", "&quot");
			replaced = replaced.replace("\'", "&#039");
			replaced = replaced.replace("<", "&lt");
			replaced = replaced.replace(">", "&gt");
			PHP_RETURN(Value(replaced));
		}

		PHP_FUNCTION_SIGNATURE(htmlspecialchars) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("arg", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), true });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}