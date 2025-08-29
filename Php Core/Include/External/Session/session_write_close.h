#pragma once
#include "Extensions/PHP_FUNCTION.h"
#include "Extensions/PHP_FUNCTION_SIGNATURE.h"
#include "Variables/Value.h"
#include "Variables/ValueType.h"
#include "PhpSerialiser.h"
#include "Internal/Session/c_session_id.h"
#include "Storage Management/FileWriter.h"
#include "Extensions/PHP_RETURN.h"


namespace Proto {

	namespace PHP {

		PHP_FUNCTION(session_write_close) {
			Value::PHP_STRING_TYPE session_id = c_session_id(context);
			const String SESSION_FILE_PREFIX = "SESS_";
			const String SESSION_FILE_SUFFIX = ".txt";
			const String SESSION_FILE_NAME = SESSION_FILE_PREFIX + session_id + SESSION_FILE_SUFFIX;
			FileWriter session_writer;
			if (session_writer.open(SESSION_FILE_NAME)) {
				if (context.current_scope->has_variable("_SESSION")) {
					session_writer.write_all(PhpSerialiser::serialise(context.current_scope->find_variable("_SESSION")));
				}
				else {
					session_writer.write_all(PhpSerialiser::serialise(Value()));
				}
			}
			PHP_RETURN(Value(true));
		}

		PHP_FUNCTION_SIGNATURE(session_write_close) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

	}

}