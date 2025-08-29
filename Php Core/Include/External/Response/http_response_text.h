#pragma once
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "Extensions/PHP_RETURN.h"
#include "Parsing/AbstractSyntaxTree.h"


namespace Proto {

	namespace PHP {

		// EXTRA FEATURE (Not normally in PHP)
		PHP_FUNCTION(http_response_text) {
			/*
			if (arguments.length() != 1) {
				throw std::runtime_error("http_response_code() must take exactly one argument!");
			}
			if (arguments[0].value()->type() != Proto::PhpValueType::STRING_TYPE) {
				throw std::runtime_error("http_response_code() must take an string type argument!");
			}*/
			const Value::PHP_STRING_TYPE& value = *arguments[0].value();
			response.status_text = value;
			PHP_RETURN(Variable());
		}

		PHP_FUNCTION_SIGNATURE(http_response_text) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("text", ArgumentInformation{ Optional<StrictInformation>(StrictInformation{ValueType::STRING_TYPE, false}), Optional<AbstractSyntaxTree>(), true });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}