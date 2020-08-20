#include <pyy0sshi.hpp>

//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(name, func_id, min_args, max_args)

/* export to python module */
namespace boost::python {
	BOOST_PYTHON_MODULE(y0sshi) {
		class_<y0sshi::pspl>("pspl")
			.def(init<std::string>())
			.def("open_device"  , &y0sshi::pspl::open_device)
			.def("close_device" , &y0sshi::pspl::close_device)
			.def("read"         , &y0sshi::pspl::read)
			.def("write"        , &y0sshi::pspl::write)
			;
	}
};
