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

    class UnsupportedFeature : virtual public Exception
    {
    public:
        UnsupportedFeature(const char *string);
        virtual const char *what() const noexcept;
    private:
        const char* string;
    };

}

#endif /* !EXCEPTION_H_ */
