#pragma once
#include "Variables/Value.h"
#include "Scope/AbstractScope.h"
#include "Data Structures/Dictionary/has_key.h"
#include "InterpreterContext.h"


namespace Proto {

	namespace PHP {

		Value::PHP_STRING_TYPE c_session_id(InterpreterContext& context) {
			if (context.current_scope->has_variable("_COOKIE")) {
				Variable cookies = context.current_scope->find_variable("_COOKIE");
				if (cookies.value()->type() == ValueType::ARRAY_TYPE) {
					Value::PHP_ARRAY_TYPE& cookie_array = *cookies.value();
					if (has_key(cookie_array, Variable(Value(String("PHPSESSID"))))) {
						const Variable& session_id_variable = cookie_array.lookup(Variable(Value(String("PHPSESSID"))));
						if (session_id_variable.value()->type() == ValueType::STRING_TYPE) {
							const Value::PHP_STRING_TYPE& session_id = *session_id_variable.value();
							return session_id;
						}
					}
				}
			}
			return "";
		}

		void c_session_id(InterpreterContext& context, HttpResponse& response, const Value::PHP_STRING_TYPE& new_id) {
			if (context.current_scope->has_variable("_COOKIE")) {
				Variable cookies = context.current_scope->find_variable("_COOKIE");
				if (cookies.value()->type() == ValueType::ARRAY_TYPE) {
					Value::PHP_ARRAY_TYPE& cookie_array = *cookies.value();
					if (has_key(cookie_array, Variable(Value(String("PHPSESSID"))))) {
						const Variable& session_id_variable = cookie_array.lookup(Variable(Value(String("PHPSESSID"))));
						if (session_id_variable.value()->type() == ValueType::STRING_TYPE) {
							const Value::PHP_STRING_TYPE& session_id = *session_id_variable.value();
							if (!(session_id == new_id)) {
								response.headers.append(Proto::HttpHeader{ "Set-Cookie", "PHPSESSID=" + new_id + "; path=/" });
							}
						}
					}
					cookie_array.set(Variable(Value(String("PHPSESSID"))), Variable(Value(String(new_id))));
					return;
				}
				else {
					Value::PHP_ARRAY_TYPE cookie_array;
					cookie_array.set(Variable(Value("PHPSESSID")), Variable(Value(new_id)));
					cookies = Variable(Value(cookie_array));
					response.headers.append(Proto::HttpHeader{ "Set-Cookie", "PHPSESSID=" + new_id + "; path=/" });
				}
			}
			else {
				Value::PHP_ARRAY_TYPE cookie_array;
				cookie_array.set(Variable(Value("PHPSESSID")), Variable(Value(new_id)));
				context.current_scope->register_variable("_COOKIE", Variable(Value(cookie_array)));
				response.headers.append(Proto::HttpHeader{ "Set-Cookie", "PHPSESSID=" + new_id + "; path=/" });
			}
			return;
		}

	}

}