#include "External/File Handling/File.h"
#include "Storage Management/FileReader.h"
#include "Extensions/PHP_RETURN.h"
#include "Extensions/PHP_REGISTER_METHOD.h"
#include <iostream>
#include "Memory Management/Pointers/SharablePolymorphicPointer.h"


namespace Proto {

	namespace PHP {

		File::File() : Object("File"), file_name() {
			return;
		}
		File::File(File&& other) : Object("File") {
			this->_move_(other);
			return;
		}
		File::File(const File& other) : Object("File") {
			this->_copy_(other);
			return;
		}
		File& File::operator=(File&& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_move_(other);
			}
			return *this;
		}
		File& File::operator=(const File& other) {
			if (&other != this) {
				this->_cleanup_();
				this->_copy_(other);
			}
			return *this;
		}
		File::~File() {
			this->_cleanup_();
			return;
		}

		File::File(String path) : Object("File"), file_name(path) {
			return;
		}

		PHP_METHOD(File::read_all) {
			FileReader reader;
			reader.open(this->file_name);
			if (reader.is_open()) {
				PHP_RETURN(Value(reader.read_all()));
			}
			PHP_RETURN(Value(false));
		}

		inline void File::_move_(File& other) {
			this->file_name = move_cast(other.file_name);
			return;
		}
		inline void File::_copy_(const File& other) {
			this->file_name = other.file_name;
			return;
		}
		inline void File::_cleanup_() {
			return;
		}

		// Method metadata
		PHP_METHOD_SIGNATURE(File, read_all) {
			ArrayDictionary<String, ArgumentInformation> arguments;
			return FunctionInformation{ Optional<StrictInformation>(), arguments };
		}
		// Class metadata
		PHP_CLASS_SIGNATURE(File) {
			ClassInformation signature;
			// Instance Methods
			REGISTER_METHOD(signature.instance_methods, File, read_all);
			signature.factory_method = File_factory;
			signature.translate_function = File_translate_class_address;
			return signature;
		}
		// Class construction
		PHP_FUNCTION(File_factory) {
			const String& path = *arguments[0].value();
			Value::PHP_OBJECT_TYPE instance = SharablePolymorphicPointer<Object>(File(path));
			auto a = Value(move_cast(instance));
			std::cout << "Returning an object of type: " << a.type() << "\n";
			PHP_RETURN(a);
		}
		// Address translation
		PHP_TRANSLATE_ADDRESS(File) {
			return dynamic_cast<File*>(object);
		}

	}

}