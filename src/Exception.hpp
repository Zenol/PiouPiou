#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>

namespace PiouC
{
    class Exception : virtual public std::exception
    {
    public:
        virtual const char *what() const noexcept;
    };

}

#endif /* !EXCEPTION_H_ */
