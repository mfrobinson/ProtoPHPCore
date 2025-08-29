#pragma once
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "ProtoString.h"
#include "Extensions/PHP_RETURN.h"
#include "Parsing/AbstractSyntaxTree.h"


namespace Proto {

	namespace PHP {
		PHP_FUNCTION(http_response_code) {
			/*
			if (arguments.length() != 1) {
				throw std::runtime_error("http_response_code() must take exactly one argument!");
			}
			if (arguments[0].value()->type() != Proto::PhpValueType::INTEGER_TYPE) {
				throw std::runtime_error("http_response_code() must take an integer type argument!");
			}*/
			const Value::PHP_INTEGER_TYPE& value = *arguments[0].value();
			response.status_code = String(value);
			PHP_RETURN(Variable());
		}

		PHP_FUNCTION_SIGNATURE(http_response_code) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("code", ArgumentInformation{ Optional<StrictInformation>(StrictInformation{ValueType::INTEGER_TYPE, false}), Optional<AbstractSyntaxTree>(), false });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}