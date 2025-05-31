#ifndef API_ROUTER_ROUTING_RADIX_HPP_
#define API_ROUTER_ROUTING_RADIX_HPP_

#include "apirouter/generic/str_util.hpp"

#include "router.hpp"

#include <string>
#include <vector>
#include <optional>

namespace apirouter {
namespace radix {

class tree;

class node
{
public:
    node(const std::string& seg)
        : m_segment(seg), m_children{}, m_callback{ nullptr }
    {
    }

    node() : m_segment{}, m_children{}, m_callback{ nullptr } {}

    const std::string& get_segment() const { return m_segment; }

    const auto& get_children() const { return m_children; }

    const auto& get_callback() const { return m_callback; }
private:
    std::string m_segment;

    std::vector<node> m_children;
    
    route_callback_t m_callback;
    
    http::http_method method;

    friend bool operator==(const node&, const node&);
    friend class tree;
};
// TODO: NOT SCALEABLE
bool operator==(const radix::node& left, const radix::node& right)
{
    return (left.m_segment == right.m_segment);
}

///
/// @brief
///     Radix Trie
/// 
#pragma message ("!!!!!!!!!!!!!!REMEMBER TO OPTIMIZE THE RADIX::TREE!!!!!!!!!!!!!!!!")
class tree
{
public:
    tree() : m_root{}
    {
    }

    inline void insert(const std::vector<std::string>& list, route_callback_t cb, http::http_method method);
   
    inline void insert(node& entry, const generic::string_list& list, route_callback_t cb, http::http_method method);

    inline radix::node* search(const std::vector<std::string>& path);

    inline radix::node* get_root() { return &m_root; }
private:

private:

    radix::node m_root;
};

void radix::tree::insert(
    const std::vector<std::string>& list, route_callback_t cb, http::http_method method
)
{
    return insert(m_root, list, cb, method);
}

radix::node* radix::tree::search(const std::vector<std::string>& path)
{
    radix::node* head = &m_root;

    for (const auto& p : path)
    {
        auto iter = std::find(
            head->m_children.begin(),
            head->m_children.end(),
            p
        );

        if (iter == head->m_children.end())
            return nullptr;
        else {
            head = &(*iter);
        }
    }

    return head;
}

void radix::tree::insert(node& entry, const generic::string_list& list, route_callback_t cb, http::http_method method)
{
    radix::node* head = &entry;

    for (const auto& path : list)
    {
        auto iter = std::find(
            head->m_children.begin(),
            head->m_children.end(),
            path
        );

        if (iter != head->m_children.end())
        {
            head = iter._Ptr;
            continue;
        }
        else
        {
            head->m_children.push_back({ path });
            head = &head->m_children.back();
        }
    }

    if (head) 
    {
        head->m_callback = cb;
        head->method = method;
    }
}

} // radix
} // apirouter


#endif // API_ROUTER_ROUTING_RADIX_HPP_