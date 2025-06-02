#ifndef API_ROUTER_HTTP_RESPONSE_HPP_
#define API_ROUTER_HTTP_RESPONSE_HPP_

#include <string>
#include <sstream>
#include <cassert>
#include <unordered_map>
#include "apirouter/generic/types.hpp"
#include "apirouter/http/status_code.hpp"

namespace apirouter {
namespace http {



///
/// @brief
///     HTTP Response base class
/// 
class response
{
public:

    response(
        opt_string content = std::nullopt,
        opt_string content_type = std::nullopt,
        status_code_t status_code = status_code_t::OK
    );

    virtual void set_content(const std::string& content) { m_content = content; }

    virtual void set_content_type(const std::string& content_type)
    {
        m_content_type = content_type;
    }

    virtual void set_status_code(status_code_t code) { m_status_code = code; }

    virtual void set_status_code(unsigned int code)
    {
        assert(code <= 599 && code >= 100);
        m_status_code = (status_code_t)code;
    }


    virtual const std::string& get_content() const { return m_content; }
    virtual const std::string& get_content_type() const { return m_content; }
    virtual status_code_t get_status_code() const { return m_status_code; }

    virtual std::string format_response() const;

private:

    std::string m_content;
    std::string m_content_type;

    status_code_t m_status_code;



};

response::response(
    opt_string content,
    opt_string content_type,
    status_code_t status_code
)
    : m_content{ content.value_or("") },
    m_content_type{ content_type.value_or("text/html") },
    m_status_code{ status_code }
{

}

std::string response::format_response() const
{
    std::stringstream resstr{};

    resstr << "HTTP/1.1 " << (int)m_status_code << " " << g_status_code_map.at(m_status_code) << " \r\n";
    resstr << "content-type: " << m_content_type << "\r\n";
    resstr << "content-length: " << m_content.length() << "\r\n";
    resstr << "\r\n" << m_content;

    return resstr.str();
    
}

} // http
} // apirouter


#endif // API_ROUTER_HTTP_RESPONSE_HPP_