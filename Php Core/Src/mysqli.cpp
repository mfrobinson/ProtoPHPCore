#include "External/mysqli/mysqli.h"
#include "Variables/Value.h"
#include "Lexing/Tokeniser.h"
#include "Parsing/Parser.h"
#include "Classes/LibraryMethod.h"
#include "Functions/LibraryFunction.h"
#include "Classes/MethodFunctionUnion.h"
#include "Classes/MethodFunction.h"
#include "Classes/get_method_as_function.h"
#include <iostream>
#include <jdbc/cppconn/statement.h>

#include "Extensions/PHP_REGISTER_METHOD.h"
#include "Extensions/PHP_RETURN.h"
#include "Cast/ref_cast.h"
#include "Parsing/AbstractSyntaxTree.h"

#define STRICT(...) Proto::PHP::StrictInformation{Proto::Array<Proto::PHP::ValueType>(__VA_ARGS__)}
#define STRICT_ARGUMENT(...) ArgumentInformation{ STRICT(__VA_ARGS__) }
#define ARG_INFO(str, def) ArgumentInformation{ str, def }
#define REGISTER_STATIC_METHOD(registry_name, class_name, method_name) registry_name.set(#method_name, (Pointer<Callable>&&)(PolymorphicPointer<Callable>(LibraryFunction(&class_name::method_name, class_name##__##method_name##_signature()))))

namespace Proto {

	namespace PHP {

		size_t mysqli::connection_attempts = 0;
		// Class Methods

		mysqli::mysqli() : Proto::PHP::Object("mysqli"), driver(get_driver_instance()), connection(nullptr) {
			this->identifier = this->connection_attempts;
			return;
		}

		mysqli::mysqli(mysqli&& other) : Proto::PHP::Object("mysqli") {
			this->identifier = this->connection_attempts;
			this->_move_(other);
			return;
		}
		mysqli& mysqli::operator=(mysqli&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_move_(other);
			}
			return *this;
		}

		mysqli::~mysqli() {
			this->_cleanup_();
			return;
		}

		inline void mysqli::_move_(mysqli& other) {
			this->my_value = move_cast(other.my_value);
			this->identifier = this->connection_attempts;
			this->connection = move_cast(other.connection);
			this->most_recent_result = move_cast(other.most_recent_result);
			other.connection = nullptr;
			return;
		}
		inline void mysqli::_cleanup_() {
			if (this->connection != nullptr) {
				this->connection->close();
				delete this->connection;
				this->connection = nullptr;
			}
			return;
		}

		PHP_METHOD(mysqli::connect) {
			if (arguments[0].value()->type() != ValueType::STRING_TYPE) {
				throw std::runtime_error("hostname must be a string!");
			}
			if (arguments[1].value()->type() != ValueType::INTEGER_TYPE) {
				throw std::runtime_error("hostport must be an integer!");
			}

			Value::PHP_STRING_TYPE& hostname = *arguments[0].value();
			Value::PHP_INTEGER_TYPE& hostport = *arguments[1].value();

			if (hostport < 0) {
				throw std::runtime_error("hostport must be positive!");
			}

			try {
				this->driver = get_driver_instance();
				String host = hostname + ":" + String(hostport);
				this->connection = this->driver->connect(std::string(host), "Admin", "AdminTest");
			}
			catch (sql::SQLException e) {
				throw std::runtime_error("Could not connect to MySQL server!");
			}

			PHP_RETURN(Variable(Value(true)));
		}

		PHP_METHOD(mysqli::select_db) {
			if (this->connection == nullptr) {
				PHP_RETURN(Variable(Value(false)));
			}
			Value::PHP_STRING_TYPE& database_name = *arguments[0].value();
			this->connection->setSchema(sql::SQLString(database_name));
			PHP_RETURN(Variable(Value(true)));
		}

		PHP_METHOD(mysqli::execute) {
			if (this->connection == nullptr) {
				PHP_RETURN(Variable(Value(false)));
			}
			Value::PHP_STRING_TYPE& statement_text = *arguments[0].value();
			sql::Statement* statement = this->connection->createStatement();
			try {
				sql::ResultSet* result_set = statement->executeQuery(sql::SQLString(statement_text));
				PHP_RETURN(Value((Pointer<Object>&&)(PolymorphicPointer<Object>(mysqli_result(result_set)))));
			}
			catch (sql::SQLException e) {
				statement->execute(sql::SQLString(statement_text));
			}
			delete statement;
			PHP_RETURN(Variable(Value(true)));
		}

		PHP_METHOD(mysqli::close) {
			if (this->connection != nullptr) {
				this->connection->close();
				delete this->connection;
				this->connection = nullptr;
			}
			PHP_RETURN(Variable(Value(true)));
		}

		PHP_METHOD(mysqli::commit) {
			PHP_RETURN(Variable(Value(false)));
		}

		PHP_METHOD(mysqli::begin_transaction) {
			PHP_RETURN(Variable(Value(false)));
		}

		PHP_METHOD(mysqli::test_static) {
			PHP_RETURN(Variable(Value(false)));
		}


		// Method Signatures

		PHP_METHOD_SIGNATURE(mysqli, __construct) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}
		PHP_METHOD_SIGNATURE(mysqli, __destruct) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}
		PHP_METHOD_SIGNATURE(mysqli, begin_transaction) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}
		PHP_METHOD_SIGNATURE(mysqli, connect) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			arguments.set("host",     STRICT_ARGUMENT(ValueType::STRING_TYPE,  ValueType::NULL_TYPE));
			arguments.set("username", STRICT_ARGUMENT(ValueType::STRING_TYPE,  ValueType::NULL_TYPE));
			arguments.set("password", STRICT_ARGUMENT(ValueType::STRING_TYPE,  ValueType::NULL_TYPE));
			arguments.set("database", STRICT_ARGUMENT(ValueType::STRING_TYPE,  ValueType::NULL_TYPE));
			arguments.set("port",     STRICT_ARGUMENT(ValueType::INTEGER_TYPE, ValueType::NULL_TYPE));
			arguments.set("socket",   STRICT_ARGUMENT(ValueType::STRING_TYPE,  ValueType::NULL_TYPE));
			return FunctionInformation{ STRICT(ValueType::BOOLEAN_TYPE), arguments };
		}
		PHP_METHOD_SIGNATURE(mysqli, select_db) {
			StrictInformation return_information;
			return_information.types = Array<ValueType>(ValueType::BOOLEAN_TYPE);
			return FunctionInformation{ Optional<StrictInformation>(return_information) };
		}
		PHP_METHOD_SIGNATURE(mysqli, execute) {
			StrictInformation return_information;
			return_information.types = Array<ValueType>(ValueType::BOOLEAN_TYPE);
			return FunctionInformation{ Optional<StrictInformation>(return_information) };
		}
		PHP_METHOD_SIGNATURE(mysqli, close) {
			StrictInformation return_information;
			return_information.values = Array<Value>(Value(true));
			return FunctionInformation{ Optional<StrictInformation>(return_information)};
		}
		PHP_METHOD_SIGNATURE(mysqli, commit) {
			ArrayDictionary<String, ArgumentInformation> arguments;

			ArrayList<Token> default_flags_tokens;
			Tokeniser::tokenise_php("0", &default_flags_tokens);
			Pointer<AbstractSyntaxTree> default_flags = Parser::parse_expression(default_flags_tokens);
			arguments.set("flags", ArgumentInformation{ Proto::PHP::StrictInformation{Proto::Array<Proto::PHP::ValueType>(ValueType::INTEGER_TYPE)}, default_flags });

			ArrayList<Token> default_name_tokens;
			Tokeniser::tokenise_php("null", &default_name_tokens);
			Pointer<AbstractSyntaxTree> default_name = Parser::parse_expression(default_name_tokens);
			arguments.set("name", ARG_INFO(STRICT(ValueType::STRING_TYPE, ValueType::NULL_TYPE), default_name));

			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}
		PHP_METHOD_SIGNATURE(mysqli, test_static) {
			// No arguments, no specified return type
			return FunctionInformation{};
		}

		PHP_FUNCTION(mysqli_factory) {
			Pointer<Object> instance = (Pointer<Object>&&)PolymorphicPointer<Object>(mysqli());
			PHP_RETURN(Value(move_cast(instance)));
		}

		PHP_TRANSLATE_ADDRESS(mysqli) {
			return dynamic_cast<mysqli*>(object);
		}

		PHP_CLASS_SIGNATURE(mysqli) {
			ClassInformation signature;
			// Instance Methods
			REGISTER_METHOD(signature.instance_methods, mysqli, begin_transaction);
			REGISTER_METHOD(signature.instance_methods, mysqli, connect);
			REGISTER_METHOD(signature.instance_methods, mysqli, select_db);
			REGISTER_METHOD(signature.instance_methods, mysqli, execute);
			REGISTER_METHOD(signature.instance_methods, mysqli, close);
			REGISTER_METHOD(signature.instance_methods, mysqli, commit);
			// Static Methods
			REGISTER_STATIC_METHOD(signature.static_methods, mysqli, test_static);
			signature.factory_method = mysqli_factory;
			signature.translate_function = mysqli_translate_class_address;
			return signature;
		}

	}

}