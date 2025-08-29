#include "External/mysqli/mysqli_result.h"
#include "Memory Management/Pointers/PolymorphicPointer.h"
#include "Extensions/PHP_REGISTER_METHOD.h"
#include "Extensions/PHP_RETURN.h"
#include "Memory Management/Pointers/SharablePolymorphicPointer.h"


namespace Proto {

	namespace PHP {

		mysqli_result::mysqli_result() : Object("mysqli_result"), results(nullptr) {

		}

		mysqli_result::mysqli_result(mysqli_result&& other) : Object("mysqli_result") {
			this->_move_(other);
			return;
		}

		mysqli_result& mysqli_result::operator=(mysqli_result&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_move_(other);
			}
			return *this;
		}

		mysqli_result::~mysqli_result() {
			this->_cleanup_();
			return;
		}

		mysqli_result::mysqli_result(sql::ResultSet* result) : Object("mysqli_result"), results(result) {
			return;
		}

		inline void mysqli_result::_move_(mysqli_result& other) {
			this->results = other.results;
			other.results = nullptr;
		}

		inline void mysqli_result::_cleanup_() {
			if (this->results != nullptr) {
				delete this->results;
			}
			return;
		}

		PHP_METHOD(mysqli_result::fetch_all) {
			if (this->results == nullptr) {
				PHP_RETURN(Value(Value::PHP_ARRAY_TYPE()));
			}
			Value::PHP_ARRAY_TYPE result;
			sql::ResultSetMetaData* result_meta = this->results->getMetaData();
			for (size_t i = 0; this->results->next(); ++i) {
				Value::PHP_ARRAY_TYPE row_result;
				for (size_t j = 0; j < result_meta->getColumnCount(); ++j) {
					Value cell_value;
					sql::SQLString column_name = result_meta->getColumnName(j + 1);
					switch (result_meta->getColumnType(j + 1)) {
						case sql::DataType::SQLNULL:
							break;
						case sql::DataType::LONGVARCHAR:
						case sql::DataType::VARCHAR:
							cell_value = Value(Value::PHP_STRING_TYPE(results->getString(j + 1).c_str()));
							break;
						case sql::DataType::DOUBLE:
							cell_value = Value(Value::PHP_FLOAT_TYPE(results->getDouble(j + 1)));
							break;
						case sql::DataType::INTEGER:
							cell_value = Value(Value::PHP_INTEGER_TYPE(results->getInt64(j + 1)));
							break;
						default:
							String error("MYSQL TYPE NOT SUPPORTED: ");
							error += String((size_t)result_meta->getColumnType(j + 1));
							throw std::runtime_error(error);
					}
					row_result.set(Value(String(column_name.c_str())), cell_value);
				}
				result.set(Variable(Value((Value::PHP_INTEGER_TYPE)(i))), Variable(Value(row_result)));
			}
			PHP_RETURN(Value(result));
		}

		PHP_METHOD_SIGNATURE(mysqli_result, fetch_all) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}

		PHP_FUNCTION(mysqli_result_factory) {
			Value::PHP_OBJECT_TYPE instance = SharablePolymorphicPointer<Object>(mysqli_result());
			PHP_RETURN(Value(move_cast(instance)));
		}

		PHP_TRANSLATE_ADDRESS(mysqli_result) {
			return dynamic_cast<mysqli_result*>(object);
		}

		PHP_CLASS_SIGNATURE(mysqli_result) {
			ClassInformation signature;
			// Instance Methods
			REGISTER_METHOD(signature.instance_methods, mysqli_result, fetch_all);
			// Static Methods
			signature.factory_method = mysqli_result_factory;
			signature.translate_function = mysqli_result_translate_class_address;
			return signature;
		}

	}

}