// Interface Structures/MACROs
	#include "Extensions/PHP_REGISTER.h"
	#include "Extensions/PHP_UNREGISTER.h"
	#include "Extensions/PHP_INTERNAL_REGISTER.h"
	#include "Extensions/PHP_REGISTER_FUNCTION.h"
	#include "Extensions/PHP_REGISTER_ALIAS.h"
	#include "Extensions/PHP_REGISTER_OVERLOADS.h"
	#include "Functions/FunctionRegistry.h"
	#include "Classes/ClassRegistry.h"
// Functions
	// Utility
		#include "External/Utility/isset.h"
		#include "External/Utility/is_bool.h"
		#include "External/Utility/is_int.h"
		#include "External/Utility/is_float.h"
		#include "External/Utility/is_string.h"
		#include "External/Utility/is_array.h"
		#include "External/Utility/is_object.h"
		#include "External/Utility/array_keys.h"
		#include "External/Utility/array_values.h"
		#include "External/Utility/strlen.h"
		#include "External/Utility/count.h"
		#include "External/Utility/str_replace.h"
		#include "External/Utility/htmlspecialchars.h"
	// Response
		#include "External/Response/http_response_code.h"
		#include "External/Response/http_response_text.h"
		#include "External/Response/header.h"
	// Session
		#include "External/Session/session_start.h"
		#include "External/Session/session_write_close.h"
		#include "External/Session/session_create_id.h"
		#include "External/Session/session_id.h"
// Classes
	// MySQL Database Connectivity
		#include "External/mysqli/mysqli.h"
		#include "External/mysqli/mysqli_result.h"
		#include "External/File Handling/File.h"

#include <iostream>

#define PHP_REGISTER_CLASS(registry, class_name) registry.set(#class_name, class_name##_class_signature())


namespace Proto {

	namespace PHP {

		PHP_INTERNAL_REGISTER(internal_register) {
			ExtensionInformation* extension_ptr = new ExtensionInformation{};
			FunctionRegistry& registry = extension_ptr->functions;
			// Utility
			PHP_REGISTER_FUNCTION(registry, isset);
			PHP_REGISTER_FUNCTION(registry, is_bool);
			PHP_REGISTER_FUNCTION(registry, is_int);
			PHP_REGISTER_FUNCTION(registry, is_float);
			PHP_REGISTER_FUNCTION(registry, is_string);
			PHP_REGISTER_FUNCTION(registry, is_array);
			PHP_REGISTER_FUNCTION(registry, is_object);
			PHP_REGISTER_FUNCTION(registry, array_keys);
			PHP_REGISTER_FUNCTION(registry, array_values);
			PHP_REGISTER_FUNCTION(registry, strlen);
			PHP_REGISTER_FUNCTION(registry, count);
			PHP_REGISTER_FUNCTION(registry, str_replace);
			PHP_REGISTER_FUNCTION(registry, htmlspecialchars);
			// Http Response functions
			PHP_REGISTER_FUNCTION(registry, header);
			PHP_REGISTER_FUNCTION(registry, http_response_code);
			PHP_REGISTER_FUNCTION(registry, http_response_text);
			// Session functions
			PHP_REGISTER_FUNCTION(registry, session_start);
			PHP_REGISTER_FUNCTION(registry, session_write_close);
			PHP_REGISTER_ALIAS(registry, session_commit, session_write_close);
			PHP_REGISTER_FUNCTION(registry, session_create_id);
			PHP_REGISTER_OVERLOADS(registry, session_id);
			//		PHP_REGISTER_OVERLOAD_ALIAS(registry, session_do_id, session_id);

			ClassRegistry& class_registry = extension_ptr->classes;
			PHP_REGISTER_CLASS(class_registry, mysqli);
			PHP_REGISTER_CLASS(class_registry, mysqli_result);
			PHP_REGISTER_CLASS(class_registry, File);
			return extension_ptr;
		}

	}

}

PHP_REGISTER(Proto::PHP::internal_register)
PHP_UNREGISTER();