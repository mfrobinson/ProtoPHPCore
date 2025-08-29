#pragma once
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "Memory Management/contains.h"
#include "Memory Management/find.h"
#include "ProtoString.h"
#include "Internet/Http/HttpHeader.h"
#include "Extensions/PHP_RETURN.h"
#include "Parsing/AbstractSyntaxTree.h"


namespace Proto {

	namespace PHP {
		PHP_FUNCTION(header) {
			if (arguments.length() != 1) {
				throw std::runtime_error("header() must take exactly one argument!");
			}
			if (arguments[0].value()->type() != ValueType::STRING_TYPE) {
				throw std::runtime_error("header() must take a string type argument!");
			}
			const Proto::String& value = *arguments[0].value();

			if (contains<char>(value, ':', value.length())) {
				const char* raw_value = value;
				size_t index_of_colon = find<char>(raw_value, ':');
				String lhs(raw_value, index_of_colon);
				String rhs(raw_value + index_of_colon + 2, value.length() - index_of_colon - 3);
				response.headers.append(HttpHeader{ lhs, rhs });
			}
			else {
				throw std::runtime_error("Cannot edit status line yet!");
			}
			PHP_RETURN(Variable());
		}

		PHP_FUNCTION_SIGNATURE(header) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("arg", ArgumentInformation{ Optional<StrictInformation>(), Optional<AbstractSyntaxTree>(), false });
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}