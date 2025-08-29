#pragma once
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "Storage Management/FileReader.h"
#include "PhpSerialiser.h"
#include "Internal/Session/c_session_create_id.h"
#include "Internal/Session/c_session_id.h"
#include "Extensions/PHP_RETURN.h"


namespace Proto {

	namespace PHP {

		PHP_FUNCTION(session_start) {
			Value::PHP_STRING_TYPE session_id = c_session_id(context);
			if (session_id == "") {
				Value::PHP_STRING_TYPE new_session_id = c_session_create_id();
				response.headers.append(Proto::HttpHeader{ "Set-Cookie", "PHPSESSID=" + new_session_id + "; path=/" });
				c_session_id(context, response, new_session_id);
				session_id = c_session_id(context);
			}
			const String SESSION_FILE_PREFIX = "SESS_";
			const String SESSION_FILE_SUFFIX = ".txt";
			const String SESSION_FILE_NAME = SESSION_FILE_PREFIX + session_id + SESSION_FILE_SUFFIX;
			FileReader session_reader;
			if (session_reader.open(SESSION_FILE_NAME)) {
				context.current_scope->register_variable("_SESSION", PhpSerialiser::unserialise(session_reader.read_all()));
				PHP_RETURN(Value(true));
			}
			context.current_scope->register_variable("_SESSION", Value());
			PHP_RETURN(Value(true));
		}

		PHP_FUNCTION_SIGNATURE(session_start) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}