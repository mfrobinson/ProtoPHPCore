#pragma once
#include "Extensions/PHP_CLASS.h"
#include "Extensions/PHP_METHOD.h"
#include "Extensions/PHP_CLASS_SIGNATURE.h"
#include "Extensions/PHP_METHOD_SIGNATURE.h"
#include "Extensions/PHP_TRANSLATE_ADDRESS.h"

namespace Proto {

	namespace PHP {

		PHP_CLASS(File) {
		public:
			File();
			File(File&& other);
			File(const File& other);
			File& operator=(File&& other);
			File& operator=(const File& other);
			~File();

			File(String path);
			PHP_METHOD(read_all);
		protected:
			inline void _move_(File& other);
			inline void _copy_(const File& other);
			inline void _cleanup_();
		private:
			String file_name;
		};

		// Method metadata
		PHP_METHOD_SIGNATURE(File, read_all);
		// Class metadata
		PHP_CLASS_SIGNATURE(File);
		// Class construction
		PHP_FUNCTION(File_factory);
		// Address translation
		PHP_TRANSLATE_ADDRESS(File);

	}

}