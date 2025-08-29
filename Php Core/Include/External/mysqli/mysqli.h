#pragma once
#include "Functions/Function.h"
#include "Functions/FunctionInformation.h"
#include "Classes/ClassInformation.h"
#include "Variables/Variable.h"
#include "Memory Management/Pointers/PolymorphicPointer.h"
#include "Classes/Object.h"
#include "Internet/Socket/Socket.h"
#include "Cast/move_cast.h"

#include <stdlib.h>
#include <iostream>

#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>

#include "Extensions/PHP_CLASS.h"
#include "Extensions/PHP_METHOD.h"
#include "Extensions/PHP_FIELD.h"
#include "Extensions/PHP_CLASS_SIGNATURE.h"
#include "Extensions/PHP_TRANSLATE_ADDRESS.h"
#include "Extensions/PHP_METHOD_SIGNATURE.h"

#include "External/mysqli/mysqli_result.h"


#define PHP_STATIC_FIELD(name) static PHP_FIELD(name)
#define PHP_SCRIPT_STATIC_FIELD(name) PHP_FIELD(*name)

#define PHP_CLASS_FACTORY(name) Proto::PolymorphicPointer<Proto::PHP::Object> name##___factory()
#define PHP_METHOD_OVERLOADS(class_name, method_name) Proto::PHP::LibraryFunctionOverloadsInformation class_name##__##method_name##_overloads()


namespace Proto {

	namespace PHP {
		
		// ALTERNATE IDEA: Make the macro PHP_CLASS inherit from an interface, then allow Object
		// values to point to an instance of a PHP_CLASS

		// VIRTUAL INHERITANCE CAUSES PROBLEMS - CANNOT CONVERT FROM
		//	&mysqli::method
		// TO
		//	&Object::method

		PHP_CLASS(mysqli) {
		public:
			mysqli();
			mysqli(mysqli&& other);
			mysqli(const mysqli& other) = delete;
			mysqli& operator=(mysqli&& other);
			mysqli& operator=(const mysqli& other) = delete;
			~mysqli();
			PHP_METHOD(connect);
			PHP_METHOD(select_db);
			PHP_METHOD(execute);
			PHP_METHOD(close);
			PHP_METHOD(commit);
			PHP_METHOD(begin_transaction);
			static PHP_METHOD(test_static);
		protected:
			inline void _move_(mysqli& other);
			inline void _copy_(const mysqli & other) = delete;
			inline void _cleanup_();
		private:
			sql::Driver* driver;
			sql::Connection* connection;
			mysqli_result most_recent_result;

			static size_t connection_attempts;
			size_t identifier;
			PHP_FIELD(my_value);
			PHP_SCRIPT_STATIC_FIELD(id);
		};

		// Method metadata
		PHP_METHOD_SIGNATURE(mysqli, __construct);
		PHP_METHOD_SIGNATURE(mysqli, __destruct);
		PHP_METHOD_SIGNATURE(mysqli, begin_transaction);
		PHP_METHOD_SIGNATURE(mysqli, connect);
		PHP_METHOD_SIGNATURE(mysqli, close);
		PHP_METHOD_SIGNATURE(mysqli, commit);
		// Class metadata
		PHP_CLASS_SIGNATURE(mysqli);
		// Class construction
		PHP_FUNCTION(mysqli_factory);
		// Address translation
		PHP_TRANSLATE_ADDRESS(mysqli);

	}

}