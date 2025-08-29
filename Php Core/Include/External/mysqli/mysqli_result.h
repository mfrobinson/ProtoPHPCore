#pragma once
#include "Extensions/PHP_CLASS.h"
#include "Extensions/PHP_METHOD.h"
#include "Extensions/PHP_CLASS_SIGNATURE.h"
#include "Extensions/PHP_TRANSLATE_ADDRESS.h"
#include "Extensions/PHP_METHOD_SIGNATURE.h"
#include <jdbc/cppconn/resultset.h>


namespace Proto {

	namespace PHP {

		PHP_CLASS(mysqli_result) {
		public:
			mysqli_result();
			mysqli_result(mysqli_result&& other);
			mysqli_result(const mysqli_result& other) = delete;
			mysqli_result& operator=(mysqli_result&& other);
			mysqli_result& operator=(const mysqli_result& other) = delete;
			~mysqli_result();

			mysqli_result(sql::ResultSet * result);

			PHP_METHOD(fetch_all);
		protected:
			inline void _move_(mysqli_result & other);
			inline void _copy_(const mysqli_result & other) = delete;
			inline void _cleanup_();
		private:
			sql::ResultSet* results;
		};


		PHP_METHOD_SIGNATURE(mysqli, __construct);
		PHP_CLASS_SIGNATURE(mysqli_result);


		PHP_FUNCTION(mysqli_result_factory);

		PHP_TRANSLATE_ADDRESS(mysqli_result);


	}

}